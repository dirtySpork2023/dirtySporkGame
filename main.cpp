#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <stdlib.h>

#include "lib.hpp"
#include "bulletManager.hpp"
#include "coin.hpp"
#include "entity.hpp"
#include "shooter.hpp"
#include "yuck.hpp"
#include "player.hpp"
#include "kuba.hpp"
#include "platform.hpp"
#include "level.hpp"
#include "menu.hpp"

using namespace std;

#define COIN_SPACING 7

struct lvlNode {
	level* lvl;
	lvlNode* next;
};
typedef lvlNode* lvlList;

int main(){
	srand(time(NULL));
	
	//inizializza ncurses
	init();

	// bottom window setup
	WINDOW* bottomWin = newwin(WIN_HEIGHT, COLS, LINES-WIN_HEIGHT, 0);
	
	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco
	
	char input;
	bool quit = false;
	bool openMenu = false;
	int numL = 1; // numero del livello corrente;
	int diff = numL;
	int money = 300;
	
	// Lista di livelli
	lvlList head = new lvlNode;
	head->lvl = new level (numL, diff);
	head->next = NULL;
	// Puntatore al livello corrente
	level* currentLvl = head->lvl;
	player P = player(2, LINES-WIN_HEIGHT-2, currentLvl, PISTOL, 12, 0);
	menu M = menu();
	
	while( !quit ) {
		// MENU
		if (!quit && openMenu){
			input = getch();
			if( input=='Q' ) quit = true;

			// RIPRENDI
			// MERCATO
			// - ARMA <SHOTGUN> per 2$
			// - AGGIUNGI HP per 2$
			// - AUMENTA ARMATURA a <70%> per 5$
			// LIVELLO <numL>

			input = M.open();
			if (input == 1) numL = M.changeLevel(currentLvl->number());
			else if (input == 2) M.market(&P, &money, bottomWin);
			openMenu = false;
			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money, currentLvl->number(), diff);
			// https://youtube.com/playlist?list=PL2U2TQ__OrQ8jTf0_noNKtHMuYlyxQl4v&si=F0BcWtcIV_qjJREG
		}

		// LEVEL SETUP
		if(currentLvl->number() != numL){
			if( head->lvl->number() < numL ){
				// livello nuovo aggiunto in testa
				lvlNode* tmp = new lvlNode;
				tmp->lvl = new level (head->lvl->number()+1, ++diff);
				tmp->next = head;
				head = tmp;
			}

			// cambia livello
			lvlNode* tmp = head;
			bool found = false;
			while( tmp != NULL && !found){
				if(tmp->lvl->number() == numL){
					currentLvl = tmp->lvl;
					found = true;
				}
				tmp = tmp->next;
			}
			P.changeLevel(currentLvl);
		}

		// CICLO PRINCIPALE
		auto lastTimePoint = std::chrono::high_resolution_clock::now();
		while( !quit && !openMenu && currentLvl->number()==numL){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();

			// UPDATE
			
			input = getch();
			if( input=='Q' ) quit = true;
			if( input=='m' ) openMenu = true;

			if(P.getPos().x==COLS-2 && input=='d' && currentLvl->completed()){
				numL++;
			}
			if( (P.getPos().x==1 && input=='a' || input=='m') && currentLvl->completed() ){
				// apri menu
				openMenu = true;
			}

		    currentLvl->update(&P, deltaTime);
			P.update(input, deltaTime);
			money += currentLvl->updateCoin(&P);

			// OUTPUT

			attrset(COLOR_PAIR(PAINT_BACKGROUND));
			// background brick texture
			for(int y=0; y<LINES-WIN_HEIGHT; y++){
				for(int x=0; x<COLS; x++){
					if( y%2==0 && x%6==1 || y%2==1 && x%6==4)
						mvprintw(y, x, "|");
					else
						mvprintw(y, x, "_");
				}
			}
			if(currentLvl->number()==1){
				titleScreen();
			}
			attrset(COLOR_PAIR(PAINT_DEFAULT));
			attron(A_DIM);
			mvprintw(0, 3, "fps: %.0f | deltaTime: %f ", 1/deltaTime, deltaTime);
			attroff(A_DIM);


			currentLvl->printAll(deltaTime);
			P.print(deltaTime);

			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money, currentLvl->number(), diff);

			refresh();
			wrefresh(bottomWin);
		}
	}
	delwin(bottomWin);
	endwin();
}