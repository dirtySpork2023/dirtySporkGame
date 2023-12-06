#include <ncurses.h>
#include <stdio.h>
#include <chrono>

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
using namespace std::chrono;

struct lvlNode {
	level* lvl;
	lvlNode* next;
};
typedef lvlNode* lvlList;

int main(){
	srand(time(NULL));
	printf("fuck");
	//inizializza ncurses
	init();
	mvprintw(1,1,"hello0");
	// bottom window setup
	WINDOW* bottomWin = newwin(WIN_HEIGHT, COLS, LINES-WIN_HEIGHT, 0);
	
	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco
	mvprintw(1,1,"hello1");
	char input = 'd';
	bool quit = false;
	bool openMenu = false;
	int numL = 1; // numero del livello corrente;
	int diff = numL;
	int money = 0;
	
	mvprintw(1,1,"hello2");
	// Lista di livelli
	lvlList head = new lvlNode;
	head->lvl = new level (numL, diff);
	head->next = NULL;
	mvprintw(1,1,"hello3");
	// Puntatore al livello corrente
	level* currentLvl = head->lvl;
	player P = player(2, LINES-WIN_HEIGHT-2, currentLvl, PISTOL, 12, 0);
	menu M = menu();
	mvprintw(1,1,"hello4");
	while( !quit ){

		// MENU
		while(!quit && openMenu){
			input = getch();
			if( input=='Q' ) quit = true;
			if( input=='m' || input=='q' ) openMenu = false;
			// provvisorio
			if(input=='1'){ numL=1; }
			if(input=='2'){ numL=2; }
			if(input=='3'){ numL=3; }
			if(input=='4'){ numL=4; }
			if(input=='5'){ numL=5; }
			if(input=='6'){ numL=6; }
			if(input=='7'){ numL=7; }
			if(input=='8'){ numL=8; }
			if(input=='9'){ numL=9; }
			M.print();
			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money, currentLvl->number(), diff);
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
		auto lastTimePoint = high_resolution_clock::now();
		while( !quit && !openMenu && currentLvl->number()==numL){
			auto thisTimePoint = high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = duration<double>(elapsed).count();
			
			// UPDATE
			//input = getch();
			if( input=='Q' ) quit = true;
			if( input=='m' ) openMenu = true;
			if(P.getPos().x==COLS-2 && input=='d' && currentLvl->completed())
				numL++;
			if(P.getPos().x==1 && input=='a' && currentLvl->number()>1)
				numL--;
			
		    money += currentLvl->update(&P, deltaTime);
			P.update(input, deltaTime);
			// OUTPUT

			printBackground(currentLvl->number());
			mvprintw(0, 3, "[[fps: %.0f ]]", 1/deltaTime);

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