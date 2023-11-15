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

// Funzione che ritorna dove si trova in ALTEZZA v2 rispetto a v1
// 1: sopra || 2: sotto || 3: coincidono in quelche punto
int whereIsY (hitBox v1, hitBox v2) {
    int k;
    if (v2.a.y > v1.b.y) {
        k = 2;
    } else if (v2.b.y < v1.a.y) {
        k=1;
    } else k=3;

    return k;
}

// Funzione che ritorna dove si trova in LARGHEZZA v2 rispetto a v1
// 1: sinistra || 2: destra || 3: coincidono in quelche punto
int whereIsX (hitBox v1, hitBox v2) {
    int k;
    if (v2.b.x < v1.a.x) {
        k = 1;
    } else if (v2.a.x > v1.b.x) {
        k = 2;
    } else k = 3;

    return k;
}


// Quattro funzioni per verificare se la hitBox r 
// sta per toccare la hitbox ch nelle varie direzioni
bool isTouchingA (hitBox r, hitBox ch) {
	return (whereIsY (r, ch) == 3 && r.b.x == ch.a.x-1);
} 

bool isTouchingD (hitBox r, hitBox ch) {
	return (whereIsY (r, ch) == 3 && r.a.x == ch.b.x+1);
}

bool isTouchingW (hitBox r, hitBox ch) {
	return (whereIsX (r, ch) == 3 && r.b.y == ch.a.y-1);
}

bool isTouchingS (hitBox r, hitBox ch) {
	return (whereIsX (r, ch) == 3 && r.a.y == ch.b.y+1);
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
	             _________, ,_,   ,_,     __         __    ,_________, ,_, ,__,    ,_, ,_,                                        ,__,     ____
	           /"  _______| | |   | |   -"  "-     -"  "-  |___, ,___| | | |  \    | | | |                         ,___________,  |  |    /  /
	          |  /"         | |   | |  /  __  \   /  __  \     | |     | | |   \   | | |_/                         |_____   ___|  |  |   /  /
	          \  ".____     | |___| | |  /  \  | |  /  \  |    | |     | | | |\ \  | |                      __________   \  \     |  |  /  /
	           "-.___  "\   | ,___, | |  |  |  | |  |  |  |    | |     | | | | \ \ | |  +-------,,    |""\  \    ___  "-  \  \    |  | /  /
	                 "\  |  | |   | | |  \__/  | |  \__/  |    | |     | | | |  \ \| |  |         "\  |   \  \   \__)   |  \  \   |  |/  /
	         ,_______."  /  | |   | |  \      /   \      /     | |     | | | |   \   |  |   +--_    \ |    \  \        /    \  \  |  /  /
	         |________.-"   |_|   |_|   "-__-"     "-__-"      |_|     |_| |_|    \__|  |   |   \   | |     \  \   \",  ",   \-"  |    /
																					    |   |   /   | |  |\  \  \   \ ",  ",      |   /
																						|   +--"    / |  |-"  \  \   \  ","       /  /
																						|         ,/  |     _  \  \   \          /  /
																						|   +---""    |  ,-" \  \  \-"          /  /
																						|   |         |  |    \-""             /  /
																						|   |         |  |                    ""-/
																						|   |         |-"
																						|   |
																						|   |         
																						|  _'
																						|-"
	*/

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
	 
	 
	 
	    |""\
	    |_=/
	--_ /7  ____,
	|__\WWW/____|
	   _WWW_
	  //===\\  
	 //     \\ 
	//       \\


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