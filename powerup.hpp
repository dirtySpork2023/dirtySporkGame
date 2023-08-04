#ifndef POWERUP_HPP
#define POWERUP_HPP

#include "lib.hpp"

class powerup{
protected:
    point position;
    char texture;
    bool isTaken;

public: powerup(int x, int y, char texture);
    virtual ~powerup(); //distruttore virtuale

    point getPosition();
    char getTexture();
    bool getIsTaken();

    //TODO
    virtual void applyPowerupToPlayer(player& player) = 0;
};

#endif // POWERUP_HPP