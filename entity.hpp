#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "lib.hpp"
#include "bulletManager.hpp"

#define GRAVITY 175

class entity {
protected:
	hitBox box;
	int health;
	timeSpan lastDamage; // time in seconds elapsed since entity was hurt
	bulletManager* bM;
	double ySpeed; // velocità verticale
	double yMod; // parte decimale della posizione in verticale
	bool isGrounded; // true se il player è sopra qualcosa di solido ( => non sta cadendo <=> può saltare)

	void applyGravity(timeSpan deltaTime);
	void move(char input);
	void setPrintColor();

public:
	entity(int x, int y, int hp, bulletManager* bM);
	void update(timeSpan deltaTime);
	point getPos();
	hitBox getHitBox();
	int getHealth();
	bool hurt(int value);
	void setGrounded(bool grounded);
	~entity();
};

#endif //ENTITY_HPP