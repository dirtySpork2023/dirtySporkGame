#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "lib.hpp"
#include "bulletManager.hpp"

const char texture[3][3] = {
	{' ','p',' '},
	{'>','W','='},
	{'/','"','\\'},
};
const char reverse[3][3] = {
	{' ','q',' '},
	{'=','W','<'},
	{'/','"','\\'},
};

class player{
private:
	int hp; //health points
	point pos; // posizione relativa alla casella centrale, torso
	double ySpeed; // velocità verticale
	double yMod; // parte decimale di pos.y
	bool isGrounded; // true se il player è sopra qualcosa di solido ( ==> può saltare)
	double jumpSpeed;
	hitBox box;
	bool facingRight;
	bulletManager* bM;
	double fireRate;
	int dmg; // danno di ogni proiettile
	double elapsedSinceLastShot; // tempo in secondi
	//void kill(); //WIP

public:
	player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, int health, float jumpHeight);
	void print();
	void update(char input, double deltaTime);
	void shoot();
	bool hurt(int value);
	int getHealth();
	point getPos();
	void moveTmp(int height);
	hitBox getHitBox();
	void setGrounded(bool playerGrounded);
};

#endif //PLAYER_HPP