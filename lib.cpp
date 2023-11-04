#include "lib.hpp"

#include <ncurses.h>
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
    if (v2.a.y < v1.b.y) {
        k = 2;
    } else if (v2.b.y > v1.a.y) {
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

void posPrintW(point pos, const char* str){
	mvprintw(pos.y, pos.x, str);
}

bool upperCase(char c){
	return ('A'<=c && c<= 'Z');
}