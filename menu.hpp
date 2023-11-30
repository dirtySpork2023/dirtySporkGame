#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include "player.hpp"


#define HEIGHT 7
#define WIDTH 10

#define N_ARMOR 6
#define N_GUNS 3

//value dipende dall'oggetto
//cost è zero quando l'oggetto è già acquistato
struct buyable{
    int value;
    int cost;
};

bool addLife (player* P);

class menu {
protected:
    WINDOW* win;
    buyable armor[N_ARMOR]; // value da 0 a 100
    buyable gun[N_GUNS]; // values PISTOL, SHOTGUN, RIFLE
public:
    menu();
    void print();
    ~menu();
};












#endif // MENU_HPP