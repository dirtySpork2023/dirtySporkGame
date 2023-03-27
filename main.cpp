#include <ncurses.h>
#include <chrono>
#include "lib.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "kuba.hpp"
#include "shooter.hpp"
#include "bulletManager.hpp"
#include "level.hpp"
using namespace std;

//inizializza ncurses
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
}

int main(){

	init();

	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco

	bulletManager B = bulletManager();

	char input;
	bool quit = false;

	while( !quit ){
		//level setup here

		int lvl = 1; //provvisorio per testing

		player P = player(10, 10, &B, 0.1, 10, 12, 0.5);
		kuba* K = new kuba(80, 10, &B, lvl);
		shooter* S = new shooter(120, 10, &B, lvl);

		auto lastTimePoint = std::chrono::high_resolution_clock::now();

		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();


			input = getch();

			// setGrounded
			if( P.getPos().y==35 ) P.setGrounded(true);
			else P.setGrounded(false);
			if( K!=NULL && K->getPos().y==35 ) K->setGrounded(true);
			else if(K!=NULL) K->setGrounded(false);
			if( S!=NULL && S->getPos().y==35 ) S->setGrounded(true);
			else if(S!=NULL) S->setGrounded(false);

			// update
			P.update(input, deltaTime);
			if(K!=NULL) K->update(&P, deltaTime);
			if(S!=NULL) S->update(P.getPos(), deltaTime);
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
			if(S==NULL && K==NULL){
				lvl++;
				K = new kuba(80, 10, &B, lvl);
				S = new shooter(120, 10, &B, lvl);
			}

			// output
			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);
			mvprintw(0, 30, "|level: %d", lvl);
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