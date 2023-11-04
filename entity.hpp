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
	bulletManager* bM; // reference al gestore dei proiettili
	level* lvl; // reference al gestore del livello
	double ySpeed; // velocità verticale
	double yMod; // parte decimale della posizione in verticale
	bool isGrounded; // 'se il player ha i piedi per terra'

	void setGrounded(bool grounded);
	void applyGravity(timeSpan deltaTime); // abbassa entity in base alla forza di gravità e il tempo passato
	void move(char input); // muove entity di una posizione verso una direzione WASD
	void setPrintColor(int paint = PAINT_DEFAULT); // applica il colore con cui stampare

public:
	entity(int x, int y, level* lM, bulletManager* bM, int hp);
	void update(timeSpan deltaTime);
	point getPos(); // ritorna la posizione
	hitBox getHitBox(); // ritorna la hitBox
	int getHealth(); // ritorna i punti vita
	bool hurt(int value); // danneggia entity e ritorna 'se è morto'
	~entity();
};

#endif //ENTITY_HPP