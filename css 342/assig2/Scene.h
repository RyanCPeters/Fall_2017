//
// Created by R.Peters on 10/22/2017.
//

#ifndef CSS_342_SCENE_H
#define CSS_342_SCENE_H

#include <iosfwd>
#include "Actor.h"

using namespace std;

class Scene {
public:

    const char
            _left = 'l',
            _water = 'w',
            _right = 'r';

    const Actor
            ex1 = Actor('E'), ex2 = Actor('E'), ex3 = Actor('E'),
            can1 = Actor('C'), can2 = Actor('C'), can3 = Actor('C');

    Scene();
    friend ostream& operator<<(ostream &os, const Scene &scene);

protected:
    explicit Scene(const char &);
    Actor *stage;
    int myLen;
    char myType;

private:

    Actor le[6] = {ex1,ex2,ex3,can1,can2,can3};
//    Actor riv[8] = {Actor('\\'),Actor('_'),Actor('_'),Actor('_'),Actor('_'),Actor('_'),Actor('_'),Actor('/')};
    Actor ri[6] = {Actor(),Actor(),Actor(),Actor(),Actor(),Actor()};
};




#endif //CSS_342_SCENE_H
