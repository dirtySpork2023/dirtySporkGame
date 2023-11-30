#include "lib.hpp"

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

bool collisionHH(hitBox B, hitBox T){
	// per ogni punto della hitbox T(iny), controllo se collide con la hitbox B(ig)
	bool found = false;
	int x = T.a.x;
	int y = T.a.y;
	while( x<=T.b.x && !found ){
		while( y<=T.b.y && !found ){
			point tmp;
			tmp.x = x;
			tmp.y = y;
			if( collisionHP(B, tmp) )
				found = true;
			y++;
		}
		x++;
	}
	return found;
}

bool collisionHP(hitBox box, point p){
	if( (box.a.x <= p.x && p.x <= box.b.x) &&
		(box.a.y <= p.y && p.y <= box.b.y) )
		return true;
	else
		return false;
}

bool collisionHV(hitBox box, vector p){
	if( (box.a.x-0.5 <= p.x && p.x <= box.b.x+0.5) &&
		(box.a.y-0.5 <= p.y && p.y <= box.b.y+0.5) )
		return true;
	else
		return false;
}

bool collisionPP(point A, point B){
	if( A.x==B.x && A.y==B.y ) return true;
	else return false;
}


// Controllo se v1 sta per scontrarsi con v2 nella direzione 'd'
bool isTouching (hitBox v1, hitBox v2, char d) {
	if( d=='d') return(!(v2.a.y > v1.b.y) && !(v2.b.y < v1.a.y) && v1.b.x == v2.a.x-1);
	else if(d=='a') return(!(v2.a.y > v1.b.y) && !(v2.b.y < v1.a.y) && v1.a.x == v2.b.x+1);
	else if(d=='s') return(!(v2.b.x < v1.a.x) && !(v2.a.x > v1.b.x) && v1.b.y == v2.a.y-1);
	else if(d=='w') return(!(v2.b.x < v1.a.x) && !(v2.a.x > v1.b.x) && v1.a.y == v2.b.y+1);
	else return false;
}

point snap(vector v){
	point result;
	result.x = (int)v.x;
	result.y = (int)v.y;
	return result;
}

// restituisce un vettore con inclinazione a caso e modulo compreso tra min e max
vector randVector(){
	vector result;
	result.x = rand()%61 - 30;
	result.y = -rand()%50 + 20;
	return result;
}

void posPrintW(point pos, const char* str){
	mvprintw(pos.y, pos.x, str);
}

void posPrintW(point pos, char ch){
	mvprintw(pos.y, pos.x, "%c", ch);
}

// ritorna true se il carattere è maiuscolo
bool upperCase(char c){
	return ('A'<=c && c<= 'Z');
}

