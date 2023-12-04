#include "coin.hpp"

//		Sprites
#define S1 0.3 //	($)
#define S2 0.1 //	 @
#define S3 0.2 //	 |
#define ANIMATION_TIME S1+S2+S3+S2

// costruttore
coin::coin(int x, int y, int value){
	box.a.x = x-1;
	box.a.y = y;
	box.b.x = x+1;
	box.b.y = y;
	this->value = value;
	this->t = 0;
}

// ritorna il valore della moneta se è presa, altrimenti ritorna -1
int coin::check(hitBox player){
	if( collisionHP(player, box.a) || collisionHP(player, box.b) )
		return value;
	else
		return -1;
}

// stampa la moneta animando l'animazione
void coin::print(timeSpan deltaTime){
	t += deltaTime;
	if( t>ANIMATION_TIME ) t -= ANIMATION_TIME;

	attrset(COLOR_PAIR(PAINT_COIN));	

	if(t<S1){
		posPrintW(box.a, "($)");
	}else if(t<S1+S2){
		posPrintW(box.a, " @ ");
	}else if(t<(ANIMATION_TIME-S2)){
		posPrintW(box.a, " | ");
	}else{
		posPrintW(box.a, " @ ");
	}

	attrset(COLOR_PAIR(PAINT_DEFAULT));	
}