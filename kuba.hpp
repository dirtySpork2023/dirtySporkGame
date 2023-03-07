#ifndef	KUBA_HPP
#define KUBA_HPP

#include "lib.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "bulletManager.hpp"

class kuba: public entity {
protected:
	double xSpeed; // tempo in secondi dopo il quale si muove
	int damage;
public:
	kuba(int x, int y, int h, bulletManager* b, double moveSpeed, int damage);
	void update(player* target, timeSpan deltaTime);
	void print(timeSpan deltaTime);
};

#endif //KUBA_HPP