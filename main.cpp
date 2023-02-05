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

	long int deltaTime = 0 ; // durata in nanosecondi di ogni ciclo del gioco

	bulletManager B = bulletManager();

	player P = player(10, 5, &B, 0.1, 10, 100);

	player enemy = player(100, 5, &B, 0.3, 30, 50); //temporaneo

	char input;
	bool quit = false;
	bool playerDead = false;
	bool enemyDead = false;

	while( !quit ){
		while( !quit ){
			TIME_POINT begin = NOW(); //tick

			//  INPUT E CALCOLI
			input = getch();
			if( P.getPos().y==30 ) P.setGrounded(true);
			else P.setGrounded(false);
			P.update(input, deltaTime);
			if( enemy.getPos().y==30 ) enemy.setGrounded(true);
			else enemy.setGrounded(false);
			enemy.update(input, deltaTime);
			B.update(deltaTime);
			if( input=='k' ){ //temporaneo
				point muzzle;
				muzzle.x = 120;
				muzzle.y = 30;
				vector speed;
				speed.x = -180;
				speed.y = -200;
				B.add(muzzle,speed,true,20,'G');
			}
			int playerDamage = B.check(P.getHitBox());
			int enemyDamage = B.check(enemy.getHitBox());
			playerDead = P.hurt(playerDamage);
			enemyDead = enemy.hurt(enemyDamage);

			if( input=='q' || playerDead ) quit = true;

			double seconds = deltaTime/(double)1000000000; //da nanosecondi a secondi

			//  OUTPUT
			//clear(); //è meglio stampare solo ciò che cambia
			mvprintw(0, 1, "fps: %.0f ", 1/seconds);
			mvprintw(0, 12, "|delta: %d ", deltaTime) ;//quanti secondi dura un ciclo
			mvprintw(1, 1, "health: %3d", P.getHealth());
			mvprintw(2, 1, "enemy: %3d", enemy.getHealth());
			move(32, 0);
			for(int i=0 ; i<COLS ; i++){ printw("#"); }

			B.print();
			P.print();
			enemy.print();
			refresh();

			TIME_POINT end = NOW(); //tock
			deltaTime = NANOSECONDS(end - begin).count();
			// milli > micro > nano
			// deltaTime viene calcolato in nanosecondi -> 10^-9 secondi
		}
	}
	endwin();
}