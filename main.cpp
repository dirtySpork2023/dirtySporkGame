#include <ncurses.h>
#include <iostream>
#include <fstream>
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

using namespace std;


#define COIN_SPACING 7

struct Plevel {
	level* thisLvl;
	Plevel* prev;
};
typedef Plevel* lLevel;


void init(){
	initscr();
	start_color();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);

	/*	COLOR_BLACK
		COLOR_RED
		COLOR_GREEN
		COLOR_YELLOW
		COLOR_BLUE
		COLOR_MAGENTA
		COLOR_CYAN
		COLOR_WHITE

	 	COLORS numero tot di colori
	 	COLOR_PAIRS numero tot di coppie di colori
	 */

	init_color(COLOR_BLACK, 100, 100, 100);
	init_color(COLOR_DARK, 170, 170, 170);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(COLOR_RED, 1000, 0, 0);
	//init_color(COLOR_GREEN, 0, 1000, 0);
	init_color(COLOR_BLUE, 200, 200, 700);
	init_color(COLOR_PLAYER, 850, 1000, 850); //500, 800, 600
	init_color(COLOR_ENEMY, 300, 600, 700);
	init_color(COLOR_COIN, 800, 800, 0);
	init_color(COLOR_PLATFORM, 200, 200, 200);
	init_color(COLOR_HP, 200, 700, 200);

	init_pair(PAINT_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAINT_DAMAGE, COLOR_RED, COLOR_BLACK);
	init_pair(PAINT_PLAYER, COLOR_PLAYER, COLOR_BLACK);
	init_pair(PAINT_ENEMY, COLOR_ENEMY, COLOR_BLACK);
	init_pair(PAINT_COIN, COLOR_COIN, COLOR_BLACK);
	init_pair(PAINT_PLATFORM, COLOR_WHITE, COLOR_PLATFORM);
	init_pair(PAINT_HP, COLOR_HP, COLOR_BLACK);
	init_pair(PAINT_ARMOR, COLOR_BLUE, COLOR_BLACK);
	init_pair(PAINT_BACKGROUND, COLOR_DARK, COLOR_BLACK);

	attrset(COLOR_PAIR(PAINT_DEFAULT));
}

int main(){
	srand(time(NULL));
	
	init(); //inizializza ncurses

	// bottom window setup
	WINDOW* bottomWin = newwin(WIN_HEIGHT, COLS, LINES-WIN_HEIGHT, 0);
	
	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco
	
	char input;
	bool quit = false;
	bool openMenu = false;
	int numL = 1; // numero del livello corrente;
	int diff = numL;
	int money = 0;
	
	bulletManager B = bulletManager();
	// Lista di livelli
	lLevel lvlList = new Plevel;
	lvlList->thisLvl = new level (numL, diff, &B);
	lvlList->prev = NULL;
	// Puntatore al livello corrente
	level* currentLvl = lvlList->thisLvl;
	player P = player(1, LINES-WIN_HEIGHT-2, currentLvl, &B, RIFLE, 12, 0.5);

	
	//titleScreen();
	while( !quit ){

		//menu
		while(!quit && openMenu){


			input = getch();
			if( input=='Q' ) quit = true;
			if( input=='m' ) openMenu = false;
			//menu.update(input);
			//menu.print;
			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money, currentLvl->number());

			// https://youtube.com/playlist?list=PL2U2TQ__OrQ8jTf0_noNKtHMuYlyxQl4v&si=F0BcWtcIV_qjJREG
			// RIPRENDI
			// MERCATO
			// - ARMA <SHOTGUN> per 2$
			// - AGGIUNGI HP per 2$
			// - AUMENTA ARMATURA a <70%> per 5$
			// LIVELLO <N>

			// OUTPUT

			mvprintw(20, 20, "#####  MENU APERTO | premi m per chiudere  #####");

			//dal menu si può cambiare anche il livello
			//settando numL al livello desiderato
		}

		//level setup
		if(currentLvl->number() != numL){

			//nuovo livello in testa
			lLevel tmp = new Plevel;
			tmp->prev = lvlList;
			tmp->thisLvl = new level (numL, diff, &B);
			lvlList = tmp;
			currentLvl = lvlList->thisLvl;
			P.changeLevel(currentLvl);

			//cambia a livello esistente
		}

		//ciclo principale del gioco
		auto lastTimePoint = std::chrono::high_resolution_clock::now();
		while( !quit && !openMenu && currentLvl->number()==numL){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();

			// UPDATE
			
			input = getch();
			if( input=='Q' || input=='q' ) quit = true;

			if(P.getPos().x==COLS-2 && input=='d' && currentLvl->completed()){
				// passa al livello successivo, che esista già o nuovo
				numL++;
			}
			if( (P.getPos().x==1 && input=='a' || input=='m') && currentLvl->completed() ){
				// apri menu
				openMenu = true;
			}

			B.update(deltaTime);
			P.update(input, deltaTime);
			money += currentLvl->updateCoin(&P);
		    currentLvl->update(&P, deltaTime);

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
			attrset(COLOR_PAIR(PAINT_DEFAULT));
			attron(A_DIM);
			mvprintw(0, 3, "fps: %.0f | deltaTime: %f ", 1/deltaTime, deltaTime);
			attroff(A_DIM);


			currentLvl->printAll(deltaTime);
			B.print();
			P.print(deltaTime);

			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money, currentLvl->number());

			refresh();
			wrefresh(bottomWin);
		}
	}
	delwin(bottomWin);
	endwin();
}
