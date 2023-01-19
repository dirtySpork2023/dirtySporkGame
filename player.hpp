#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "lib.hpp"
#include "bullet.hpp"

class player{
public:
	int hp ;
	point pos ; // relativa alla casella centrale, torso
	double ySpeed ; // velocità verticale
	double yMod ; // parte decimale di pos.y
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
	bool facing; //true = destra / false = sinistra
	bullet B;
	double fireRate; // proiettili massimi al secondo
	int damage;

public:
	player(int x, int y, double gunFireRate, int gunDamage, int health) ;
	void print() ;
	void move(char input, long int deltaTime) ;
	void shoot(bool input, long int deltaTime) ;
	int checkCollisions(hitBox enemy);
	int getHealth();
};

#endif //PLAYER_HPP