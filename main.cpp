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

	init_color(COLOR_BLACK, 100, 100, 100);
	init_color(COLOR_DARK, 170, 170, 170);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(COLOR_RED, 1000, 0, 0);
	//init_color(COLOR_GREEN, 0, 1000, 0);
	init_color(COLOR_BLUE, 200, 200, 700);
	init_color(COLOR_PLAYER, 850, 1000, 850); //500, 800, 600
	init_color(COLOR_ENEMY, 300, 600, 700);
	init_color(COLOR_COIN, 800, 800, 0);
	init_color(COLOR_PLATFORM, 200, 200, 200);
	init_color(COLOR_HP, 200, 700, 200);

	init_pair(PAINT_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAINT_DAMAGE, COLOR_RED, COLOR_BLACK);
	init_pair(PAINT_PLAYER, COLOR_PLAYER, COLOR_BLACK);
	init_pair(PAINT_ENEMY, COLOR_ENEMY, COLOR_BLACK);
	init_pair(PAINT_COIN, COLOR_COIN, COLOR_BLACK);
	init_pair(PAINT_PLATFORM, COLOR_WHITE, COLOR_PLATFORM);
	init_pair(PAINT_HP, COLOR_HP, COLOR_BLACK);
	init_pair(PAINT_ARMOR, COLOR_BLUE, COLOR_BLACK);
	init_pair(PAINT_BACKGROUND, COLOR_DARK, COLOR_BLACK);

	attrset(COLOR_PAIR(PAINT_DEFAULT));
}

int main(){
	srand(time(NULL));
	
	init(); //inizializza ncurses

	// bottom window setup
	WINDOW* bottomWin = newwin(WIN_HEIGHT, COLS, LINES-WIN_HEIGHT, 0);
	
	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco
	
	bulletManager B = bulletManager();
	
	char input;
	int numL = 4; // Contatore dei livelli
	bool quit = false;

	int diff = numL;
	level* pointL;
	
	//titleScreen(); 
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
		    pointL->update(&P, deltaTime);

			if( input=='Q' ) quit = true;

			// OUTPUT

			attrset(COLOR_PAIR(PAINT_BACKGROUND));
			// background brick texture
			for(int y=0; y<LINES-WIN_HEIGHT; y++){
				for(int x=0; x<COLS-3; x+=4){
					if(y%2==0)
						mvprintw(y, x, "_|__");
					else
						mvprintw(y, x, "___|");
				}
			}
			attrset(COLOR_PAIR(PAINT_DEFAULT));
			attron(A_DIM);
			mvprintw(0, 3, "fps: %.0f | deltaTime: %f ", 1/deltaTime, deltaTime);
			attroff(A_DIM);


			pointL->printAll(deltaTime);
			B.print();
			P.print(deltaTime);

			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money);

			refresh();
			wrefresh(bottomWin);
		}
	}
	delwin(bottomWin);
	endwin();
}