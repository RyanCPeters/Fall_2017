//
// Created by R.Peters on 10/17/2017.
//
#include "cannibals.h"
#include "cannibals.cpp"
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