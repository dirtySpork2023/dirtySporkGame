#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
#include <stdlib.h>

#include "lib.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"
#include "shooter.hpp"
#include "player.hpp"
#include "powerup.hpp"
#include "kuba.hpp"
#include "platform.hpp"
#include "level.hpp"

using namespace std;

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
	init_color(COLOR_PLAYER, 500, 800, 700);
	init_color(COLOR_ENEMY, 500, 700, 800);
	init_color(COLOR_POWERUP, 700, 300, 300);
	init_color(COLOR_PLATFORM, 400, 400, 400);

	init_pair(PAINT_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAINT_DAMAGE, COLOR_RED, COLOR_BLACK);
	init_pair(PAINT_PLAYER, COLOR_PLAYER, COLOR_BLACK);
	init_pair(PAINT_ENEMY, COLOR_ENEMY, COLOR_BLACK);
	init_pair(PAINT_POWERUP, COLOR_POWERUP, COLOR_BLACK);
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
		player P = player(10, 10, pointL, &B, 0.1, 10, 12, 0);
		kuba* K = new kuba(80, 10, pointL, &B);
		shooter* S = new shooter(120, 10, pointL, &B);
		yuck* Y = new yuck(150, 10, pointL, &B);
		powerup* U = new powerup(100, 43);

		auto lastTimePoint = std::chrono::high_resolution_clock::now();
		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();

			input = getch();

            // Update

			P.update(input, deltaTime);
		    if(K!=NULL) K->update(&P, deltaTime);
			if(S!=NULL) S->update(P.getPos(), deltaTime);
			if(Y!=NULL) Y->update(P.getPos(), deltaTime);
				
		    B.update(deltaTime);

			// death
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

			// output
			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);	
			mvprintw(1, 1, "Numero piattaforme: %d", pointL->givenplat());
			mvprintw(4, 0, "Coordinate piattaforma 1: %d %d %d %d", pointL->coordinate(1).a.x, pointL->coordinate(1).a.y, pointL->coordinate(1).b.x, pointL->coordinate(1).b.y );
			mvprintw(6, 0, "Coordinate piattaforma 2: %d %d %d %d", pointL->coordinate(2).a.x, pointL->coordinate(2).a.y, pointL->coordinate(2).b.x, pointL->coordinate(2).b.y );
			pointL->print_platforms();
			B.print();
			P.print(deltaTime);
			if(K!=NULL) K->print(deltaTime);
			if(S!=NULL) S->print(deltaTime);
			if(Y!=NULL) Y->print(deltaTime);
			if(U!=NULL) U->print();

			refresh();
		}
	}
	endwin();
}