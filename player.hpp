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

	//Variabili per il powerup shield
	bool shieldActive;
    double shieldDuration;
    double elapsedShieldTime;

public:
	player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, float jumpHeight, float armor);
	void print(timeSpan deltaTime);
	void update(char input, timeSpan deltaTime);
	bool hurt(int value);
	void shoot();

	//metodo per health powerup
	void heal(int amount);

	//metodi per shield powerup
	void activateShield(double duration);
    void updateShield(double deltaTime);
    bool isShieldActive();
};

#endif //PLAYER_HPP