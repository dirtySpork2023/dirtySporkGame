#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "lib.hpp"
#include "bulletManager.hpp"

#define GRAVITY 175

// sente la gravità ma non può saltare.
class entity {
protected:
	hitBox box;
	int health;
	bulletManager* bM;
	double ySpeed; // velocità verticale
	double yMod; // parte decimale della posizione in verticale
	bool isGrounded; // true se il player è sopra qualcosa di solido ( => non sta cadendo <=> può saltare)

	void applyGravity(timeSpan deltaTime);
	void move(char input);

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