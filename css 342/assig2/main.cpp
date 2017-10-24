//
// Created by R.Peters on 10/17/2017.
//

#include <memory>


using namespace std;

int main(){
    vector<unique_ptr<Scene>> myScene = {Bank('l'),TheRiver(),Bank('r')};
    cannibals cann();
    return 0;
}