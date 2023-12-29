#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "lib.hpp"
#include "bulletManager.hpp"

#include "shooter.hpp"

class level;

#define MAX_HEALTH 100
#define PISTOL 0
#define SHOTGUN 1
#define RIFLE 2

class player: public shooter {
protected:
	double armor; // 0-1 riduce i danni subiti
	double jumpSpeed;
	int gunID;

public:
	player(int x, int y, level* lvl, int weapon, float jumpHeight, float armor);
	void update(char input, timeSpan deltaTime);
	void print(timeSpan deltaTime);
	bool hurt(int value);
	void shoot();
	void setGun(int id);
	void changeLevel(level* newLvl);
	double getArmor();
	void setArmor(double ar);
};

#endif //PLAYER_HPP
