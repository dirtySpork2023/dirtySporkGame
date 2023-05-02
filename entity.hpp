#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "lib.hpp"
#include "level.hpp"
#include "bulletManager.hpp"

#define ENTITY_G 175
#define DAMAGE_TIMESPAN 0.10

class level; // necessario per compilare

class entity {
protected:
	hitBox box;
	int health; // punti vita
	timeSpan lastDamage; // time in seconds elapsed since entity was hurt
	bulletManager* bM; // reference a classi del livello
	level* lvl;
	double ySpeed; // velocità verticale
	double yMod; // parte decimale della posizione in verticale
	bool isGrounded; // true se il player è sopra qualcosa di solido ( => non sta cadendo <=> può saltare)

	void applyGravity(timeSpan deltaTime); // abbassa entity in base alla forza di gravità e il tempo passato
	void move(char input); // muove entity di un blocco verso una direzione WASD
	void setPrintColor(int paint = PAINT_DEFAULT); // colora di rosso entity se ha subito danno recentemente

public:
	entity(int x, int y, level* lM, bulletManager* bM, int hp);
	void update(timeSpan deltaTime);
	point getPos(); // ritorna la posizione del
	hitBox getHitBox(); // ritorna la hitBox
	int getHealth(); // ritorna i punti vita
	bool hurt(int value); // danneggia entity e ritorna se è morto
	void setGrounded(bool grounded); // quando entity è a terra (o sopra un nemico), bisogna invocare questo metodo // TODO rifare
	~entity(); // distruttore: cancella l'entity solo graficamente
};

#endif //ENTITY_HPP