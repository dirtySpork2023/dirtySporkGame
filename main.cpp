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
	int diff = 1;
	int money = 0;
	int points = 0;

	bool death = false;
	timeSpan deathAnimation = 0;
	
	// first setup
	lvlList head = NULL;
	head = addLevel(head, numL, diff);
	level* currentLvl = head->lvl;
	player P = player(4, LINES-WIN_HEIGHT-2, currentLvl, PISTOL, 12, 0.05);
	menu M = menu();
	
	while( !quit ){

		// LEVEL SETUP
		if(currentLvl->number() != numL){
			while( head->lvl->number() < numL ){
				// livello nuovo aggiunto in testa
				lvlNode* tmp = new lvlNode;
				tmp->lvl = new level (head->lvl->number()+1, ++diff);
				tmp->next = head;
				head = tmp;
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
		while( !quit && currentLvl->number()==numL){
			auto thisTimePoint = high_resolution_clock::now();
			auto elapsed = thisTimePoint - lastTimePoint;
			lastTimePoint = thisTimePoint;
			deltaTime = duration<double>(elapsed).count();

			// UPDATE
			
			if( P.getHealth()>0 ) input = getch();

			if( input=='Q' ) quit = true;
			if( input=='m' ) openMenu = !openMenu;
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
					diff = numL/2;
					numL = 1;
					//diff = M.count();
					head = addLevel(head, numL, diff);
					currentLvl = head->lvl;
					P.reset(currentLvl);
				}
			}
			if(P.getPos().x==COLS-2 && input=='d' && currentLvl->completed())
				numL++;
			if(P.getPos().x==1 && input=='a' && currentLvl->number()>1)
				numL--;

			if(openMenu){
				openMenu = M.update(input, money, numL, head->lvl->number(), &P, deltaTime);
			}else{
				currentLvl->update(&P, deltaTime, &money, &points);
				P.update(input, deltaTime);
			}
			
			// OUTPUT

			if(openMenu){
				M.print(numL);
			}else{
				printBackground(currentLvl->number());
				mvprintw(0, 3, "[[fps: %.0f ]]", 1/deltaTime);

				currentLvl->printAll(deltaTime);
				P.print(deltaTime);
				if(death) mvprintw(LINES/2, COLS/2-6, "- SEI MORTO -");
			}
			printResourceBar(bottomWin, P.getHealth(), P.getArmor(), money, points, currentLvl->number(), diff);

			refresh();
		}
	}
	delwin(bottomWin);
	endwin();
}
