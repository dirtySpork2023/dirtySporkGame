#ifndef	KUBA_HPP
#define KUBA_HPP

#include "lib.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "bulletManager.hpp"

class kuba: public entity {
protected:
	double xSpeed; // tempo in secondi dopo il quale si muove
public:
	kuba(int x, int y, int h, bulletManager* b, double moveSpeed);
	void update(point target, double deltaTime);
	void print(double deltaTime);
};

#endif //KUBA_HPP