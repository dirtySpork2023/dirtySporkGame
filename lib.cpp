#include "lib.hpp"
using namespace std;

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
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_PLAYER, 500, 800, 700);
	init_color(COLOR_ENEMY, 500, 700, 800);

	init_pair(PAINT_DEFAULT, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAINT_DAMAGE, COLOR_RED, COLOR_BLACK);
	init_pair(PAINT_PLAYER, COLOR_PLAYER, COLOR_BLACK);
	init_pair(PAINT_ENEMY, COLOR_ENEMY, COLOR_BLACK);
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