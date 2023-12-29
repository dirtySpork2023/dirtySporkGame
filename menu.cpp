#include "menu.hpp"

bool addLife (player* P) {
    if (P->getHealth() >= 100) return false;
    else {
        P->hurt(-10);
        return true;
    }
}

menu::menu(){
    this->win = newwin(HEIGHT, WIDTH, 10, (COLS-WIDTH)/2);
    selected = 0;

    currArmor = 0;
    for(int i=0; i<N_ARMOR; i++){
        armor[i].cost = i*50;
    }
    armor[0].value = 5;
    armor[1].value = 35;
    armor[2].value = 60;
    armor[3].value = 80;
    armor[4].value = 90;
    armor[5].value = 95;

    currGun = 0;
    for(int i=0; i<N_GUNS; i++){
        gun[i].value = i;
        gun[i].cost = i*50;
    }

    
}

// RIPRENDI
// MERCATO
// - ARMA <SHOTGUN> per 2$
// - AGGIUNGI HP per 2$
// - AUMENTA ARMATURA a <70%> per 5$
// LIVELLO <numL>

void menu::update(char input, int &numL, int totLvl){
    if(input=='w' || input=='W' || input==KEY_UP){
        selected--;
    } 
    if(input=='s' || input=='S' || input==KEY_DOWN){
        selected++;
    }

    if( selected<0 ) selected = N_OPTIONS;
    if( selected>N_OPTIONS ) selected = 0;

    if( selected==1 && input=='a' && numL>1){
        numL--;
    }
    if( selected==1 && input=='d' && numL<totLvl){
        numL++;
    }
    if( selected==2 ){
        
    }
    if( selected==3 ){
        
    }
    if( selected==4 ){
        
    }
}

void menu::print(int numL){
    box(win, 0, 0);
    int y = 2;

    option(0, y++, "RIPRENDI");
    y++;
    option(1, y++, "LIVELLO");
    wprintw(win, " <%d> ", numL);
    y++;
    mvwprintw(win, 3, y++, "MERCATO");
    option(2, y++, "- ARMA");
        wprintw(win, " <%d> per %d$", gun[currGun].value, gun[currGun].cost);
    option(3, y++, "- AGGIUNGI");
        wprintw(win, " 10 HP per 10$");
    option(4, y++, "- ARMATURA");
        wprintw(win, " <%d%> per %d$", armor[currArmor].value, armor[currArmor].cost);
    
    wrefresh(win);
}

void menu::option(int index, int y, const char* text){
    if( index==selected ) wattron(win, A_REVERSE);

    mvwprintw(win, y, 4, text);

    wattroff(win, A_REVERSE);
}

menu::~menu(){
    delwin(win);
}