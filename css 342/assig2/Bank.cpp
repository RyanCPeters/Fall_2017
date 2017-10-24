//
// Created by R.Peters on 10/22/2017.
//

#include <iostream>
#include "Bank.h"


using namespace std;

Bank::Bank(const char &leftRight):Scene(leftRight){};

int Bank::hasCannibal(){
    int num = 0;
    for(int i = 0; i < myLen; ++i){
        num = (stage[i] == can1)? num+1 : num;
    }
    return num;
}

// assumed that all calls to getCannible() will always be preceded by a call to hasCannibal();
Actor& Bank::getCannible(){
    int pos = 0;
    for(int i = 0; i < myLen; ++i){
        if(stage[i] == can1) {
            pos = i;
            break;
        }
    }
    Actor ret = stage[pos];
    stage[pos] = Actor('-');
    return ret;
}

int Bank::hasExplo(){
    int num = 0;
    for(int i = 0; i < myLen; ++i){
        num = (stage[i] == ex1)? num+1 : num;
    }
    return num;
}

// assumed that all calls to getExplo() will always be preceded by a call to hasExplo();
Actor& Bank::getExplo(){
    int pos = 0;
    for(int i = 0; i < myLen; ++i){
        if(stage[i] == ex1) {
            pos = i;
            break;
        }
    }
    Actor ret = stage[pos];
    stage[pos] = Actor('-');
    return ret;
}

friend ostream& operator<<(ostream &os, const Scene &scene) {
    for(int i = 0; i < scene.myLen; ++i){
        os << scene.stage[i];
    }
    return os;
}