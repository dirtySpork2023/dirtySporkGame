#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include "lib.hpp"
#include "level.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"
#include "kuba.hpp"
#include "shooter.hpp"
#include "player.hpp"
#include "platform.hpp"
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

	init_pair(PAINT_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAINT_DAMAGE, COLOR_RED, COLOR_BLACK);
	init_pair(PAINT_PLAYER, COLOR_PLAYER, COLOR_BLACK);
	init_pair(PAINT_ENEMY, COLOR_ENEMY, COLOR_BLACK);
	attrset(COLOR_PAIR(PAINT_DEFAULT));

	ofstream Documento ("salvataggio.txt");
}

    struct strLevel {
		level liv;
		strLevel* next;
	};
	
	typedef strLevel* lLevels;

	
int main(){

	init();

	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco

	bulletManager B = bulletManager();

	char input;
	int numL = 0;                               // Contatore dei livelli
	bool quit = false;
	lLevels levels = new strLevel;           // Lista dei livelli
	lLevels pointL = levels;


	while( !quit ){
		//level setup here

		pointL->liv = level (numL, B);

		player P = player(10, 10, &liv, &B, 0.1, 10, 12, 0);
		kuba* K = new kuba(80, 10, &liv, &B);
		shooter* S = new shooter(120, 10, &liv, &B);
		

		auto lastTimePoint = std::chrono::high_resolution_clock::now();
		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();

			input = getch();

			// setGrounded
            /*
			if( P.getPos().y==35 ) P.setGrounded(true);
			else P.setGrounded(false);
			if( K!=NULL && K->getPos().y==35 ) K->setGrounded(true);
			else if(K!=NULL) K->setGrounded(false);
			if( S!=NULL && S->getPos().y==35 ) S->setGrounded(true);
			else if(S!=NULL) S->setGrounded(false);
			*/

            // Update
			level tmp = pointL->liv;

			P.update(input, deltaTime);
			
			// Update enemies:
			/*  Update con liste:
			while (tmp.enemies != NULL && tmp.enemies->type == 'k' ) {
				tmp.enemies->ent->update(&P, deltaTime);
				tmp.enemies = tmp.enemies->next;  
			} 
			while (tmp.enemies != NULL && tmp.enemies->type == 's' ) {
				tmp.enemies->ent->update(P.getPos(), deltaTime);
				tmp.enemies = tmp.enemies->next;
			}
			*/
		    if(K!=NULL) K->update(&P, deltaTime);
			if(S!=NULL) S->update(P.getPos(), deltaTime);
			
			// Update platforms:
			tmp.print_platforms ();
			
		    B.update(deltaTime);

			// death
			if( input=='q' ) quit = true;
			if(K!=NULL && K->getHealth()==0){
				delete K;
				K = NULL;
			}
			if(S!=NULL && S->getHealth()==0){
				delete S;
				S = NULL;
			}

			// output
			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);
			move(36, 0);
			for(int i=0 ; i<COLS ; i++){ printw("#"); }

			B.print();
			P.print(deltaTime);
			if(K!=NULL) K->print(deltaTime);
			if(S!=NULL) S->print(deltaTime);

			refresh();
		}
	}
	endwin();
}
