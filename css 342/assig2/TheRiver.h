//
// Created by R.Peters on 10/22/2017.
//

#ifndef CSS_342_THERIVER_H
#define CSS_342_THERIVER_H

#include <iosfwd>
#include "Scene.h"
#include "Boat.h"


class TheRiver: public Scene{
public:
    const char _right = 'r', _left = 'l';
    explicit TheRiver();
    friend ostream& operator<<(ostream &os, const TheRiver &riv);
    Boat& getBoat()const;
    void setBoat(Boat &b);

private:
    void insertBoat();
    void updatePos();
    int curPos;
    const int boatPos[4] = {1,2,3,-2};
    Boat myBoat = Boat(_right);

    ostream& makeOStrm(ostream &os)const;
};

#endif //CSS_342_THERIVER_H
