#ifndef LIB_HPP
#define LIB_HPP

#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

// colori da 8 a 255 (i colori 0-7 sono predefiniti ma modificabili)
#define COLOR_PLAYER 8
#define COLOR_ENEMY 9
#define COLOR_COIN 10
#define COLOR_PLATFORM 11
#define COLOR_HP 12
#define COLOR_DARK 13
#define COLOR_TITLE 14
#define COLOR_SELECTED 15
#define COLOR_ERROR 16
#define COLOR_CHOSEN 17

// palette da 1 a 255
#define PAINT_DEFAULT 1
#define PAINT_DAMAGE 2
#define PAINT_PLAYER 3
#define PAINT_ENEMY 4
#define PAINT_COIN 5
#define PAINT_PLATFORM 6
#define PAINT_HP 7
#define PAINT_ARMOR 8
#define PAINT_BACKGROUND 9
#define PAINT_TITLE 10
#define PAINT_SELECTION 11
#define PAINT_ERROR 12
#define PAINT_CHOSEN 13

// altezza resource bar
#define WIN_HEIGHT 9
// posizione del titolo
#define X_OFFSET COLS/2-64
#define Y_OFFSET 4
// death animation timeSpan
#define DEATH_TIMESPAN 2

typedef double timeSpan;

void init();

struct point {
	int x;
	int y;
};

struct vector {
	double x;
	double y;
};

struct hitBox {
	point a; // top left
	point b; // bottom right
};
/*		A---+
		|   |
		|   |
		+---B
*/

bool collisionHH(hitBox, hitBox);
bool collisionHP(hitBox, point);
bool collisionHV(hitBox, vector);
bool collisionPP(point, point);

bool isTouching (hitBox v1, hitBox v2, char d);

point snap(vector);
int random(int min, int max);
vector randVector();

void posPrintW(point, const char*);
void posPrintW(point, char);

void printBackground(int lvl);

void printResourceBar(WINDOW* w, int health, double armor, int money, int points, int level, int difficulty);

#endif //LIB_HPP