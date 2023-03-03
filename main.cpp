#include <ncurses.h>
#include <chrono>
#include "entity.hpp"
#include "player.hpp"
#include "bulletManager.hpp"
using namespace std;

int main(){

	initscr(); // inizializza ncurses
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);

	//start_color(); // permette di usare i colori attraverso gli attributi di ncurses
	//init_pair(1, COLOR_WHITE, COLOR_BLACK);
	//attrset(COLOR_PAIR(1));
	//init_pair(1, COLOR_RED, COLOR_BLUE);
	//attrset(COLOR_PAIR(1));
	//attrset(A_NORMAL);
	//if(has_colors()) printw("DOES HAVE COLORS");

	double deltaTime = 0; // durata in secondi di ogni ciclo del gioco

	bulletManager B = bulletManager();

	player P = player(10, 5, &B, 0.1, 10, 100, 12);

	char input;
	bool quit = false;

	while( !quit ){

		auto lastTimePoint = std::chrono::high_resolution_clock::now();
		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();


			//  INPUT E CALCOLI
			input = getch();
			if( P.getPos().y==30 ) P.setGrounded(true);
			else P.setGrounded(false);
			P.update(input, deltaTime);
			B.update(deltaTime);
			if( input=='k' ){ // crea un proiettile a partire dal punto 'muzzle'
				point muzzle;
				muzzle.x = COLS - 20;
				muzzle.y = 30;
				vector speed;
				speed.x = -100;
				speed.y = -100;
				B.add(muzzle,speed,true,20,'G');
			}
			if( input=='q' ) quit = true;

			//  OUTPUT
			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);
			mvprintw(1, 1, "health: %3d", P.getHealth());
			move(32, 0);
			for(int i=0 ; i<COLS ; i++){ printw("#"); }

			mvprintw(2,1, "height: %d", P.getPos().y);

			B.print();
			P.print();

			refresh();
		}
	}
	endwin();
}