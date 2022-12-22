#include <ncurses.h>
#include <chrono>

#include "player.hpp"
using namespace std ;

long int deltaTime ; // durata in nanosecondi di ogni "ciclo" del gioco

int main(){
	initscr() ;
	noecho() ; // così gli input non appaiono scritti
	cbreak() ;
	nodelay(stdscr, TRUE) ; // così getch() non ferma il programma
	curs_set(0) ;

	deltaTime = 0 ;
	player P = player(20,5) ;
	double projectile = 1 ;
	char input ;
	bool quit = false ;

	while( !quit ){
		//carica il livello

		while( !quit ){
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now() ; //tick

			//  INPUT
			input = getch() ;

			//  calcoli
			P.move(input) ;
			if( input=='m' ) quit = true ;
			if( input=='k' ) projectile = 6 ;
			projectile += 1000.0/deltaTime ;

			double seconds = deltaTime/(double)1000000000 ; //da nanosecondi a secondi
			double fps = 1/seconds ;

			//  OUTPUT
			//clear();
			move(0, 1) ;
			printw("-fps: %.0f ", fps) ;
			printw("-seconds: %f ", seconds) ;//quanti secondi dura un ciclo
			P.print() ;
			mvprintw(P.pos.y, P.pos.x+(int)projectile-1, " #") ;
			refresh() ;

			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() ; //tock
			deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() ;
			// milli > micro > nano
			// deltaTime viene calcolato in nanosecondi -> 1*10^-9 secondi
		}
	}
	endwin() ;
}