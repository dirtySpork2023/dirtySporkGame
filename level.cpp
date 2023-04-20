#include <ncurses.h>
#include "lib.hpp"
#include "level.hpp"
#include "bulletManager.hpp"
#include "entity.hpp"
#include "kuba.hpp"
#include "player.hpp"
#include "platform.hpp"


level::level (int nl, bulletManager B) {
    this->nlevel = nl;                // Assegno il numero del livello 
    int numPlat = 3 + rand()%6;       // Genero un valore fra 3 e 6 che rappresenta il numero di piattaforme in quel livello
    int len = COLS-3 / numPlat;       // Larghezza massima delle piattaforme in base al loro numero
    int height = 12;                  // Altezza massima delle piattaforme fissata alla massima capacità di salto del player
    hitBox p1;                        // Hitbox della prima piattaforma
    p1.a.x = 3;                       // valore arbitrario di distanza da tenere dal lato sinistro
    p1.a.y = height;
    p2.b.x = len;
    p2.b.y = 3;                       // altezza del player

    // Generazione lista di piattaforme per questo livello.
    this->plat = new lPlatforms;
    this->plat->pl = platform (0, 1, COLS, 0);        // Base del livello
    lPlatforms tmp1 = this->plat->next;
    for (int i=0; i<numPlat; i++) {
        tmp1->pl = randomPlat(p1);
        tmp1 = tmp1->next;
        p1.a.x += len;
        p1.b.x += len;
    }
    tmp1 = NULL;
    delete tmp1;

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
}

 void level::print_platforms () {
    lPlatforms tmp = this->plat;
    while (tmp != NULL) {
		tmp->pl.print();
		tmp = tmp->next;   
	}
    delete tmp;
 }

infoCrash level::check (hitBox ch, char d) {
    infoCrash info;      // Variabile da restituire                             
    bool here = false;   // True se trovo qualcosa                                   
    int j;               // Contatore per sapere la posizione in lista
    hitBox r;
    
    // Controllo piattaforme
    lPlatforms tmp1 = this->plat;
    for (j=0; tmp1 != NULL && here == false; j++) {
        r = tmp1->pl.getHitbox();
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
    delete tmp1;

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

    /* 
    
    Controllo powerups ...
    
    */

   if (!here) {
    info.tipe = 'n';
    info.i = -1;
   }

   return info;
}

int level::lnumber () {
    return this->nlevel;
}
