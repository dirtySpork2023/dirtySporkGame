#include <ncurses.h>
#include <chrono>
#include "player.hpp"
#include "bulletManager.hpp"
using namespace std;

//#define TIME_POINT std::chrono::steady_clock::time_point
//#define NOW std::chrono::steady_clock::now
//#define NANOSECONDS std::chrono::duration_cast<std::chrono::nanoseconds>

int main(){

	initscr(); // inizializza ncurses
	start_color(); // permette di usare i colori attraverso gli attributi di ncurses
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	attrset(COLOR_PAIR(1));
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);

	double deltaTime = 0; // durata in secondi di ogni ciclo del gioco
	double realSeconds = 0;

	bulletManager B = bulletManager();

	player P = player(10, 5, &B, 0.1, 10, 100);

	char input;
	bool quit = false;
	bool playerDead = false;

	//init_pair(1, COLOR_RED, COLOR_BLUE);
	//attrset(COLOR_PAIR(1));
	//attrset(A_NORMAL);
	//if(has_colors()) printw("DOES HAVE COLORS");


	while( !quit ){

		auto lastTimePoint = std::chrono::high_resolution_clock::now();
		while( !quit ){

			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;

			deltaTime = std::chrono::duration<double>(elapsed).count();

			//TIME_POINT begin = NOW(); //tick

			//  INPUT E CALCOLI
			input = getch();
			if( P.getPos().y==30 ) P.setGrounded(true);
			else P.setGrounded(false);
			P.update(input, deltaTime);
			B.update(deltaTime);
			if( input=='k' ){ // crea un proiettile a partire dal punto 'muzzle'
				point muzzle;
				muzzle.x = 120;
				muzzle.y = 30;
				vector speed;
				speed.x = -100;
				speed.y = -100;
				B.add(muzzle,speed,true,20,'G');
			}
			int playerDamage = B.check(P.getHitBox());
			playerDead = P.hurt(playerDamage);

			if( input=='q' || playerDead ) quit = true;

			//  OUTPUT
			//mvprintw(0, 1, "fps: %.0f ", 1/seconds);
			//mvprintw(0, 12, "|delta: %d ", deltaTime) ;//quanti secondi dura un ciclo
			realSeconds += deltaTime;
			mvprintw(3,1, "%.2f", realSeconds);
			mvprintw(4,1, "pos.y= %d", P.getPos().y);

			mvprintw(2, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(2, 12, "|deltaTime: %f ", deltaTime);
			mvprintw(1, 1, "health: %3d", P.getHealth());
			move(32, 0);
			for(int i=0 ; i<COLS ; i++){ printw("#"); }

			B.print();
			P.print();
			refresh();

			//TIME_POINT end = NOW(); //tock
			//deltaTime = NANOSECONDS(end - begin).count();
			// milli > micro > nano
			// deltaTime viene calcolato in nanosecondi -> 10^-9 secondi
		}
	}
	endwin();
}