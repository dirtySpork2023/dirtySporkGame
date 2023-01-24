#include <ncurses.h>
#include <chrono>
#include "player.hpp"
using namespace std;

#define TIME_POINT std::chrono::steady_clock::time_point
#define NOW std::chrono::steady_clock::now
#define NANOSECONDS std::chrono::duration_cast<std::chrono::nanoseconds>

int main(){

	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);

	long int deltaTime = 0 ; // durata in nanosecondi di ogni "ciclo" del gioco
	bulletManager B = bulletManager();
	player P = player(3, 10, &B, 0.1, 10, 100);

	hitBox prova;
	prova.a.x = 40;
	prova.a.y = 28;
	prova.b.x = 45;
	prova.b.y = 31;

	char input;
	bool quit = false;

	while( !quit ){
		while( !quit ){
			TIME_POINT begin = NOW(); //tick

			//  INPUT E CALCOLI
			input = getch();
			P.update(input, deltaTime);
			if( input=='q' ) quit = true;

			B.update(deltaTime);
			double seconds = deltaTime/(double)1000000000; //da nanosecondi a secondi

			//  OUTPUT
			//clear(); //è meglio stampare solo ciò che cambia
			mvprintw(0, 1, "fps: %.0f ", 1/seconds);
			mvprintw(0, 12, "|delta: %d ", deltaTime) ;//quanti secondi dura un ciclo
			mvprintw(0, 40, "|hb: %d ", B.check(prova));
			move(32, 0);
			for(int i=0 ; i<COLS ; i++){ printw("#"); }

			B.print();
			P.print();
			refresh();

			TIME_POINT end = NOW(); //tock
			deltaTime = NANOSECONDS(end - begin).count();
			// milli > micro > nano
			// deltaTime viene calcolato in nanosecondi -> 10^-9 secondi
		}
	}
	endwin();
}