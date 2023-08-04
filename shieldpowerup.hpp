#ifndef SHIELD_POWERUP_HPP
#define SHIELD_POWERUP_HPP

#include "powerup.hpp"
#include "player.hpp"

/* SHIELD POWERUP: GIVES THE PLAYER A TEMPORARY SHIELD
SHIELD LASTS FOR numsec SECONDS, IN THIS CASE 10 SECONDS
*/

//TODO how the fuck to implement shield graphics?? eg parenthesis around player

class shieldpowerup : public powerup {
protected:
    int numsec; //number of seconds the shield lasts for

public:
    shieldpowerup(int x, int y);
    virtual ~shieldpowerup();

    virtual void applyPowerupToPlayer(player& player);
};

#endif // SHIELD_POWERUP_HPP