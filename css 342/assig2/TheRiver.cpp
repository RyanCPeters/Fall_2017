//
// Created by R.Peters on 10/22/2017.
//



#include <iostream>
#include "TheRiver.h"


using namespace std;

TheRiver::TheRiver():Scene(_water) {
    curPos = boatPos[0];
    insertBoat();
}

void TheRiver::insertBoat() {
    Actor result[myLen];
    result[0] = '\\';
    result[myLen -1] = '/';
    for (int i = 1; i < myLen-1 ; ++i) result[i] = Actor('_');
    for (int j = 0; j < myBoat.myLen; ++j) {
        result[j+curPos] = (myBoat.getCast())[j];
    }
    updatePos();
}
void TheRiver::updatePos() {
    switch (curPos){
        case -2:
            curPos = boatPos[0];
            break;
        case 1:
            myBoat.goRight(myBoat.getSeat1(),myBoat.getSeat2());
            curPos = boatPos[1];
            break;
        case 2:
            curPos = boatPos[2];
            break;
        case 3:
            myBoat.goLeft(myBoat.getSeat1(),myBoat.getSeat2());
            curPos = boatPos[3];
            break;
        default:
            cout << endl << "shits gone sideways mang!!!!"<< endl;
    }
}
Boat& TheRiver::getBoat()const{ return myBoat;}
void TheRiver::setBoat(Boat &b){
    myBoat = b;
}

ostream& TheRiver::makeOStrm(ostream &os)const{
    for(int i = 0; i < myLen; ++i){
        os << stage[i].getId();
    }
    return os;
}

ostream& operator<<(ostream &os, const TheRiver &riv) {

    return riv.makeOStrm(os);
}
