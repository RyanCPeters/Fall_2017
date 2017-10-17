//
// Created by R.Peters on 10/16/2017.
//

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "fucked.h"

using namespace std;



string transport(vector<char> &lShore, vector<char> &river, vector<char> &rShore, char *boat, int boatPos,
                 stringstream &ss){

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
        if(boat[1] == _empty && boat[2] == )
    }
    return ss.str();
}

int main(){
    vector<char> river;
    vector<char> lShore;
    vector<char> rShore;
    stringstream ss;
    // set up lShore's char array.
    lShore.assign(6,' ');
    for (int i = 0; i < 3; ++i) lShore[i] = _canni;
    for (int j = 3; j < 6; ++j) lShore[j] = _exp;

    // set up river's char array, including the boat char array.
    river.assign(8,_water);
    river[0] = _lbnk;
    river[7] = _rbnk;
    char boat[4] = {_lprow,_empty,_empty,_rprow};
    for(int i = 0; i < 4; ++i) river[i+1] = boat[i];


    // set up rShore
    rShore.assign(6,_dirt);

    // make sure there's no excess allocation on the vectors before we start recursion.
    lShore.resize(6);
    river.resize(8);
    rShore.resize(6);

    // commence recurse!!
    for(char c : lShore)ss << c;
    for(char c : river)ss << c;
    for(char c : rShore)ss << c;
    ss << endl;
    cout << transport(lShore, river, rShore, boat, 1, ss);

    return 0;
}