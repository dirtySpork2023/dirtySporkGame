#include "menu.hpp"

using namespace std;

menu::menu(){

    for(int i=0; i<N_ARMOR; i++){
        armor[i].cost = i*20;
    }
    armor[0].value = 5;
    armor[1].value = 35;
    armor[2].value = 60;
    armor[3].value = 80;
    armor[4].value = 90;
    armor[5].value = 95;
    
    this->armorIndex = 1;
    
    for (int i=0; i<N_GUNS; i++) gun[i] = i*25;
}

bool menu::addLife (player* P, int hp) {
    if (P->getHealth() >= 100) return false;
    else {
        P->heal(hp);
        return true;
    }
}

void menu::changeGun(player* P, int* money){
    clear();
    wclear(win);
    wrefresh(win);
    box(win, 0, 0);
    int choice = 0; 
    bool close = false;
    int highlight = 0;
    string choices[3] = {"Pistol", "Shotgun", "Rifle"};

    mvwprintw(win, 1, WIDTH/2-5, "CAMBIO ARMA");
    
    while (!close) {      // choice =! 'invio'
        for(int i=0; i<3; i++) {
            if (i == highlight) wattron(win, A_REVERSE);
            mvwprintw(win, i+4, 1, "%s - costo: %d$  ", choices[i].c_str(), gun[i]);
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        if (choice == KEY_UP) {
            if (highlight == 0) highlight = 2;
            else highlight--;
        } else if (choice == KEY_DOWN) {
            if (highlight == 2) highlight = 0;
            else highlight++;
        }
        
        if (choice== 10 && *money >= gun[highlight]) {
            P->setGun(highlight);
            *money -= gun[highlight];
            gun[highlight] = 0;
            close =  true;
        }
        wrefresh(win);
    }
    
}

int menu::open() {
    this->win = newwin(HEIGHT, WIDTH, 9, COLS/2-WIDTH/2);

    box(this->win, 0, 0);
    keypad(this->win, true);

    mvwprintw(this->win, 1, WIDTH/2-2, "MENU");
    
    bool close = false;
    string choices[3] = {"Riprendi", "Cambia livello", "Mercato"};
    int choice = 0;
    int highlight = 0;

    while (choice != 10 && choice != 'm') {      // choice =! 'invio'
        for(int i=0; i<3; i++) {
            if (i == highlight) wattron(this->win, A_REVERSE);
            mvwprintw(this->win, i+4, 1, "%s", choices[i].c_str());
            wattroff(this->win, A_REVERSE);
        }
        choice = wgetch(this->win);

        if (choice == KEY_UP ) {
            if (highlight == 0) highlight = 2;
            else highlight--;
        } else if (choice == KEY_DOWN) {
            if (highlight == 2) highlight = 0;
            else highlight++;
        }
        wrefresh(this->win);
    }

    if (highlight == 1) return 1;
    else if (highlight == 2) return 2;
    else return 0;
}

int menu::changeLevel (int totLvl) {
    wclear(this->win);
    wrefresh(this->win);
    box(this->win, 0, 0);
    int i = 1;
    int choice = 0;

    mvwprintw(this->win, 1, WIDTH/2-6, "CAMBIO LIVELLO");
    mvwprintw(this->win, 5, 1, "Livello da raggiungere -> ");

    wattron(this->win, A_REVERSE);
    while (choice != 10) {
        mvwprintw(this->win, 5, 27, "%d  ", i);
        choice = wgetch(this->win);
        if (choice == KEY_UP) {
            if (i == 1) i = totLvl;
            else i--;
        } else if (choice == KEY_DOWN) {
            if (i == totLvl) i = 1;
            else i++;
        }
        wrefresh(this->win);
    }
    wattroff(this->win, A_REVERSE);
    return i;
}

void menu::market (player* P, int* money, int* points, WINDOW* bottomWin) {
    wclear(this->win);
    wrefresh(this->win);
    int choice = 0;
    int highlight = 0;
    bool close = false;
    string choices[3] = {"Riprendi", "Cambia arma", "Aggiungi 10 hp - costo: 10$ "};

    while (!close) {
        mvwprintw(this->win, 1, WIDTH/2-3, "MERCATO");
        box(this->win, 0, 0);

        while (choice != 10) {      // choice =! 'invio'
            for(int i=0; i<4; i++) {
                if (i == highlight) wattron(this->win, A_REVERSE);
                if (i==3) mvwprintw(this->win, i+4, 1, "Aumenta armatura al %d%%- costo: %d$  ", armor[armorIndex].value, armor[armorIndex].cost);
                else mvwprintw(this->win, i+4, 1, "%s", choices[i].c_str());
                wattroff(this->win, A_REVERSE);
            }
            choice = wgetch(this->win);

            if (choice == KEY_UP) {
                if (highlight == 0) highlight = 3;
                else highlight--;
            } else if (choice == KEY_DOWN) {
                if (highlight == 3) highlight = 0;
                else highlight++;
            }
            wrefresh(win);
        }
        
        if (highlight==0) close = true;
        else if (highlight==1) {
            changeGun(P, money);
            highlight = 0;
            wclear(win);
        } else if (highlight==2) {
            if (*money >= 10) if (addLife (P,10)) *money-=10;
        } else if (*money >= armor[armorIndex].cost) {
            *money -= armor[armorIndex].cost;
            P->setArmor(this->armor[armorIndex].value);
            armor[armorIndex].cost = 0;
            this->armorIndex++;
        }
        printResourceBarLow(bottomWin, P->getHealth(), P->getArmor(), *money, *points);
        wrefresh(bottomWin);
        choice = 0;
        wrefresh(win);
    }
}

int menu::count () {
    int c = armorIndex;
    if(gun[1] == 0) c += 1;
    if(gun[2] == 0) c += 2;
    return c;
}