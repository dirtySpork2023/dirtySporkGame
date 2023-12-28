#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include "player.hpp"


#define HEIGHT (LINES-18)
#define WIDTH (COLS-75)

#define N_ARMOR 3
#define N_GUNS 3

//value dipende dall'oggetto
//cost è zero quando l'oggetto è già acquistato
struct buyable{
    int value;
    int cost;
};

bool addLife (player* P);
int changeLevel(int totLvl, WINDOW* win);
void market ();

class menu {
protected:
    WINDOW* win;
    buyable armors[N_ARMOR]; // value da 0 a 100
    buyable guns[N_GUNS]; // values PISTOL, SHOTGUN, 
public:
    menu();
    void open(int totLvl, int* currentLvl);
    ~menu();
};












#endif // MENU_HPP