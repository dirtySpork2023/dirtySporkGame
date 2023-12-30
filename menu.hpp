#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include "lib.hpp"
#include "player.hpp"

#define HEIGHT 12
#define WIDTH 50
#define SELECT_TIMESPAN 0.1


#define N_ARMOR 6
#define N_GUNS 3
#define N_OPTIONS 4

//value dipende dall'oggetto
//cost è zero quando l'oggetto è già acquistato
struct buyable{
    int value;
    int cost;
};

class menu {
protected:
    WINDOW* win;
    int selected;
    buyable armor[N_ARMOR]; // value da 0 a 100
    buyable gun[N_GUNS]; // values PISTOL, SHOTGUN, RIFLE
    buyable heal;
    int currArmor;
    int currGun;
    int currHeal;
    bool error;
    timeSpan lastSelect;

    void printOption(int index, int y, const char* text);
    const char* gunName(int id);
public:
    menu();
    bool update(char input, int &money, int &numL, int totLvl, player* P, timeSpan deltaTime);
    void updateScroll(char type, buyable b[], int size, int &curr, char input, int &money, player* P);
    void print(int numL);
    ~menu();
};

#endif // MENU_HPP