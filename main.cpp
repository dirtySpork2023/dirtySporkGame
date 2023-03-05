#include <ncurses.h>
#include <chrono>
#include "entity.hpp"
#include "player.hpp"
#include "kuba.hpp"
#include "bulletManager.hpp"
using namespace std;

int main(){

	initscr(); // inizializza ncurses
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);

	start_color(); // permette di usare i colori attraverso gli attributi di ncurses
	init_color(COLOR_BLACK, 100, 100, 100);
	init_pair(1, COLOR_WHITE, COLOR_BLACK); //default
	init_pair(2, COLOR_RED, COLOR_BLACK); //player received damage
	attrset(COLOR_PAIR(1));
	//if(has_colors()) printw("DOES HAVE COLORS");

	double deltaTime = 0; // durata in secondi di ogni ciclo del gioco

	bulletManager B = bulletManager();

	player P = player(10, 5, &B, 0.1, 10, 12, 0.5);
	kuba K = kuba(100, 5, 50, &B, 0.1);

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
			if( K.getPos().y==30 ) K.setGrounded(true);
			else K.setGrounded(false);
			P.update(input, deltaTime);
			K.update(P.getPos(), deltaTime);
			B.update(deltaTime);
			if( input=='k' ){ // crea un proiettile a partire dal punto 'muzzle'
				point target = P.getPos();
				//mvprintw(target.y, target.x, "X");

				point p;
				p.x = COLS-5;
				p.y = 30;
				vector speed;
				speed.x = -150;
				//speed.y = -100;
				speed.y = -112*(target.x-p.x)/speed.x  +  (target.y-p.y)*speed.x/(target.x-p.x);
				//POV hai trovato un equazione utilizzando la fisica ma non è precisa
				// :C
				B.add(p,speed,true,4,'G');
			}
			if( input=='q' ) quit = true;

			//  OUTPUT
			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);
			mvprintw(1, 1, "health: %3d", P.getHealth());
			mvprintw(2, 1, "kuba: %3d", K.getHealth());
			move(32, 0);
			for(int i=0 ; i<COLS ; i++){ printw("#"); }

			B.print();
			P.print(deltaTime);
			K.print(deltaTime);

			refresh();
		}
	}
	endwin();
}