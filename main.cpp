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

	deltaTime = 0 ;
	player P = player(6,6) ;
	char input ;

	while(true){
		//carica il livello

		while(true){
			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now() ; //tick

			//  INPUT
			input = getch() ;

			//  calcoli
			if(input=='a') P.pos.x--;
			else if(input=='d') P.pos.x++;

			double seconds = deltaTime/(double)1000000000 ; //da nanosecondi a secondi
			double fps = 1/seconds ;

			//  OUTPUT
			move(0, 1) ;
			printw("-fps: %.0f ", fps) ;
			printw("-seconds: %f ", seconds) ;//quanti secondi dura un ciclo
			P.print() ;
			refresh() ;

			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now() ; //tock
			deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() ;
			// milli > micro > nano
			// deltaTime viene calcolato in nanosecondi -> 1*10^-9 secondi
		}
	}
	endwin() ;
}