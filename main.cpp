#include <ncurses.h>
#include <chrono>

#include "player.hpp"
using namespace std ;

long int deltaTime ; // durata in nanosecondi di ogni "ciclo" del gioco

int main(){
	initscr() ;
	noecho() ;
	cbreak() ;
	nodelay(stdscr, TRUE) ;
	curs_set(0) ;

	deltaTime = 0 ;
	player P = player(3,10) ;
	double projectile = 1 ;
	char input ;
	bool quit = false ;

	while( !quit ){
		//carica il livello

		while( !quit ){
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now() ; //tick

			//  INPUT
			input = getch() ;

			//  CALCOLI
			P.move(input) ;
			if( input=='q' ) quit = true ;
			if( input=='f' ) projectile = 6 ;
			projectile += 500.0/deltaTime ;
			if( P.pos.y > 30 ) {
				P.pos.y = 30 ;
				P.ySpeed = 0 ;
				P.yMod = 0 ;
			}

			double seconds = deltaTime/(double)1000000000 ; //da nanosecondi a secondi
			double fps = 1/seconds ;

			//  OUTPUT
			//clear();
			mvprintw(0, 1, "fps: %.0f ", fps) ;
			mvprintw(0, 12, "|delta: %d ", deltaTime) ;//quanti secondi dura un ciclo
			mvprintw(0, 40, "|v: %f ", P.ySpeed) ;
			mvprintw(0, 60, "|y: %d_%.2f", P.pos.y, P.yMod) ;
			P.print() ;
			mvprintw(P.pos.y, P.pos.x+(int)projectile-1, " -") ;
			refresh() ;

			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() ; //tock
			deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() ;
			// milli > micro > nano
			// deltaTime viene calcolato in nanosecondi -> 1*10^-9 secondi
		}
	}
	endwin() ;
}