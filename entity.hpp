#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "lib.hpp"
#include "bulletManager.hpp"

#define GRAVITY 175

// sente la gravità ma non può saltare.
class entity {
protected:
	point pos; // TODO remove pos and rewrite getPos()
	hitBox box;
	int hp;
	bulletManager* bM;
	double ySpeed; // velocità verticale
	double yMod; // parte decimale di pos.y
	bool isGrounded; // true se il player è sopra qualcosa di solido ( ==> non sta cadendo <=> può saltare)

	void applyGravity(timeSpan deltaTime);
	void move(char input);

public:
	entity(int x, int y, int health, bulletManager* bM);
	void update(timeSpan deltaTime);
	point getPos();
	hitBox getHitBox();
	int getHealth();
	bool hurt(int value);
	void setGrounded(bool grounded);
	void kill();
};

#endif //ENTITY_HPP