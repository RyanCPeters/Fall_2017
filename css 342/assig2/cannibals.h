//
// Created by R.Peters on 10/17/2017.
//

#ifndef CSS_342_CANNIBALS_H
#define CSS_342_CANNIBALS_H

#include <iosfwd>
#include <vector>
#include <string>
#include <iosfwd>
using namespace std;
class cannibals {

public:

    string transport(vector<char> &lShore, vector<char> &river, vector<char> &rShore, char *boat, int boatPos, stringstream &ss);
private:
   char _canni = 'C', _exp = 'X', _lbnk = '\\',_rbnk = '/',_dirt = '-',_water = '_',_lprow = '<', _rprow = '>',_empty = '=';

};


#endif //CSS_342_CANNIBALS_H
