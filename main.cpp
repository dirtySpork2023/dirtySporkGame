#include <ncurses.h>
#include <chrono>
#include "lib.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "kuba.hpp"
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
		kuba* K = new kuba(100, 5, 50, &B, 0.1, 20);

		auto lastTimePoint = std::chrono::high_resolution_clock::now();

		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();


			//  INPUT E CALCOLI
			input = getch();
			if( P.getPos().y==35 ) P.setGrounded(true); // da spostare dentro entity
			else P.setGrounded(false);
			if( K!=NULL && K->getPos().y==35 ) K->setGrounded(true); // da spostare dentro entity
			else if(K!=NULL) K->setGrounded(false);
			P.update(input, deltaTime);
			if(K!=NULL) K->update(&P, deltaTime);
			B.update(deltaTime);
			if( input=='k' ){ // crea un proiettile a partire dal punto 'muzzle'
				point p;
				p.x = COLS-5;
				p.y = 35;
				vector speed;
				speed.x = -150;
				//speed.y = -100;
				int Dx = P.getPos().x -p.x -1;
				int Dy = P.getPos().y -p.y -1;

				speed.y = -112 * Dx / speed.x  +  Dy * speed.x / Dx;
				// velocità verticale esatta necessaria per colpire il player. (imprecisa su distanze più lunghe del terminale)
				// yeah mista white
				// yeah SCIENCE
				B.add(p,speed,true,4,'G');
			}
			if( input=='q' ) quit = true;
			if(K!=NULL && K->getHealth()==0){
				delete K;
				K = NULL;
				mvprintw(2, 1, "kuba: dead");
			}

			//  OUTPUT
			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);
			if(K!=NULL) mvprintw(2, 1, "kuba: %3d", K->getHealth());
			move(36, 0);
			for(int i=0 ; i<COLS ; i++){ printw("#"); }

			B.print();
			P.print(deltaTime);
			if(K!=NULL) K->print(deltaTime);

			refresh();
		}
	}
	endwin();
}