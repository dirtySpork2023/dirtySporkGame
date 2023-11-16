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

// Stampa della piattaforma
void platform::printp () {
    attrset(COLOR_PAIR(PAINT_PLATFORM));
    mvprintw(this->box.a.y, this->box.a.x, "|");
    mvprintw(this->box.a.y, this->box.b.x, "|");
    for (int j=this->box.a.x+1; j<=this->box.b.x-1; j++) {
        mvprintw(this->box.a.y, j, "\"");
    }

    mvprintw(this->box.b.y, this->box.a.x, "|");
    mvprintw(this->box.b.y, this->box.b.x, "|");
    for (int j=this->box.a.x+1; j<=this->box.b.x-1; j++) {
        mvprintw(this->box.b.y, j, "_");
    }
    attrset(COLOR_PAIR(PAINT_DEFAULT));
}

void platform::printc (char c) {
    attrset(COLOR_PAIR(PAINT_PLATFORM));
    for (int i = this->box.a.x; i < this->box.b.x; i++) {
        for (int j = this->box.a.y; j < this->box.b.y; j++) {
            mvprintw(j, i, "%c", c);
        }
    }
    attrset(COLOR_PAIR(PAINT_DEFAULT));
}


hitBox platform::getHitbox() {
    return this->box;
}