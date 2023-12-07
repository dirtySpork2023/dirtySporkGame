#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "lib.hpp"

class platform {
protected:
    hitBox box;
    char texture;
public:
    platform (int a, int b, int c, int d, char text);
    void print();
    void printp();
    void printc(char c);
    hitBox getHitBox();
};

#endif //PLATFORM_HPP