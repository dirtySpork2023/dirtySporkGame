#include "lib.hpp"

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
	init_color(COLOR_TITLE, 300, 300, 300);
	init_color(COLOR_SELECTED, 600, 600, 600);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_BLUE, 200, 200, 700);
	init_color(COLOR_PLAYER, 850, 1000, 850);
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
	init_pair(PAINT_TITLE, COLOR_TITLE, COLOR_BLACK);
	init_pair(PAINT_SELECTION, COLOR_WHITE, COLOR_SELECTED);

	attrset(COLOR_PAIR(PAINT_DEFAULT));
}

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

// numero random tra min e max compresi
int random(int min, int max){
	return rand()%(max-min+1) + min;
}

// restituisce un vettore con inclinazione a caso e modulo compreso tra min e max
vector randVector(){
	vector result;
	result.x = random(-30, +30);
	result.y = random(-20, -70);
	return result;
}

void posPrintW(point pos, const char* str){
	mvprintw(pos.y, pos.x, str);
}

void posPrintW(point pos, char ch){
	mvprintw(pos.y, pos.x, "%c", ch);
}

void printBackground(int lvl){
	attrset(COLOR_PAIR(PAINT_BACKGROUND));
	// background brick texture
	for(int y=0; y<LINES-WIN_HEIGHT; y++){
		for(int x=0; x<COLS; x++){
			if( y%2==0 && x%6==1 || y%2==1 && x%6==4)
				mvprintw(y, x, "|");
			else
				mvprintw(y, x, "_");
		}
	}
	if(lvl==1) attrset(COLOR_PAIR(PAINT_TITLE));
	/*
	+------------------------------------------------------------------------------------------------------------------------------+
	| ,_______, ,__,  ,_, ,____     ,_,     ,_______    ______,   ______,           ___    ,_,   ,_, ,_______    ______, ,_______, |
	| |WWWWWWW| |WW\  |W| |WWWWW\   |W|     |WWWWWWW| /WWWWWWW| /WWWWWWW|         /WWWWW\  |W|   |W| |WWWWWWW| /WWWWWWW| |WWWWWWW| |
	| |W|_____  |W*W\ |W| |W|  \WW  |W|     |W|_____  |W|____   |W|____          |W/   \W| |W|   |W| |W|_____  |W|____      |W|    |
	| |WWWWWWW| |W|\W\|W| |W|   |W| |W|     |WWWWWWW| \WWWWWWW\ \WWWWWWW\        |W|  _|W| |W|   |W| |WWWWWWW| \WWWWWWW\    |W|    |
	| |W|_____  |W| \W,W| |W|__/WW  |W|___, |W|_____   _____|W|  _____|W|        |W\__\W\' |W\___/W| |W|_____   _____|W|    |W|    |
	| |WWWWWWW| |W|  \WW| |WWWWW/   |WWWWW| |WWWWWWW| |WWWWWWW/ |WWWWWWW/         \WWW,\W\  \WWWWW/  |WWWWWWW| |WWWWWWW/    |W|    |
	+------------------------------------------------------------------------------------------------------------------------------+                       
	*/
	
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

	mvwprintw(w, 2, COLS/2-57, "HEALTH: <|");
	wattrset(w, COLOR_PAIR(PAINT_HP));
	for(int i=0; i<health; i++) wprintw(w, "M");
	for(int i=health; i<100; i++) wprintw(w, "-");
	wattrset(w, COLOR_PAIR(PAINT_DEFAULT));
	wprintw(w, "|>");

	mvwprintw(w, 3, COLS/2-56, "ARMOR: <|");
	wattrset(w, COLOR_PAIR(PAINT_ARMOR));
	for(int i=0; i<armor*100 ; i++) wprintw(w, "M");
	for(int i=armor*100; i<100; i++) wprintw(w, "-");
	wattrset(w, COLOR_PAIR(PAINT_DEFAULT));
	wprintw(w, "|>");

	mvwprintw(w, 4, COLS/2-56, "MONEY: <| %d $ |>", money);
	mvwprintw(w, 5, COLS/2-56, "LEVEL: <| %d |>", level);
	mvwprintw(w, 6, COLS/2-61, "DIFFICULTY: <| %d |>", difficulty);
}