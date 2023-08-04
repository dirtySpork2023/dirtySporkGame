#ifndef HEALTH_POWERUP_HPP
#define HEALTH_POWERUP_HPP

#include "powerup.hpp"
#include "player.hpp"

/*HEALTH POWERUP: Brings the players health back to its inital health (HEALTH in player.hpp)*/

class healthpowerup : public powerup {
protected:
    int healthBoost;

public:
    healthpowerup(int x, int y);
    virtual ~healthpowerup();

    virtual void applyPowerupToPlayer(player& player);
};

#endif // HEALTH_POWERUP_HPP