#include <ncurses.h>

#include "menu.hpp"

bool addLife (player* P) {
    if (P->getHealth() >= 100) return false;
    else {
        //P->hurt(-int);
        return true;
    }
}
 
menu::menu(){
    this->win = newwin(HEIGHT, WIDTH, 10, COLS/2-WIDTH);

    for(int i=0; i<N_ARMOR; i++){
        armor[i].cost = i*50;
    }
    armor[0].value = 0;
    armor[1].value = 25;
    armor[2].value = 60;
    armor[3].value = 80;
    armor[4].value = 90;
    armor[5].value = 95;
    for(int i=0; i<N_GUNS; i++){
        gun[i].value = i;
        gun[i].cost = i*50;
    }
}
 
void menu::print(){
    box(win, 0, 0);
    wrefresh(win);
}

menu::~menu(){
    delwin(win);
}