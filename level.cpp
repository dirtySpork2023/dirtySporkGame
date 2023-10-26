#include <ncurses.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <stdlib.h>
#include "lib.hpp"
#include "level.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"
#include "kuba.hpp"
#include "player.hpp"
#include "shooter.hpp"
#include "platform.hpp"
using namespace std;

// Funzione per generare una piattaforma casuale all'interno di un'area definita da w
hitBox newRandomPlat (hitBox w) {
    hitBox nw;
    nw.a.x = w.a.x + rand()%(w.a.x + 8);     
    nw.a.y = w.a.y + rand()%(w.a.y + 4);
    nw.b.x = nw.b.x + 3 + rand()%(w.b.x);
    nw.b.y = nw.b.y + 3 + rand()%(w.b.y);                      

    return nw; 
}

// Funzione che genera una lista di n piattaforme in modo ricorsivo
lPlatform createnPlat (int np, hitBox ht, int len) {
    if (np > 0) {
        lPlatform tmp1 = new Pplatform;
        /*
        tmp1->plat = new platform(ht.a.x, ht.a.y, ht.b.x, ht.b.y);
        ht.a.x += 7;
        ht.b.x += 7;
        */
        hitBox hpl = newRandomPlat (ht);
        tmp1->plat = new platform(hpl.a.x, hpl.a.y, hpl.b.x, hpl.b.y);
        ht.a.x += len;
        ht.b.x += len;
        tmp1->next = createnPlat (np-1, ht, len);
        return tmp1;
    } else return NULL;
}

level::level (int nl, bulletManager* B) {
    this->nlevel = nl;                 // Assegno il numero del livello 
    int numPlat = rand()%(6-3) + 3;    // Genero un valore fra 3 e 6 che rappresenta il numero di piattaforme in quel livello
    int len = (COLS-3) / numPlat;      // Larghezza massima delle piattaforme in base al loro numero
    int height = 12;                   // Altezza massima delle piattaforme fissata alla massima capacità di salto del player
    hitBox p1;                         // Hitbox della prima piattaforma
    p1.a.x = 3;                        // valore arbitrario di distanza da tenere dal lato sinistro
    p1.a.y = height;
    p1.b.x = len;
    p1.b.y = 3;                       // altezza del player
    
    // Generazione lista di piattaforme per questo livello.
    this->platforms = new Pplatform;
    this->platforms->plat = new platform (0, 32, COLS, 34);  // Base del livello     
    //lPlatform tmp1 = this->platforms->next;
    hitBox nw;
    nw.a.x = 20;
    nw.a.y = 18;
    nw.b.x = 22;
    nw.b.y = 20;
    this->platforms->next = createnPlat (numPlat, nw, len);

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
    while (tmp != NULL) {
        tmp->plat->print();
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
    
    // Controllo piattaforme
    lPlatform tmp1 = this->platforms;
    for (j=0; tmp1 != NULL && here == false; j++) {
        r = tmp1->plat->getHitbox();
        if (d == 'a') {
            if (whereIsY (r, ch) == 3 && r.b.x == ch.a.x-1) {
                info.type = 'p';
                info.i = j;
                here = true;
            }
        } else if (d == 'd') {
            if (whereIsY (r, ch) == 3 && r.a.x == ch.b.x+1) {
                info.type = 'p';
                info.i= j;
                here = true;
            }
        } else if (d == 'w') {
            if (whereIsX (r, ch) == 3 && r.b.y == ch.a.y+1) {
                info.type = 'p';
                info.i = j;
                here = true;                
            } 
        } else if (d == 's') {
            if (whereIsX (r, ch) == 3 && r.a.y == ch.b.y-1) {
                info.type = 'p';
                info.i = j;
                here = true;
            }
        }
        tmp1 = tmp1->next;
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
}
