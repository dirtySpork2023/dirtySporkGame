#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "lib.hpp"
#include "entity.hpp"
#include "bulletManager.hpp"

#define HEALTH 100

class player: public entity {
protected:
	float armor; // 0-1 moltiplica i danni subiti
	double jumpSpeed;
	bool facingRight;
	double fireRate;
	int dmg; // danno di ogni proiettile

public:
	player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, float jumpHeight, float armor);
	void print(double deltaTime);
	void update(char input, double deltaTime);
	bool hurt(int value);
	void shoot();
};

#endif //PLAYER_HPP