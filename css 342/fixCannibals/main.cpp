#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
//bool recurseSolve(vector<vector<int>> &path,vector<vector<int>> &offpath, int lvl);
bool recurseSolve(vector<vector<int>> &path, int lvl);
string makeString(vector<int> curr, vector<int> prev);


static const vector<vector<int>> options = {{1, 0, 1 },{ 0,1,1 },{ 0,2,1 },{ 1,1,1 },{ 2,0,1 }};
const vector<int> initState = {3,3,1};
int main() {
    vector<vector<int>> path;
    vector<vector<int>> offpath;
    path.push_back(initState);
    offpath.push_back({0,0,0});
    int lvl = 1;
    bool didWeWin = recurseSolve(path, lvl);
    cout << "did we win? "<< didWeWin << endl;
    vector<int> prev = {3,3,1};
    for(vector<int> cur: path){
        cout << makeString(cur,prev);
        cout << endl;
    }
    return 0;
}

//bool recurseSolve(vector<vector<int>> &path,vector<vector<int>> &offpath, int lvl){
bool recurseSolve(vector<vector<int>> &path, int lvl){
    bool foundAValid = false;
    int signer = (lvl%2 == 1)? -1 : 1;
    vector<int> currLvl,nextLvl, subOpt, currOff, nextOff;
    currLvl = path.at(path.size()-1);
    if(currLvl.at(0) == 0 && currLvl.at(1) == 0){
//        path.push_back(currLvl);
        return true;
    }
    path.pop_back();
//    currOff = offpath.at(offpath.size()-1);
//    offpath.pop_back();
    for(int idx = (signer > 0)? 0 : 2 ; idx < 5, !foundAValid; ++idx){
        nextLvl.clear();
        subOpt.clear();
//        nextOff.clear();
        subOpt.assign(options.at(idx).begin(),options.at(idx).end());
        for(int jdx = 0; jdx <3;++jdx){
            int tmp = currLvl.at(jdx) + (subOpt.at(jdx)) * signer;
//            offtmp = currOff.at(jdx) + (subOpt.at(jdx)) * signer*(-1);
            nextLvl.push_back(tmp);
//            nextOff.push_back(offtmp);
        }

        if(nextLvl.at(0) >= nextLvl.at(1) ) {
            if (    nextLvl.at(0) >= 0 &&
                    nextLvl.at(0) <= 3 &&
                    nextLvl.at(1) >= 0 &&
                    nextLvl.at(1) <= 3) {
                path.push_back(currLvl);
                path.push_back(nextLvl);
//            offpath.push_back(currOff);
//            offpath.push_back(nextOff);
                lvl++;
                foundAValid = recurseSolve(path, lvl);
//            if(foundAValid)return true;
            }
        }
    }
    return foundAValid;


}


string makeString(vector<int> curr, vector<int> prev){
    int explo = curr.at(0),
        canns = curr.at(1),
        boatSide = curr.at(2),
        rExp = prev.at(0),
        rCan = prev.at(1);

    int boatExp = explo - rExp,
        boatCan = canns - rCan;
    boatExp = (boatExp < 0)? -boatExp :boatExp;
    boatCan = (boatCan  < 0)? -boatCan :boatCan;

    stringstream scene;
    for(int j = 0; j < (6 -explo - canns); ++j) scene << "-";
    for (int i = 0; i <explo ; ++i) scene << "E";
    for(int k = 0; k < canns; ++k) scene << "C";
    scene << " \\ ";
    switch (boatSide){
        case 0:
            scene << " _ " << "_ ";
            scene << "<..>";
//            for(int i = 0; i< boatExp; ++i){
//                scene << "E";
//            }
//            for (int j = 0; j < boatCan; ++j) {
//                scene << "C";
//            }
//            scene << ">";
            break;
        case 1:
            scene << "<..>";
//            for(int i = 0; i< boatExp; ++i){
//                scene << "E";
//            }
//            for (int j = 0; j < boatCan; ++j) {
//                scene << "C";
//            }
//            scene << ">";
            scene << " _ " << "_ ";
            break;
    }
    scene << " / ";
    for(int i = 0; i < 3-explo; ++i)scene << "E";
    for(int i = 0; i < 3 - canns; ++i)scene << "C";
    for(int i = 0; i < 6 -((3- explo) + (3-canns)); ++i)scene << "-";

    return scene.str();


}