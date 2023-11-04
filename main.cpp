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
struct coins{
	coin* C;
	coins* next;
};

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
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_PLAYER, 500, 1000, 600);
	init_color(COLOR_ENEMY, 500, 600, 1000);
	init_color(COLOR_COIN, 1000, 1000, 0);
	init_color(COLOR_PLATFORM, 200, 200, 200);

	init_pair(PAINT_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAINT_DAMAGE, COLOR_RED, COLOR_BLACK);
	init_pair(PAINT_PLAYER, COLOR_PLAYER, COLOR_BLACK);
	init_pair(PAINT_ENEMY, COLOR_ENEMY, COLOR_BLACK);
	init_pair(PAINT_COIN, COLOR_COIN, COLOR_BLACK);
	init_pair(PAINT_PLATFORM, COLOR_WHITE, COLOR_PLATFORM);

	attrset(COLOR_PAIR(PAINT_DEFAULT));	
}


int main(){
	srand(time(NULL));
	
	init(); //inizializza ncurses
	
	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco
	
	bulletManager B = bulletManager();
	
	char input;
	int numL = 0;                               // Contatore dei livelli
	bool quit = false;
	level* pointL; 

	while( !quit ){
		//level setup
		pointL = new level (numL, &B);
		player P = player(10, 10, pointL, &B, RIFLE, 12, 0.5);
		kuba* K = new kuba(80, 10, pointL, &B);
		shooter* S = new shooter(120, 10, pointL, &B);
		yuck* Y = new yuck(150, 10, pointL, &B);

		//creo una lista di monete posizionate in fila
		int money = 0;
		coins* H = new coins;
		coins* tmp = H;
		for(int i=0; i<COIN_SPACING*5; i+=COIN_SPACING){
			tmp->C = new coin(100+i, 42, 20);
			tmp->next = new coins;
			tmp = tmp->next;
		}
		tmp = NULL;

		//ciclo principale del gioco
		auto lastTimePoint = std::chrono::high_resolution_clock::now();
		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();

			input = getch();

            // UPDATE

			P.update(input, deltaTime);
			tmp = H;
			while( tmp->next!=NULL ){
				int value = -1;
				//se la moneta esiste ancora controllo se il player può prenderla
				if( tmp->C!=NULL ) value = tmp->C->check(P.getHitBox());
				if(value==-1){
					tmp = tmp->next;
				}else{
					money += value;
					delete tmp->C; //NON rimuovo nodi per pigrizia, li rendo solo vuoti
					tmp->C = NULL;
				}
			}
		    if(K!=NULL) K->update(&P, deltaTime);
			if(S!=NULL) S->update(P.getPos(), deltaTime);
			if(Y!=NULL) Y->update(P.getPos(), deltaTime);
		    B.update(deltaTime);

			// elimino entità morte
			if( input=='Q' ) quit = true;
			if(K!=NULL && K->getHealth()==0){
				delete K;
				K = NULL;
			}
			if(S!=NULL && S->getHealth()==0){
				delete S;
				S = NULL;
			}
			if(S==NULL && K==NULL && Y!=NULL){
				Y->wakeUp();
			}
			if(Y!=NULL && Y->getHealth()==0){
				delete Y;
				Y = NULL;
			}

			// OUTPUT

			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);
			//righe 1-2 scritte da player.print
			mvprintw(3, 1, "money: %d", money);
			mvprintw(4, 1, "Numero piattaforme: %d", pointL->givenplat());

			pointL->print_platforms();
			tmp = H;
			while( tmp->next!=NULL ){
				if( tmp->C!=NULL ) tmp->C->print(deltaTime);
				tmp = tmp->next;
			}
			B.print();
			P.print(deltaTime);
			if(K!=NULL) K->print(deltaTime);
			if(S!=NULL) S->print(deltaTime);
			if(Y!=NULL) Y->print(deltaTime);
			

			refresh();
		}
	}
	endwin();
}