void titleScreen(){
	/*
+------------------------------------------------------------------------------------------------------------------------------+
| ,_______, ,__,  ,_, ,____     ,_,     ,_______    ______,   ______,           ___    ,_,   ,_, ,_______    ______, ,_______, |
| |WWWWWWW| |WW\  |W| |WWWWW\   |W|     |WWWWWWW| /WWWWWWW| /WWWWWWW|         /WWWWW\  |W|   |W| |WWWWWWW| /WWWWWWW| |WWWWWWW| |
| |W|_____  |W*W\ |W| |W|  \WW  |W|     |W|_____  |W|____   |W|____          |W/   \W| |W|   |W| |W|_____  |W|____      |W|    |
| |WWWWWWW| |W|\W\|W| |W|   |W| |W|     |WWWWWWW| \WWWWWWW\ \WWWWWWW\        |W|  _|W| |W|   |W| |WWWWWWW| \WWWWWWW\    |W|    |
| |W|_____  |W| \W,W| |W|__/WW  |W|___, |W|_____   _____|W|  _____|W|        |W\__\W\' |W\___/W| |W|_____   _____|W|    |W|    |
| |WWWWWWW| |W|  \WW| |WWWWW/   |WWWWW| |WWWWWWW| |WWWWWWW/ |WWWWWWW/         \WWW,\W\  \WWWWW/  |WWWWWWW| |WWWWWWW/    |W|    |
+------------------------------------------------------------------------------------------------------------------------------+
                       |                           _______________________________________,  |
                       |   =====-----....__  __,-""  [____] _.----------,_________________|  |
                       |  |                ""   \___________(||||||||||||)_)                 |
                       |  |                   ,-"(( ]        `----------'                    |
                       |  |    ___....--,_  ,'    ""                                         |
                       |   """"           /`                                                 |
                       +---------------------------------------------------------------------+
                ______                           
 ______________//_____) _______________/|        
#######################H###############H#======HH
########Y"""""/H#((_)##`""""""""""""""~ '        
###Y"`       /H#/    ((                          
            (H#{      "                          
*/
	attrset(COLOR_PAIR(PAINT_TITLE));
	attron(A_BOLD);

	mvprintw(Y_OFFSET+0, X_OFFSET,  "+------------------------------------------------------------------------------------------------------------------------------+");
	mvprintw(Y_OFFSET+1, X_OFFSET,  "| ,_______, ,__,  ,_, ,____     ,_,     ,_______    ______,   ______,           ___    ,_,   ,_, ,_______    ______, ,_______, |");
	mvprintw(Y_OFFSET+2, X_OFFSET,  "| |WWWWWWW| |WW\\  |W| |WWWWW\\   |W|     |WWWWWWW| /WWWWWWW| /WWWWWWW|         /WWWWW\\  |W|   |W| |WWWWWWW| /WWWWWWW| |WWWWWWW| |");
	mvprintw(Y_OFFSET+3, X_OFFSET,  "| |W|_____  |W*W\\ |W| |W|  \\WW  |W|     |W|_____  |W|____   |W|____          |W/   \\W| |W|   |W| |W|_____  |W|____      |W|    |");
	mvprintw(Y_OFFSET+4, X_OFFSET,  "| |WWWWWWW| |W|\\W\\|W| |W|   |W| |W|     |WWWWWWW| \\WWWWWWW\\ \\WWWWWWW\\        |W|  _|W| |W|   |W| |WWWWWWW| \\WWWWWWW\\    |W|    |");
	mvprintw(Y_OFFSET+5, X_OFFSET,  "| |W|_____  |W| \\W,W| |W|__/WW  |W|___, |W|_____   _____|W|  _____|W|        |W\\__\\W\\' |W\\___/W| |W|_____   _____|W|    |W|    |");
	mvprintw(Y_OFFSET+6, X_OFFSET,  "| |WWWWWWW| |W|  \\WW| |WWWWW/   |WWWWW| |WWWWWWW| |WWWWWWW/ |WWWWWWW/         \\WWW,\\W\\  \\WWWWW/  |WWWWWWW| |WWWWWWW/    |W|    |");
	mvprintw(Y_OFFSET+7, X_OFFSET,  "+------------------------------------------------------------------------------------------------------------------------------+");

	attroff(A_BOLD);
}

void printResourceBar(WINDOW* w, int health, double armor, int money, int level, int difficulty){
	wattrset(w, COLOR_PAIR(PAINT_DEFAULT));
	box(w, 0, 0);

	mvwprintw(w, 2, WIN_OFFSET-7, "HEALTH: <|");
	wattrset(w, COLOR_PAIR(PAINT_HP));
	for(int i=0; i<health; i++) wprintw(w, "M");
	for(int i=health; i<100; i++) wprintw(w, "-");
	wattrset(w, COLOR_PAIR(PAINT_DEFAULT));
	wprintw(w, "|>");

	mvwprintw(w, 3, WIN_OFFSET-6, "ARMOR: <|");
	wattrset(w, COLOR_PAIR(PAINT_ARMOR));
	for(int i=0; i<armor*100 ; i++) wprintw(w, "M");
	for(int i=armor*100; i<100; i++) wprintw(w, "-");
	wattrset(w, COLOR_PAIR(PAINT_DEFAULT));
	wprintw(w, "|>");

	mvwprintw(w, 4, WIN_OFFSET-6, "MONEY: <| %d $ |>", money);
	mvwprintw(w, 5, WIN_OFFSET-6, "LEVEL: <| %d |>", level);
	mvwprintw(w, 6, WIN_OFFSET-11, "DIFFICULTY: <| %d |>", difficulty);
}