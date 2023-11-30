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
	              ________, ,_,   ,_,     __         __    ,_________, ,_, ,__,    ,_, ,_,                                        ,__,     ____
	           /WWWWWWWWWW| |w|   |W|   -WWWW-     -WWWW-  |WWWWWWWWW| |W| |WW\    |W| |M|                         ,___________,  |WW|    /WW/
	          |WWW"         |W|   |W|  /WWWWWW\   /WWWWWW\     |W|     |W| |W,W\   |W| |W'                         |WWWWWWWWWWW|  |WW|   /WW/
	          \WWW.___      |W|___|W| |WW/  \WW| |WW/  \WW|    |W|     |W| |W|\W\  |W|                      __________   \WW\     |WW|  /WW/
	           "-WWWWWwW\   |WWWWWWW| |WW|  |WW| |WW|  |WW|    |W|     |W| |W| \W\ |W|  |MMMMMMM,,    |WW\  \WWWWWWWWWW-  \WW\    |WW| /WW/
	                 "WWW|  |W|   |W| |WW\__/WW| |WW\__/WW|    |W|     |W| |W|  \W\|W|  |WWWWWWWWWW\  |WWW\  \WWW\__)WWW|  \WW\   |WW|/WW/
	         ,_______.WWW/  |W|   |W|  \WWWWWW/   \WWWWWW/     |W|     |W| |W|   \W'w|  |WWWMMMWWWWW\ |WWWW\  \WWWWWWWW/    \WW\  |WW/WW/
	         |WWWWWWWWW-"   |W|   |W|   "MWWM"     "MWWM"      |W|     |W| |W|    \WW|  |WWW|   \WWW| |WW,WW\  \WWW\"WWWW,   \M"  |WWWW/
																					    |WWW|   /WWW| |WW|\WW\  \WWW\ "WWWW,      |WWW/
																						|WWWWWWWWWWW/ |WW|-WWW\  \WWW\  "W"       /WW/
																						|WWWWWWWWWW/  |WWWWWWWW\  \WWW\          /WW/
																						|WWWMMMM""    |WWW-" \WW\  \M"          /WW/
																						|WWW|         |WW|    \M""             /WW/
																						|WWW|         |WW|                    ""M/
																						|WWW|         |M"
																						|WWW|
																						|WWW|         
																						|WWW'
																						|W"
	*/

	/*
	 p
	>W=
	/"\


	
	*/





	attron(A_BOLD);

	mvprintw(3, 20, "     _________, ,_,   ,_,     __         __    ,_________, ,_, ,__,    ,_, ,_,                                        ,__,     ____");
	mvprintw(4, 20, "   /\"  _______| | |   | |   -\"  \"-     -\"  \"-  |___, ,___| | | |  \\    | | | |                         ,___________,  |  |    /  /");
	mvprintw(5, 20, "  |  /\"         | |   | |  /  __  \\   /  __  \\     | |     | | |   \\   | | |_/                         |_____   ___|  |  |   /  /");
	mvprintw(6, 20, "  \\  \".____     | |___| | |  /  \\  | |  /  \\  |    | |     | | | |\\ \\  | |                      __________   \\  \\     |  |  /  /");
	mvprintw(7, 20, "   \"-.___  \"\\   | ,___, | |  |  |  | |  |  |  |    | |     | | | | \\ \\ | |  +-------,,    |\"\"\\  \\    ___  \"-  \\  \\    |  | /  /");
	mvprintw(8, 20, "         \"\\  |  | |   | | |  \\__/  | |  \\__/  |    | |     | | | |  \\ \\| |  |         \"\\  |   \\  \\   \\__)   |  \\  \\   |  |/  /");
	mvprintw(9, 20, " ,_______.\"  /  | |   | |  \\      /   \\      /     | |     | | | |   \\   |  |   +--_    \\ |    \\  \\        /    \\  \\  |  /  /");
	mvprintw(10, 20, " |________.-\"   |_|   |_|   \"-__-\"     \"-__-\"      |_|     |_| |_|    \\__|  |   |   \\   | |     \\  \\   \\\",  \",   \\-\"  |    /");
	mvprintw(11, 20, "                                                                            |   |   /   | |  |\\  \\  \\   \\ \",  \",      |   /");
	mvprintw(12, 20, "                                                                            |   +--\"    / |  |-\"  \\  \\   \\  \",\"       /  /");
	mvprintw(13, 20, "                                                                            |         ,/  |     _  \\  \\   \\          /  /");
	mvprintw(14, 20, "                                                                            |   +---\"\"    |  ,-\" \\  \\  \\-\"          /  /");
	mvprintw(15, 20, "                                                                            |   |         |  |    \\-\"\"             /  /");
	mvprintw(16, 20, "                                                                            |   |         |  |                    \"\"-/");
	mvprintw(17, 20, "                                                                            |   |         |-\"");
	mvprintw(18, 20, "                                                                            |   |");
	mvprintw(19, 20, "                                                                            |   |");
	mvprintw(20, 20, "                                                                            |   |");
	mvprintw(21, 20, "                                                                            |  _'");
	mvprintw(22, 20, "                                                                            |-\"");

	mvprintw(17, 30, "    |\"\"\\");
	mvprintw(18, 30, "    |_=/");
	mvprintw(19, 30, "--_ /7  ____,");
	mvprintw(20, 30, "|__\\WWW/____|");
	mvprintw(21, 30, "   _WWW_");
	mvprintw(22, 30, "  //===\\\\");
	mvprintw(23, 30, " //     \\\\");
	mvprintw(24, 30, "//       \\\\");

	attroff(A_BOLD);

	mvprintw(LINES-10, COLS/2-12, "PRESS SPACE TO CONTINUE");

	while(getch()!=' '){/*wait*/};
	clear();
}




void printResourceBar(WINDOW* w, int health, double armor, int money, int level, int difficulty){
	wattrset(w, COLOR_PAIR(PAINT_DEFAULT));
	box(w, 0, 0);

	mvwprintw(w, 2, WIN_OFFSET, "HEALTH: <|");
	wattrset(w, COLOR_PAIR(PAINT_HP));
	for(int i=0; i<health; i++) wprintw(w, "M");
	for(int i=health; i<100; i++) wprintw(w, "-");
	wattrset(w, COLOR_PAIR(PAINT_DEFAULT));
	wprintw(w, "|>");

	mvwprintw(w, 3, WIN_OFFSET, " ARMOR: <|");
	wattrset(w, COLOR_PAIR(PAINT_ARMOR));
	for(int i=0; i<armor*100 ; i++) wprintw(w, "M");
	for(int i=armor*100; i<100; i++) wprintw(w, "-");
	wattrset(w, COLOR_PAIR(PAINT_DEFAULT));
	wprintw(w, "|>");

	mvwprintw(w, 4, WIN_OFFSET, " MONEY: <| %d $ |>", money);
	mvwprintw(w, 5, WIN_OFFSET, " LEVEL: <| %d |>", level);
	mvwprintw(w, 6, WIN_OFFSET-4, "DIFFICULTY: <| %d |>", difficulty);
}