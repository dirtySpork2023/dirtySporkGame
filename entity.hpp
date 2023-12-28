#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "lib.hpp"
#include "bulletManager.hpp"

class level;

#define ENTITY_G 175
#define DAMAGE_TIMESPAN 0.10

class entity {
protected:
	hitBox box;
	int health; // punti vita
	timeSpan lastDamage; // tempo passato dall'ultima volta che è stato colpito entity
	level* lvl; // reference al gestore del livello
	double ySpeed; // velocità verticale
	double yMod; // parte decimale della posizione in verticale
	bool isGrounded; // 'se il player ha i piedi per terra'

	void applyGravity(timeSpan deltaTime);
	void move(char input);
	void setPrintColor(int paint);

public:
	entity(int x, int y, level* lM, int hp);
	void update(timeSpan deltaTime);
	point getPos();
	hitBox getHitBox();
	int getHealth();
	bool hurt(int value);
	~entity();
};

#endif //ENTITY_HPP