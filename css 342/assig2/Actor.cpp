//
// Created by R.Peters on 10/22/2017.
//

#include <iostream
#include "Actor.h"

using namespace std;


Actor &Actor::operator=(const Actor &a){
    this->myId = a.getId();
    return *this;
}

Actor &Actor::operator=(const char &c) {
    this->myId = c;
    return *this;
}

char Actor::getId() const{ return myId; }

bool Actor::operator==(const Actor &a) const { return this->myId == a.getId(); }

bool Actor::operator==(const char &c) const { return this->myId == c; }

bool Actor::operator!=(const Actor &a) const { return this->myId != a.getId(); }

bool Actor::operator!=(const char &c) const { return this->myId != c; }


ostream& operator<<(ostream &os, const Actor &a) {
    os << a.getId();
    return os;
}

