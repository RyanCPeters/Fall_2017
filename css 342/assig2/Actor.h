//
// Created by R.Peters on 10/22/2017.
//

#ifndef CSS_342_ACTOR_H
#define CSS_342_ACTOR_H

#include <iosfwd>

using namespace std;

class Actor {
public:
    Actor(const char &id = '-'):myId(id){};
    Actor& operator=(const Actor &a);
    Actor& operator=(const char &c);
    char getId() const;
    bool operator==(const Actor &a) const;
    bool operator==(const char &c) const;
    bool operator!=(const Actor &a) const;
    bool operator!=(const char &c) const;
    friend ostream& operator<<(ostream &os, const Actor &a);

private:
    char myId;

};


#endif //CSS_342_ACTOR_H
