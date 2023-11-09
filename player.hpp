#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "lib.hpp"
#include "bulletManager.hpp"

#include "shooter.hpp"

class level;

#define MAX_HEALTH 100
#define HEALTH_BAR_LENGTH 20
#define PISTOL 0
#define SHOTGUN 1
#define RIFLE 2

class player: public shooter {
protected:
	float armor; // 0-1 moltiplica i danni subiti
	double jumpSpeed;

public:
	player(int x, int y, level* lvl, bulletManager* b, int weapon, float jumpHeight, float armor);
	void update(char input, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	bool hurt(int value);
	void shoot();
	void setGun(int id);
};

#endif //PLAYER_HPP
