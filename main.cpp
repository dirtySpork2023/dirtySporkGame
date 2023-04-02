#include <ncurses.h>
#include <chrono>
#include "lib.hpp"
#include "level.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"
#include "kuba.hpp"
#include "shooter.hpp"
#include "player.hpp"
using namespace std;

int main(){

	init();

	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco

	bulletManager B = bulletManager();
	level levelClass = level(5);

	char input;
	bool quit = false;

	while( !quit ){
		//level setup here

		player P = player(10, 10, &B, 0.1, 10, 12, 0);
		kuba* K = new kuba(80, 10, &levelClass, &B);
		shooter* S = new shooter(120, 10, &levelClass, &B);

		auto lastTimePoint = std::chrono::high_resolution_clock::now();

		while( !quit ){
			auto thisTimePoint = std::chrono::high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = std::chrono::duration<double>(elapsed).count();


			input = getch();

			// setGrounded
/*			if( P.getPos().y==35 ) P.setGrounded(true);
			else P.setGrounded(false);
			if( K!=NULL && K->getPos().y==35 ) K->setGrounded(true);
			else if(K!=NULL) K->setGrounded(false);
			if( S!=NULL && S->getPos().y==35 ) S->setGrounded(true);
			else if(S!=NULL) S->setGrounded(false);*/

			// update
			P.update(input, deltaTime);
			if(K!=NULL) K->update(&P, deltaTime);
			if(S!=NULL) S->update(P.getPos(), deltaTime);
			B.update(deltaTime);

			// death
			if( input=='q' ) quit = true;
			if(K!=NULL && K->getHealth()==0){
				delete K;
				K = NULL;
			}
			if(S!=NULL && S->getHealth()==0){
				delete S;
				S = NULL;
			}

			// output
			mvprintw(0, 1, "fps: %.0f ", 1/deltaTime);
			mvprintw(0, 12, "|deltaTime: %f ", deltaTime);
			move(36, 0);
			for(int i=0 ; i<COLS ; i++){ printw("#"); }

			B.print();
			P.print(deltaTime);
			if(K!=NULL) K->print(deltaTime);
			if(S!=NULL) S->print(deltaTime);

			refresh();
		}
	}
	endwin();
}