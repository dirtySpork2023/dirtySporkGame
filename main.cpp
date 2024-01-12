#include <ncurses.h>
#include <chrono>

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
#include "menu.hpp"
using namespace std::chrono;

struct lvlNode {
	level* lvl;
	lvlNode* next;
};
typedef lvlNode* lvlList;

// aggiunge livello nuovo in testa
lvlList addLevel(lvlList h, int num, int diff){
	lvlList tmp = new lvlNode;
	tmp->lvl = new level(num, diff);
	tmp->next = h;
	return tmp;
}

int main()
{
	srand(time(NULL));
	
	init();

	// bottom window setup
	WINDOW* bottomWin = newwin(WIN_HEIGHT, COLS, LINES-WIN_HEIGHT, 0);
	
	timeSpan deltaTime = 0; // durata in secondi di ogni ciclo del gioco
	
	char input;
	bool quit = false;
	bool openMenu = false;
	int numL = 1; // numero del livello corrente
	int diff = numL;
	int money = 100;

	bool death = false;
	timeSpan deathAnimation = 0;
	
	// first setup
	lvlList head = NULL;
	head = addLevel(head, numL, diff);
	level* currentLvl = head->lvl;
	player P = player(4, LINES-WIN_HEIGHT-2, currentLvl, PISTOL, 12, 0);
	menu M = menu();
	
	while( !quit ) {
		// MENU
		if (!quit && openMenu){
			input = getch();
			if( input=='Q' ) quit = true;

			input = M.open();

			if (input == 1) numL = M.changeLevel(head->lvl->number());
			else if (input == 2) M.market(&P, &money, bottomWin);
			
			openMenu = false;
			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money, currentLvl->number(), diff);
		}

		// LEVEL SETUP
		if(currentLvl->number() != numL){
			while( head->lvl->number() < numL ){
				head = addLevel(head, head->lvl->number()+1, ++diff);
			}

			// cambia livello
			lvlNode* tmp = head;
			bool found = false;
			while( tmp != NULL && !found){
				if(tmp->lvl->number() == numL){
					currentLvl = tmp->lvl;
					found = true;
				}
				tmp = tmp->next;
			}
			P.changeLevel(currentLvl);
		}

		// CICLO PRINCIPALE
		auto lastTimePoint = high_resolution_clock::now();
		while( !quit && !openMenu && currentLvl->number()==numL){
			auto thisTimePoint = high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = duration<double>(elapsed).count();

			// UPDATE
			
			if( P.getHealth()>0 ) input = getch();

			if( input=='Q' ) quit = true;
			if( input=='m' ) openMenu = true;
			if( P.getHealth()==0 && death==false ){
				death = true;
				deathAnimation = DEATH_TIMESPAN;
				// esplosione
				point boom = P.getPos();
				boom.y -= 3;
				for(int i=0; i<20; i++){
					currentLvl->getBM()->add(boom, randVector(), true, 0, ':');
				}
			}
			if( P.getHealth()==0 ){
				deathAnimation -= deltaTime;
				if( deathAnimation<0 ){
					death = false;
					// reset della lista di livelli
					while( head!=NULL ){
						delete head->lvl;
						lvlList tmp = head;
						head = tmp->next;
						delete tmp;
					}
					numL = 1;
					// diff=menu.countBoughtItems
					head = addLevel(head, numL, diff);
					currentLvl = head->lvl;
					P.reset(currentLvl);
				}
			}
			if(P.getPos().x==COLS-2 && input=='d' && currentLvl->completed())
				numL++;
			if(P.getPos().x==1 && input=='a' && currentLvl->number()>1)
				numL--;

		    currentLvl->update(&P, deltaTime, &money);
			P.update(input, deltaTime);

			// OUTPUT

			printBackground(currentLvl->number());
			mvprintw(0, 3, "[[fps: %.0f ]]", 1/deltaTime);

			currentLvl->printAll(deltaTime);
			P.print(deltaTime);
			if(death) mvprintw(LINES/2, COLS/2-6, "- SEI MORTO -");

			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money, currentLvl->number(), diff);

			refresh();
			wrefresh(bottomWin);
		}
	}
	delwin(bottomWin);
	endwin();
}