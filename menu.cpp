#include "menu.hpp"

menu::menu(){
    win = newwin(HEIGHT, WIDTH, 10, (COLS-WIDTH)/2);
    selected = 0;

    heal.value = 10;
    heal.cost = 10;

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

bool menu::update(char input, int &money, int &numL, int totLvl, player *P){
    bool keepOpen = true;
    if( input=='m' || input=='q' ) keepOpen = false;

    if( input=='w' )
        selected--;
    if( input=='s' )
        selected++;

    if( selected<0 ) selected = N_OPTIONS;
    if( selected>N_OPTIONS ) selected = 0;

    // RIPRENDI
    if( selected==0 && input=='f' )
        keepOpen = false;
    
    // LIVELLO
    if( selected==1 && input=='a' && numL>1)
        numL--;
    if( selected==1 && input=='d' && numL<totLvl)
        numL++;
    if( selected==1 && input=='f' )
        keepOpen = false;
    
    // GUN
    if( selected==2 && input=='a' && currGun>0)
        currGun--;
    if( selected==2 && input=='d' && currGun<N_GUNS-1)
        currGun++;
    if( selected==2 && input=='f'){
        //seleziona o compra currGun
        if(gun[currGun].cost<=money){
            money -= gun[currGun].cost;
            gun[currGun].cost = 0;
            P->setGun(gun[currGun].value);
        }else{
            //error animation ?
        }
    }

    // HEALTH
    if( selected==3 && input=='f' ){
        if( P->getHealth()<100 && money>=heal.cost ){
            P->heal(heal.value);
            money -= heal.cost;
        }else{
            //error animation ?
        }
    }

    // ARMOR
    if( selected==4 && input=='a' && currArmor>0)
        currArmor--;
    if( selected==4 && input=='d' && currArmor<N_ARMOR-1)
        currArmor++;
    if( selected==4 && input=='f'){
        //seleziona o compra currArmor
        if(armor[currArmor].cost<=money){
            money -= armor[currArmor].cost;
            armor[currArmor].cost = 0;
            P->setArmor(armor[currArmor].value);
        }
    }
    return keepOpen;
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
        wprintw(win, " <%s> per %d$  ", gunName(currGun), gun[currGun].cost);
    option(3, y++, "- AGGIUNGI");
        wprintw(win, " %d HP per %d$", heal.value, heal.cost);
    option(4, y++, "- ARMATURA");
        wprintw(win, " <%d%> per %d$  ", armor[currArmor].value, armor[currArmor].cost);
    
    wrefresh(win);
}

void menu::option(int index, int y, const char* text){
    if( index==selected ){
        mvwprintw(win, y, 2, ">");
        wattron(win, A_REVERSE);
    }else{
        mvwprintw(win, y, 2, " ");
    }
    
    mvwprintw(win, y, 4, text);

    wattroff(win, A_REVERSE);
}

const char* menu::gunName(int id){
    id = gun[id].value;
    if(id==0)
        return "PISTOL";
    else if(id==1)
        return "SHOTGUN";
    else if(id==2)
        return "RIFLE";
    else return "ERROR";
}

menu::~menu(){
    delwin(win);
}