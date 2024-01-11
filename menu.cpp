#include "menu.hpp"

menu::menu(){
    win = newwin(HEIGHT, WIDTH, 10, (COLS-WIDTH)/2);
    selected = 0;
    lastSelect = SELECT_TIMESPAN;

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

    currHeal = 0;
    heal.value = 20;
    heal.cost = 5;
}

bool menu::update(char input, int &money, int &numL, int totLvl, player *P, timeSpan deltaTime){
    bool keepOpen = true;
    lastSelect += deltaTime;

    if( input=='w' && selected>0 )
        selected--;
    if( input=='s' && selected<N_OPTIONS )
        selected++;

    // RIPRENDI
    if( selected==0 && input=='f' )
        keepOpen = false;

    // LIVELLO
    if( selected==1 && input=='a' && numL>1 )
        numL--;
    if( selected==1 && input=='d' && numL<totLvl )
        numL++;
    if( selected==1 && input=='f' )
        keepOpen = false;

    if(selected==2)
        updateScroll('g', gun, N_GUNS, currGun,input, money, P);

    if( selected==3 )
        updateScroll('a', armor, N_ARMOR, currArmor, input, money, P);

    if( selected==4 )
        updateScroll('h', &heal, 1, currHeal, input, money, P);
    
    return keepOpen;
}

void menu::updateScroll(char type, buyable b[], int size, int &curr, char input, int &money, player* P){
    //if type = 'a'  b = *armor size=N_ARMORs blablabla
    // per togliere argomenti superflui

    if( input=='a' && curr>0)
        curr--;
    if( input=='d' && curr<size-1)
        curr++;
    if( input=='f'){
        lastSelect = 0;
        if(b[curr].cost<=money && (type!='h' || P->getHealth()<100)){
            money -= b[curr].cost;
            if(type=='g' || type=='a')
                b[curr].cost = 0;
            if(type=='g')
                P->setGun(b[curr].value);
            if(type=='h')
                P->heal(b[curr].value);
            if(type=='a')
                P->setArmor(b[curr].value);
            error = false;
        }else
            error = true;
    }
}

void menu::print(int numL){
    box(win, 0, 0);
    int y = 2;

    printOption(0, y++, "RIPRENDI");
    y++;
    printOption(1, y++, "LIVELLO");
        wprintw(win, " <%d> ", numL);
    y++;
    mvwprintw(win, y++, 8, "MERCATO");
    printOption(2, y++, "- ARMA");
        wprintw(win, " <%s> per %d$  ", gunName(currGun), gun[currGun].cost);
    printOption(3, y++, "- ARMATURA");
        wprintw(win, " <%d%> per %d$  ", armor[currArmor].value, armor[currArmor].cost);
    printOption(4, y++, "- AGGIUNGI");
        wprintw(win, " %d HP per %d$", heal.value, heal.cost);
    
    wrefresh(win);
}

void menu::printOption(int index, int y, const char* text){
    if( index==selected && lastSelect>SELECT_TIMESPAN){
        mvwprintw(win, y, 2, ">");
        wattrset(win, COLOR_PAIR(PAINT_SELECTION));
    }else if( index==selected && error==true){
        mvwprintw(win, y, 2, "X");
        wattrset(win, COLOR_PAIR(PAINT_ERROR));
    }else if( index==selected && error==false){
        mvwprintw(win, y, 2, "O");
        wattrset(win, COLOR_PAIR(PAINT_CHOSEN));
    }else{
        mvwprintw(win, y, 2, " ");
    }
    
    mvwprintw(win, y, 4, text);

    wattrset(win, COLOR_PAIR(PAINT_DEFAULT));
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