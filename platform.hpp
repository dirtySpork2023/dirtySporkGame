#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "lib.hpp"

class platform {
private:
    hitBox box;
public:
    platform (int x, int y);
    void print();
    point getPos;
    hitBox getHitbox();
};

platform randomPlat (hitBox where);

int whereIsY (hitBox v1, hitBox v2);

int whereIsX (hitBox v1, hitBox v2);

#endif //PLATFORM_HPP