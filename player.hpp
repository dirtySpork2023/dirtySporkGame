#include "lib.hpp"
#include "bullet.hpp"

class player{
public:
	point pos ; // relativa alla casella centrale, torso
	double ySpeed ;
	double yMod ;
	hitBox box ;
	char texture[3][3] = {
			{' ','p',' '},
			{'>','W','='},
			{'/','"','\\'},
	};
	char reverse[3][3] = {
			{' ','q',' '},
			{'=','W','<'},
			{'/','"','\\'},
	};
	bool facing ; //true = destra / false = sinistra
	bullet B ;

public:
	player(int x, int y) ;
	void print() ;
	void move(char input, long int deltaTime) ;
	void shoot(bool input, long int deltaTime) ;
};
