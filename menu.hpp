#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include <string>
#include "player.hpp"
#include "lib.hpp"

#define HEIGHT 11 /*(LINES-18)*/
#define WIDTH 50 /*(COLS-75)*/

#define N_ARMOR 6
#define N_GUNS 3

//value dipende dall'oggetto
//cost è zero quando l'oggetto è già acquistato
struct buyable{
    int value;
    int cost;
};

class menu {
protected:
    WINDOW* win;
    buyable armor[N_ARMOR]; // value da 0 a 100
    int gun[N_GUNS];
    int armorIndex;
    bool addLife (player* P, int hp);
    void changeGun (player* P, int* money);
public:
    menu();
    int open();
    int changeLevel(int totLvl);
    void market(player* P, int* money, int* points, WINDOW* bottomWin);
    ~menu();
};

#endif // MENU_HPP