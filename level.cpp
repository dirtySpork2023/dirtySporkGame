#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <stdlib.h>

#include "level.hpp"
using namespace std;

// Funzione per generare una piattaforma casuale all'interno di un'area definita da w
hitBox newRandomPlat (hitBox w, int de) {
    hitBox nw;
    nw.a.x = w.a.x + (rand()%5);     
    nw.a.y = w.a.y + (rand()%4);
    nw.b.x = nw.a.x + (15 + rand()%(35 - 12));    //(nw.a.x + 2) + (rand()%(w.b.x - nw.a.x - 6));  8 + rand()%(w.b.x - nw.a.x - 8)
    nw.b.y = nw.a.y + 1;

    return nw; 
}

// Funzione che genera una lista di n piattaforme in modo ricorsivo
lPlatform createnPlat (int np, hitBox ht, int len, int d) {
    if (np > 0) {
        lPlatform tmp1 = new Pplatform;
        /*
        tmp1->plat = new platform(ht.a.x, ht.a.y, ht.b.x, ht.b.y);
        ht.a.x += 7;
        ht.b.x += 7;
        */
        hitBox hpl = newRandomPlat (ht, d);
        tmp1->plat = new platform(hpl.a.x, hpl.a.y, hpl.b.x, hpl.b.y);
        ht.a.x += len;
        ht.b.x += len;
        tmp1->next = createnPlat (np-1, ht, len, d);
        return tmp1;
    } else return NULL;
}

level::level (int nl, bulletManager* B) {

    //generazione piattaforme inferiori
    this->nlevel = nl;                      // Assegno il numero del livello 
    int numPlatinf = (rand()%3) + 2;        // Genero un valore fra 2 e 4 che rappresenta il numero di piattaforme inferiori in quel livello
    int leninf = (COLS-10) / numPlatinf;    // Larghezza massima delle piattaforme in base al loro numero
    int blevel = LINES - 10;
    int heightinf = blevel - 7;             // Altezza massima delle piattaforme fissata alla massima capacità di salto del player
    hitBox p1;                              // Hitbox della prima piattaforma
    p1.a.x = 8;                             // valore arbitrario di distanza da tenere dal lato sinistro
    p1.a.y = heightinf - 4;
    p1.b.x = leninf + 5;
    p1.b.y = heightinf;                            // base - altezza del player
    int dens = 8 - numPlatinf;

    
    this->platforms = new Pplatform;
    this->platforms->plat = new platform (-10, blevel, COLS+10, blevel + 1);           // Base del livello
    this->platforms->next = new Pplatform;
    lPlatform bs = this->platforms->next;
    bs->plat = new platform (0, 8, 2, blevel - 3);                      // Parete sinistra
    bs->next = new Pplatform; 
    bs = bs->next;
    bs->plat = new platform (COLS-2, 8, COLS, blevel - 3);              // Parete destra
    bs->next = new Pplatform;
    bs = bs->next;
    bs->plat = new platform (-1, LINES-8, 0, blevel);               // Porta sinistra
    bs->next = new Pplatform; 
    bs = bs->next;
    bs->plat = new platform (COLS, LINES-8, COLS+1, blevel);         // Porta destra
    
    bs->next = createnPlat (numPlatinf, p1, leninf, dens);


    // generazione piattaforme superiori
    int numPlatsup = (rand()%3) + 2;
    int lensup = (COLS-10) / numPlatsup;
    int heightsup = heightinf - 10;                   
    p1.a.x = 8; 
    p1.a.y = heightsup - 2;
    p1.b.x = lensup + 5;
    p1.b.y = heightsup;
    dens = 12 - numPlatsup;
    
    lPlatform tmp = this->platforms;
    while (tmp->next != NULL) {
	    tmp = tmp->next;
	}  
    tmp->next = createnPlat (numPlatsup, p1, lensup, dens);

    /*
    for (int i=0; i<numPlat; i++) {
        tmp1 = new Pplatform;
        //hitBox nw = newRandomPlat(p1);
        tmp1->plat = new platform(nw.a.x, nw.a.y, nw.b.x, nw.b.y);
        tmp1 = tmp1->next;
        nw.a.x += 7;
        nw.b.x += 7;
    }

    tmp1 = NULL;
    //delete tmp1;
    */
/*
    Da migliorare:::

    // Generazione lista nemici per il livello
    this->enemies = new lEnemies;
    lEnemies tmp2 = enemies;
    for (int i=0; i<2; i++) {
        if (i<1) {
            tmp2->ent = new kuba(80, 10, &this, &B);
            tmp2->type = 'k';
        } else {
            tmp2->ent = new shooter(120, 10, &this, &B);
            tmp2->type = 's';
        }
        tmp2=tmp2->next;
    }
    tmp2 = NULL;
    delete tmp2;
*/
}

