#include "coin.hpp"
#include "ncurses.h"

//		SpriteWeights
#define SW1 0.3 //	($)
#define SW2 0.1	//	 @
#define SW3 0.2 //	 |
//		SpriteTotalTime
#define STT SW1 + SW2 + SW3 + SW2

coin::coin(int x, int y, int value){
	box.a.x = x-1;
	box.a.y = y;
	box.b.x = x+1;
	box.b.y = y;
	this->value = value;
	this->t = 0;
}

int coin::check(hitBox p){
	if(collisionHH(p, box)==false)
		return 0;
	
	return value;
}

void coin::print(timeSpan deltaTime){
	t += deltaTime;
	if( t>STT ) t -= STT;

	attrset(COLOR_PAIR(PAINT_COIN));	

	if(t<SW1){
		posPrintW(box.a, "($)");
	}else if(t<SW1+SW2){
		posPrintW(box.a, " @ ");
	}else if(t<(STT-SW2)){
		posPrintW(box.a, " | ");
	}else{
		posPrintW(box.a, " @ ");
	}

	attrset(COLOR_PAIR(PAINT_DEFAULT));	
}

coin::~coin(){
	posPrintW(box.a, " ");
	posPrintW(box.b, " ");
}