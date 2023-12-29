#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include "player.hpp"
#include "lib.hpp"


#define HEIGHT (LINES-18)
#define WIDTH (COLS-75)

#define N_ARMOR 6
#define N_GUNS 3

//value dipende dall'oggetto
//cost è zero quando l'oggetto è già acquistato
struct buyable{
    int value;
    int cost;
};

bool addLife (player* P, int hp);
int changeGun (WINDOW* win);

class menu {
protected:
    WINDOW* win;
    buyable armor[N_ARMOR]; // value da 0 a 100
    buyable gun[N_GUNS]; // values PISTOL, SHOTGUN, RIFLE
    int armorIndex;
public:
    menu();
    int open();
    int changeLevel(int totLvl);
    void market(player* P, int* money, WINDOW* bottomWin);
    ~menu();
};












#endif // MENU_HPP