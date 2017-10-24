//
// Created by R.Peters on 10/22/2017.
//
#include <iostream>
#include "Scene.h"


using namespace std;

Scene::Scene() = default;

Scene::Scene(const char &_myType):myType(_myType) {
    myLen = (myType == _water)? 8:6;

    switch (myType) {
        case 'l':
            stage = le;
            break;
        case 'w':
            // in order to incorporate the boat into the river representation we are
            // going to set the stage for TheRiver inside its constructor.
//            stage = riv;
            break;
        case 'r':
            stage = ri;
            break;

        default:
            cout << "break down in scene set up for myType = " << myType << endl;
            break;
    }
}




