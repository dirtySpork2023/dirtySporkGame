#ifndef LIB_HPP
#define LIB_HPP

#include <ncurses.h>

// colori da 8 a 255 (i colori 0-7 sono predefiniti ma modificabili)
#define COLOR_PLAYER 8
#define COLOR_ENEMY 9
#define COLOR_COIN 10
#define COLOR_PLATFORM 11
#define COLOR_HP 12
#define COLOR_DARK 13
#define COLOR_TITLE 14

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

#define WIN_HEIGHT 9
#define WIN_OFFSET COLS/2-50
#define X_OFFSET COLS/2-64
#define Y_OFFSET 4

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
vector randVector();

void posPrintW(point, const char*);
void posPrintW(point, char);

bool upperCase(char c);

void titleScreen();

void printResourceBarLow(WINDOW* w, int health, double armor, int money);
void printResourceBar(WINDOW* w, int health, double armor, int money, int level, int difficulty);

#endif //LIB_HPP