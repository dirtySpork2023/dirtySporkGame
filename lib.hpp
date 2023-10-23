#ifndef LIB_HPP
#define LIB_HPP

// colori da 8 a 255 (i colori 0-7 sono predefiniti ma modificabili)
#define COLOR_PLAYER 8
#define COLOR_ENEMY 9

// palette da 1 a 255
#define PAINT_DEFAULT 1
#define PAINT_DAMAGE 2
#define PAINT_PLAYER 3
#define PAINT_ENEMY 4

typedef double timeSpan;

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
int whereIsY (hitBox v1, hitBox v2);
int whereIsX (hitBox v1, hitBox v2);

#endif //LIB_HPP