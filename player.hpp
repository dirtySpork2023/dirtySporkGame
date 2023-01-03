#include "bullet.hpp"


struct point {
	int x ;
	int y ;
};
struct hitBox {
	point a ; // top left
	point b ; // bottom right
};


class player{
public:
	point pos ; // relativa alla casella centrale, torso
	double ySpeed ;
	double yMod ;
	hitBox box ;
	char texture[3][3] = {
			{'_','p',' '},
			{'>','W','"'},
			{'/','"','\\'},
	};
	char reverse[3][3] = {
			{' ','q','_'},
			{'"','W','<'},
			{'/','"','\\'},
	};
	bool facing ; //true = detra / false = sinistra
	bullet B ;

public:
	player(int x, int y) ;
	void print() ;
	void move(char input, long int deltaTime) ;
};
