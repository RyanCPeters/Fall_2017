//
// Created by R.Peters on 10/22/2017.
//

#ifndef CSS_342_BOAT_H
#define CSS_342_BOAT_H


#include "Actor.h"

class Boat {
public:
    const int myLen = 4;
    const Actor
            tail = Actor('|'), left = Actor('<'), right = Actor('>'),
            empty1 = Actor('.'), empty2 = Actor('.');
    explicit Boat(const char &c);
    Actor* goLeft(const Actor &seat1, const Actor &seat2);
    Actor* goRight(const Actor &seat1, const Actor &seat2);
    Actor* getCast();
    Actor& setSeat1(Actor &a);
    Actor& setSeat2(Actor &a);
    Actor& getSeat1();
    Actor& getSeat2();
private:
    Actor cast[4];
    Actor* setUpBoat(const Actor &front, const Actor &seat1, const Actor &seat2);
};




#endif //CSS_342_BOAT_H
