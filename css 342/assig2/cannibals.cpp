//
// Created by R.Peters on 10/17/2017.
//

#include "cannibals.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;



string transport(vector<char> &lShore, vector<char> &river, vector<char> &rShore, char *boat, int boatPos,
                            stringstream &ss) {

    if(lShore[0] == _dirt) {
        if(boatPos == 3) {
            if (boat[1] == _empty && boat[2] == _empty) {
                for (char c : lShore)ss << c;
                for (char c : river)ss << c;
                for (char c : rShore)ss << c;
                ss << endl;
                return ss.str();
            }
        }else if(boatPos == 2){

        }
    }
    if(boatPos == 3){
//        if(boat[1] == _empty && boat[2] == )
    }
    return ss.str();
}
