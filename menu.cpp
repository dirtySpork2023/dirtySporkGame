#include <ncurses.h>
#include <string>

#include "menu.hpp"

using namespace std;

bool addLife (player* P) {
    if (P->getHealth() >= 100) return false;
    else {
        //P->hurt(-int);
        return true;
    }
}

int changeLevel (int totLvl, WINDOW* win) {
    clear();
    wclear(win);
    wrefresh(win);
    box(win, 0, 0);
    int i = 1;
    int choice = 0;

    mvwprintw(win, 1, WIDTH/2-6, "CAMBIO LIVELLO");
    mvwprintw(win, 4, 1, "Livello da raggiungere -> ");

    wattron(win, A_REVERSE);
    while (choice != 10) {
        mvwprintw(win, 4, 27, "%d", i);
        choice = wgetch(win);
        if (choice == KEY_UP) {
            if (i == 1) i = totLvl;
            else i--;
        } else if (choice == KEY_DOWN) {
            if (i == totLvl) i = 1;
            else i++;
        }
        wrefresh(win);
    }
    wattroff(win, A_REVERSE);
    return i;
}

void market () {

}

menu::menu(){

    for(int i=0; i<N_ARMOR; i++){
        armor[i].cost = i*35;
        armor[i].value = i*20-5;
    }
    for(int i=0; i<N_GUNS; i++){
        gun[i].value = i;
        gun[i].cost = i*50;
    }
}

void menu::open(int totLvl, int* currentLvl){
    win = newwin(HEIGHT, WIDTH, 6, COLS/2-WIDTH/2);

    box(win, 0, 0);
    keypad(win, true);

    mvwprintw(win, 1, WIDTH/2, "MENU");
    
    bool close = false;
    string choices[3] = {"Riprendi", "Cambia livello", "Mercato"};
    int choice, highlight = 0;

    // Menu principale
    while (!close) {
        while (choice != 10) {      // choice =! 'invio'
            for(int i=0; i<3; i++) {
                if (i == highlight) {
                    wattron(win, A_REVERSE);
                    mvwprintw(win, i+3, 1, choices[i].c_str());
                } else mvwprintw(win, i+3, 1, choices[i].c_str());
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
        }

        if (highlight == 0) close = true;
        else if (highlight == 1) {
           *currentLvl = changeLevel(totLvl, win);
           close = true;
        } //else if (highlight == 2) market();

        wrefresh(win);
    }
    delwin(win);

}

menu::~menu(){
    delwin(win);
}