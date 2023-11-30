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

    /*
    armor
    %   $
    0   0
    20  50
    60  100 
    80  200
    90  400
    95  800
    
    guns    $
    PISTOL  0
    SHOTGUN 50
    RIFLE   100
    */
    for(int i=0; i<N_ARMOR; i++){
        armor[i].cost = i*50;
    }

    armor[0].value = 0;
    armor[1].value = 20;

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