#include <ncurses.h>
#include "lib.hpp"
#include "platform.hpp"
#include stdlib.h
#include time.h

platform::platform(int x1, int y1, int x2, int y2) {
    this->box.a.x = x1;
    this->box.a.y = y1;
    this->box.b.x = x2;
    this->box.b.y = y2;
}

// Stampa della piattaforma
void platform::print () {
    for (int i=this->box.a.x; i<this->box.b.x; i++) {
        for (int j=this->box.a.y; j<this->box.b.y; j--) {
            mvprintw(j, i, "#");
        }
    }
}

// funzione per generare una piattaforma casuale all'interno di un'area definita da w
platform randomPlat (hitBox w, int nh) {
        
    int x1 = w.a.x + rand()%(w.b.x - 20);    // 20 e 15 sono valori arbitrari da sommare/sottrarre per far si che 
    int y1 = (w.b.y + 20) + rand()%(w.a.y);  // (x1,y1) sia in alto a sinistra e (x2,y2) in basso a destra.
    int x2 = (x1 + 15) + rand()%(w.b.x);
    int y2 = w.b.y + rand()%(y1 - 15);                      

    return platform(x1, y1, x2, y2); 
}

// Funzione che ritorna dove si trova in ALTEZZA v2 rispetto a v1
// 1: sopra || 2: sotto || 3: conincidono in quelche punto
int whereIsY (hitBox v1, hitBox v2) {
    int k;
    if (v2.a.y < v1.b.y) {
        k = 2;
    } else if (v2.b.y > v1.a.y) {
        k=1;
    } else k=3;

    return k;
}


// Funzione che ritorna dove si trova in LARGHEZZA v2 rispetto a v1
// 1: sinistra || 2: destra || 3: conincidono in quelche punto
int whereIsX (hitBox v1, hitBox v2) {
    int k;
    if (v2.b.x < v1.a.x) {
        k = 1;
    } else if (v2.a.x > v1.b.x) {
        k = 2;
    } else k = 3;

    return k;
}



