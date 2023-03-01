#ifndef SCHELETRO_HPP
#define SCHELETRO_HPP

#include "player.hpp"

class scheletro: public player{
private:
	char texture[3][3] = {
			{' ','°',' '},
			{')','M','>'},
			{'/','"','\\'},
	};
	char reverse[3][3] = {
			{' ','°',' '},
			{'<','M','('},
			{'/','"','\\'},
	};
public:
	scheletro(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, int health):
		player(int x, int y, bulletManager* b, double gunFireRate, int gunDamage, int health);
};

#endif //SCHELETRO_HPP