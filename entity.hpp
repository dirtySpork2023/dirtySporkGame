#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "lib.hpp"
#include "bulletManager.hpp"
#include "level.hpp"

#define ENTITY_G 175
#define DAMAGE_TIMESPAN 0.10

class entity {
protected:
	hitBox box;
	int health;
	timeSpan lastDamage; // time in seconds elapsed since entity was hurt
	bulletManager* bM;
	level* lM;
	double ySpeed; // velocità verticale
	double yMod; // parte decimale della posizione in verticale
	bool isGrounded; // true se il player è sopra qualcosa di solido ( => non sta cadendo <=> può saltare)

	void applyGravity(timeSpan deltaTime);
	void move(char input);
	void setPrintColor(int paint = PAINT_DEFAULT);

public:
	entity(int x, int y, level* l, bulletManager* b, int hp);
	void update(timeSpan deltaTime);
	point getPos();
	hitBox getHitBox();
	int getHealth();
	bool hurt(int value);
	void setGrounded(bool grounded);
	~entity();
};

#endif //ENTITY_HPP