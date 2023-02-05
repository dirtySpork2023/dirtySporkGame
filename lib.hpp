#ifndef LIB_HPP
#define LIB_HPP

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

#endif //LIB_HPP