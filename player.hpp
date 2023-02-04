#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "lib.hpp"
#include "bullet.hpp"

class player{
private:
	int hp ;
	point pos ; // relativa alla casella centrale, torso
	double ySpeed ; // velocità verticale
	double yMod ; // parte decimale di pos.y
	bool isGrounded; // true se il player è sopra qualcosa di solido
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
	bool facing; //true==destra / false==sinistra
	bulletManager* bM;
	double fireRate; // proiettili massimi al secondo
	int damage;
	double elapsedSinceLastShot; // secondi

public:
	player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, int health) ;
	void print() ;
	void update(char input, long int deltaTime) ;
	void shoot(long int deltaTime) ;
	bool hurt(int value);
	int getHealth();
	point getPos();
	hitBox getHitBox();
	void setGrounded(bool playerGrounded);
};

#endif //PLAYER_HPP