/*
void level::setNext(level* l){ 
    this->next = l; 
}
*/

void level::print_platforms () {
    lPlatform tmp = this->platforms;
    tmp->plat->printc('"');                 // stampa della base
    tmp = tmp->next;

    for (int i = 0; i < 4 && tmp != NULL; i++) {          // Stampa delle pareti
        tmp->plat->printc('|');
	    tmp = tmp->next;
    }

    while (tmp != NULL) {                   // Stampa delle piattaforme sospese
        tmp->plat->printp();
	    tmp = tmp->next;
	}
    tmp = NULL;
    delete tmp;
}

infoCrash level::check (hitBox ch, char d) {
    infoCrash info;      // Variabile da restituire                             
    bool here = false;   // True se trovo qualcosa                                   
    int j;               // Contatore per sapere la posizione in lista
    hitBox r;

    lPlatform tmp1 = this->platforms;
    
    if (d == 'a') {
        for (j=0; tmp1 != NULL && !here; j++) {             // Verifico se c'e contatto con una piattaforma
            here = isTouchingA (tmp1->plat->getHitbox(), ch);
            tmp1 = tmp1->next;
        }
        
        if (here) {
            info.i = j;
            info.type = 'p';
        } else {
            // enemies
        }

    } else if (d == 'd') {
        for (j=0; tmp1 != NULL && here == false; j++) {
            here = isTouchingD (tmp1->plat->getHitbox(), ch);
            tmp1 = tmp1->next;
        }
        
        if (here) {
            info.i = j;
            info.type = 'p';
        } else {

        }
    } else if (d == 'w') {
        for (j=0; tmp1 != NULL && here == false; j++) {
            here = isTouchingW (tmp1->plat->getHitbox(), ch);
            tmp1 = tmp1->next;
        }
        
        if (here) {
            info.i = j;
            info.type = 'p';
        } else {

        }
        
    } else if (d == 's') {
        for (j=0; tmp1 != NULL && here == false; j++) {
            here = isTouchingS (tmp1->plat->getHitbox(), ch);
            tmp1 = tmp1->next;
        }
        
        if (here) {
            info.i = j;
            info.type = 'p';
        } else {

        }

    }

    tmp1 = NULL;
    delete tmp1;

/*
    Da migliorare :::

    // Controllo nemici
    lEnemies tmp2 = this->enemies;
    for (j=0; tmp2 != NULL && here == false; j++) {
        r = tmp2->ent.getHitBox;
        if (d == 'a') {
            if (whereIsY (r, ch) == 3 && r.b.x == ch.a.x-1) {
                info.type = 'k';
                info.i = j;
                here = true;
            }
        } else if (d == 'd') {
            if (whereIsY (r, ch) == 3 && r.a.x == ch.b.x+1) {
                info.type = 'k';
                info.i = j;
                here = true;
            }
        } else if (d == 'w') {
            if (whereIsX (r, ch) == 3 && r.b.y == ch.a.y+1) {
                info.type = 'k';
                info.i = j;
                here = true;                
            } 
        } else if (d == 's') {
            if (whereIsX (r, ch) == 3 && r.a.y == ch.b.y-1) {
                info.type = 'k';
                info.i = j;
                here = true;
            }
        }
        tmp2 = tmp->next;
    }
    delete tmp2;
*/ 
    /* 
    
    Controllo powerups ...
    
    */

   if (!here) {
    info.type = 'n';
    info.i = -1;
   }

   return info;
}

int level::number () {
    return this->nlevel;
}

int level::givenplat () {
    lPlatform tmp = this->platforms;
    int k=0;
    while (tmp != NULL) {
        k++;
        tmp = tmp->next;
    }
    return k;
    tmp = NULL;
    delete tmp;
}

hitBox level::coordinate(int i) {
    lPlatform tmp = this->platforms;
    int k=0;
    while (tmp != NULL && k<i) {
        k++;
        tmp = tmp->next;
    }
    hitBox ht = tmp->plat->getHitbox();
    tmp = NULL;
    delete tmp;

    return ht;
}
