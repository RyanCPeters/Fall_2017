#include <iostream>
#include <vector>

using namespace std;
bool recurseSolve(vector<vector<int>> &path,vector<vector<int>> &offpath, int lvl);

static const vector<vector<int>> options = {{1, 0, 1 },{ 0,1,1 },{ 0,2,1 },{ 1,1,1 },{ 2,0,1 }};
const vector<int> initState = {3,3,1};
int main() {
    vector<vector<int>> path;
    vector<vector<int>> offpath;
    path.push_back(initState);
    offpath.push_back({0,0,0});
    int lvl = 1;
    bool didWeWin = recurseSolve(path, offpath, lvl);
    cout << "did we win? "<< didWeWin << endl;

    for(vector<int> ele: path){
        for(int i : ele){
            cout << i;
        }
        cout << endl;
    }
    return 0;
}

bool recurseSolve(vector<vector<int>> &path,vector<vector<int>> &offpath, int lvl){
    bool foundAValid = false;
    int signer = (lvl%2 == 1)? -1 : 1;
    vector<int> currLvl,nextLvl, subOpt, currOff, nextOff;
    currLvl = path.at(path.size()-1);
    path.pop_back();
    currOff = offpath.at(offpath.size()-1);
    offpath.pop_back();
    for(int idx = (signer > 0)? 0 : 2 ; idx < 5, !foundAValid; ++idx){
        nextLvl.clear();
        subOpt.clear();
        nextOff.clear();
        subOpt.assign(options.at(idx).begin(),options.at(idx).end());
        for(int jdx = 0; jdx <3;++jdx){
            int tmp = currLvl.at(jdx) + (subOpt.at(jdx)) * signer,
            offtmp = currOff.at(jdx) + (subOpt.at(jdx)) * signer*(-1);
            nextLvl.push_back(tmp);
            nextOff.push_back(offtmp);
        }
        if(nextLvl.at(0) == 0 && nextLvl.at(1) == 0)return true;
        if(nextLvl.at(0) >= nextLvl.at(1) &&
                nextLvl.at(0) >= 0 &&
                nextLvl.at(0) <= 3 &&
                nextLvl.at(1) >= 0 &&
                nextLvl.at(1) <= 3 &&
                nextOff.at(0) >= nextOff.at(1)){
            path.push_back(currLvl);
            path.push_back(nextLvl);
            offpath.push_back(currOff);
            offpath.push_back(nextOff);
            lvl++;
            foundAValid = recurseSolve(path,offpath,lvl);
            if(foundAValid)return true;
        }
    }
    return foundAValid;


}