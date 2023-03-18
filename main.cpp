#include <ncurses.h>
#include <chrono>
#include "lib.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "kuba.hpp"
#include "shooter.hpp"
#include "bulletManager.hpp"
using namespace std;

//inizializza ncurses
void init(){
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);

	start_color(); // permette di usare i colori attraverso gli attributi di ncurses
	init_color(COLOR_BLACK, 100, 100, 100);
	init_pair(1, COLOR_WHITE, COLOR_BLACK); //default
	init_pair(2, COLOR_RED, COLOR_BLACK); //damaged entity
	attrset(COLOR_PAIR(1));
	//if(!has_colors()) printw("TERMINAL DOES NOT HAVE COLORS");
}

int main(){

	init();

	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco

	bulletManager B = bulletManager();

	char input;
	bool quit = false;

	while( !quit ){
		//level setup here

		player P = player(10, 5, &B, 0.1, 10, 12, 0.5);
		kuba* K = new kuba(COLS-30, 5, 50, &B, 0.1, 20);
		shooter* S = new shooter(COLS-10, 5, 50, &B, 1.5, 2);

		auto lastTimePoint = std::chrono::high_resolution_clock::now();

		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();


			input = getch();

			// setGrounded
			if( P.getPos().y==35 ) P.setGrounded(true); // da spostare dentro entity
			else P.setGrounded(false);
			if( K!=NULL && K->getPos().y==35 ) K->setGrounded(true); // da spostare dentro entity
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
				mvprintw(2, 1, "kuba: dead");
			}
			if(S!=NULL && S->getHealth()==0){
				delete S;
				S = NULL;
				mvprintw(3, 1, "shooter: dead");
			}

			// output
			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);
			if(K!=NULL) mvprintw(2, 1, "kuba: %3d", K->getHealth());
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