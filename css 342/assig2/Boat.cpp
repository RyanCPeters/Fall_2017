//
// Created by R.Peters on 10/22/2017.
//

#include <iostream>
#include "Boat.h"

using namespace std;

Boat::Boat(const char &c){
    switch(c){
        case 'r':
            goRight(empty1, empty2);
            break;
        case 'l':
            goLeft(empty1,empty2);
            break;
        default:
            break;
    }
}

Actor& Boat::setSeat1(Actor &a){
    Actor &result = cast[1];
    cast[1] = a;
    return result;
}
Actor& Boat::setSeat2(Actor &a){
    Actor &result = cast[2];
    cast[2] = a;
    return result;
}


Actor& Boat::getSeat1(){
    Actor &result = cast[1];
    cast[1] = empty1;
    return result;
}
Actor& Boat::getSeat2(){
    Actor &result = cast[2];
    cast[2] = empty2;
    return result;
}

Actor* Boat::goLeft(const Actor &seat1, const Actor &seat2){
    return setUpBoat(left, seat1, seat2);
}
Actor* Boat::goRight(const Actor &seat1, const Actor &seat2){

    setUpBoat(right, seat1, seat2);
    return cast;
}
Actor* Boat::getCast(){
    return cast;
}
Actor* Boat::setUpBoat(const Actor &front, const Actor &seat1, const Actor &seat2){
    cast[1] = seat1;
    cast[2] = seat2;
    switch (front.getId()) {
        case '>':
        case 'r':
        case 'R':
            cast[0] = front;
            cast[3] = tail;
            break;
        case '<':
        case 'l':
        case 'L':
            cast[0] = tail;
            cast[3] = front;
            break;
        default:
            cout << endl << "something weird happened inside setUptBoat's switch block" << endl;
            break;
    }
    return cast;
}