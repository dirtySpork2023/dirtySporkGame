#include "powerup.hpp"

powerup::powerup(int x, int y, char texture){
    this->texture = texture;
    this->isTaken = false;
    this->position.x = x;
    this->position.y = y;
}

powerup::~powerup() {
    
}

point powerup::getPosition() {
    return position;
}

char powerup::getTexture() {
    return texture;
}

bool powerup::getIsTaken() {
    return isTaken;
}