#include <ncurses.h>
#include "lib.hpp"
#include "platform.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

platform::platform(int x1, int y1, int x2, int y2) {
    this->box.a.x = x1;
    this->box.a.y = y1;
    this->box.b.x = x2;
    this->box.b.y = y2;
}

/*
void platform::setNext(platform p) {
    this->next = &p;
}
*/

/*
// Ritorna il puntatore alla piattaforma successiva;
platform* platform::getNext () {
    return (platform::next);
}
*/

// Stampa della piattaforma
void platform::print () {
    for (int i=this->box.a.x; i<this->box.b.x; i++) {
        for (int j=this->box.a.y; j<this->box.b.y; j++) {
            mvprintw(j, i, "#");
        }
    }
}

hitBox platform::getHitbox() {
    return this->box;
}
