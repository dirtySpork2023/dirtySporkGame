#include "healthpowerup.hpp"

healthpowerup::healthpowerup(int x, int y) : powerup(x, y, '+'){
    
    this->healthBoost = HEALTH; //defined in player.hpp as 100

}

healthpowerup::~healthpowerup() {

}

void healthpowerup::applyPowerupToPlayer(player& player) {
    player.heal(healthBoost);
    // NOTE: I MODIFIED THE PLAYER CLASS ADDING THE heal METHOD!
}