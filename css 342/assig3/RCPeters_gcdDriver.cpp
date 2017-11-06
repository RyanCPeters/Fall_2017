#include <iostream>
#include "RCPeters_AnalysisGen.h"
using namespace std;

int main() {

    for(int i = 15,j = i/2+1; i <=3000; j = i+1,i +=100 ) {
        AnalysisGen aGen = AnalysisGen(j,i);
    }

    return 0;
}