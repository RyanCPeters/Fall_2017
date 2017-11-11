#include <iostream>
#include "RCPeters_AnalysisGen.h"
using namespace std;

int main() {

//    for(int i = 15,j = i/2+1; i <=3015; j = i+1,i +=100 ) {
//        AnalysisGen aGen = AnalysisGen(j,i);
//    }
//    AnalysisGen gen = AnalysisGen(8,15);
//    for(int i = 115,j = i-99; i <=3015; j = i+1,i +=100 ) {
//        AnalysisGen aGen = AnalysisGen(j,i);
//    }
    const unsigned long long int max = (18446744073709551615 - 18446744073709551615/5);
    AnalysisGen aGen = AnalysisGen(8,max,false);
//    aGen = AnalysisGen(8,3000,true);

    return 0;
}