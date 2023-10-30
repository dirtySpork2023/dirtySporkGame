#include "powerup.hpp"
#include "ncurses.h"

powerup::powerup(int x, int y){
	box.a.x = x;
	box.a.y = y-1;
	box.b.x = x;
	box.b.y = y;
}

void powerup::on(){

}

void powerup::print(){
	posPrintW(box.a, "O");
	posPrintW(box.b, "V");
}

powerup::~powerup(){
	posPrintW(box.a, " ");
	posPrintW(box.b, " ");
}