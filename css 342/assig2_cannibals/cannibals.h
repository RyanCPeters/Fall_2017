//
// Created by R.Peters on 10/29/2017.
//

#ifndef FIXCANNIBALS3_CANNIBALS_H
#define FIXCANNIBALS3_CANNIBALS_H

#include <iosfwd>
#include <vector>
#include <string>

using namespace std;


class cannibals{
private:
    const vector<int> failState;
    const vector<int> baseCase;
    const vector<vector<int>> options;
    const vector<int> initState;

    bool checkValidity(const vector<int> &curState, const vector<int> &nextState)const;
    bool checkValid(const vector<int> &aState)const;
    vector<vector<int>> buildOpts(const vector<int> &nextState);
    vector<int> applyStep(const vector<int> &curState, const vector<int> &step);

public:
    cannibals();
    string makeString(vector<int> stateToBeRepresented);
    vector<vector<int>> recurseSolve(const vector<int> &curState, const vector<int> &custOpts);

};

#endif //FIXCANNIBALS3_CANNIBALS_H
