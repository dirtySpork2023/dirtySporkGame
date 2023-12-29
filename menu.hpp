#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include "lib.hpp"
#include "player.hpp"

#define HEIGHT 12
#define WIDTH 50

#define N_ARMOR 6
#define N_GUNS 3
#define N_OPTIONS 4

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
    int selected;
    buyable armor[N_ARMOR]; // value da 0 a 100
    int currArmor;
    buyable gun[N_GUNS]; // values PISTOL, SHOTGUN, RIFLE
    int currGun;
    void option(int index, int y, const char* text);
public:
    menu();
    void update(char input, int &numL, int totLvl);
    void print(int numL);
    ~menu();
};












#endif // MENU_HPP