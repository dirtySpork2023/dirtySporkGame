#include "shieldpowerup.hpp"

shieldpowerup::shieldpowerup(int x, int y) : powerup(x, y, 'S'){
    this->numsec = 10;
}

shieldpowerup::~shieldpowerup() {

}

void shieldpowerup::applyPowerupToPlayer(player& player) {
    player.activateShield(numsec);
    //activateShield method: freeza la vita del player per this->numsec secondi
    //TODO: SET SHIELD TEXTURE!!!!
    //NOTE: I MODIFIED THE PLAYER CLASS ADDING THE activateShield method + MORE!!!

}