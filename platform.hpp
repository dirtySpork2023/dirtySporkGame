#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "lib.hpp"

class platform {
protected:
    hitBox box;
public:
    platform (int a, int b, int c, int d);
    // void setNext(platform p);
    // platform* getNext ();
    void print();
    hitBox getHitbox();
};

#endif //PLATFORM_HPP