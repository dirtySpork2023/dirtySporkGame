#include <ncurses.h>

#include "menu.hpp"

bool addLife (player* P) {
    if (P->getHealth() >= 100) return false;
    else {
        // aumenta vita
        return true;
    }
}
 
menu::menu(){
    this->win = newwin(HEIGHT, WIDTH, 10, COLS/2-WIDTH);

    for(int i=1; i<N_ARMOR+1; i++){
        armors[i].value = i*225;
        armors[i].cost = i*20;
    }

    for(int i=0; i<N_GUNS; i++){
        guns[i].value = i;
        guns[i].cost = i*20;
    }
}
 
void menu::print(){
    box(win, 0, 0);
    wrefresh(win);
}



menu::~menu(){
    delwin(win);
}