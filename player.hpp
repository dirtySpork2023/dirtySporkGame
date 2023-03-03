#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "lib.hpp"
#include "entity.hpp"
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

class player: public entity {
protected:
	double jumpSpeed;
	bool facingRight;
	double fireRate;
	int dmg; // danno di ogni proiettile
	double elapsedSinceLastShot; // in secondi
	//float elapsedSinceLastDamage;

public:
	player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, int health, float jumpHeight);
	void print();
	void update(char input, double deltaTime);
	void shoot();
};

#endif //PLAYER_HPP