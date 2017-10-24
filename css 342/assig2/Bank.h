//
// Created by R.Peters on 10/22/2017.
//

#ifndef CSS_342_BANK_H
#define CSS_342_BANK_H


#include "Scene.h"

using namespace std;

class Bank: public Scene {
public:
    Bank(const char &leftRight):Scene(leftRight){};

    int hasCannibal();

    // assumed that all calls to getCannible() will always be preceded by a call to hasCannibal();
    Actor& getCannible();

    int hasExplo();

    // assumed that all calls to getExplo() will always be preceded by a call to hasExplo();
    Actor& getExplo();
private:
};

#endif //CSS_342_BANK_H
