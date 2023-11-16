#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
#include <stdlib.h>

#include "lib.hpp"
#include "bulletManager.hpp"
#include "coin.hpp"
#include "entity.hpp"
#include "shooter.hpp"
#include "yuck.hpp"
#include "player.hpp"
#include "kuba.hpp"
#include "platform.hpp"
#include "level.hpp"

using namespace std;


#define COIN_SPACING 7
struct coins{
	coin* C;
	coins* next;
};

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

	init_color(COLOR_BLACK, 120, 120, 130); //TODO change white/blacl to forward background
	init_color(COLOR_WHITE, 900, 900, 1000);
	init_color(COLOR_RED, 1000, 500, 0);
	init_color(COLOR_PLAYER, 900, 1000, 900); //500, 800, 600
	init_color(COLOR_ENEMY, 300, 600, 700);
	init_color(COLOR_COIN, 800, 800, 0);
	init_color(COLOR_PLATFORM, 200, 200, 200);
	init_color(COLOR_HP, 0, 1000, 0);

	init_pair(PAINT_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAINT_DAMAGE, COLOR_RED, COLOR_BLACK);
	init_pair(PAINT_PLAYER, COLOR_PLAYER, COLOR_BLACK);
	init_pair(PAINT_ENEMY, COLOR_ENEMY, COLOR_BLACK);
	init_pair(PAINT_COIN, COLOR_COIN, COLOR_BLACK);
	init_pair(PAINT_PLATFORM, COLOR_WHITE, COLOR_PLATFORM);
	init_pair(PAINT_HP, COLOR_HP, COLOR_BLACK);
	init_pair(PAINT_ARMOR, COLOR_BLUE, COLOR_BLACK);

	attrset(COLOR_PAIR(PAINT_DEFAULT));
	
}


int main(){
	srand(time(NULL));
	
	init(); //inizializza ncurses
	
	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco
	
	bulletManager B = bulletManager();
	
	char input;
	int numL = 3; // Contatore dei livelli
	bool quit = false;

	int diff = 0;
	level* pointL;
	
	titleScreen(); 
	while( !quit ){
		//level setup
		pointL = new level (numL, diff, &B);
		player P = player(10, 10, pointL, &B, RIFLE, 12, 0.5);
		int money = 0;

		//ciclo principale del gioco
		auto lastTimePoint = std::chrono::high_resolution_clock::now();
		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();

			input = getch();

            // UPDATE

			B.update(deltaTime);
			P.update(input, deltaTime);
			money += pointL->updateCoin(&P);
		    pointL->update(P, deltaTime);

			if( input=='Q' ) quit = true;

			// OUTPUT
			
			attron(A_DIM);
			mvprintw(0, 3, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 14, "|deltaTime: %f ", deltaTime);
			attroff(A_DIM);
			mvprintw(1, 3, "MONEY: %d @", money);
			//mvprintw(2, 3, "Numero piattaforme: %d", pointL->givenplat());

			pointL->printAll(deltaTime);
			B.print();
			P.print(deltaTime);
			
			refresh();
		}
	}
	endwin();
}