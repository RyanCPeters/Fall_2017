//
// Created by R.Peters on 11/5/2017.
//

#include <iostream>
#include <chrono>
#include "RCPeters_AnalysisGen.h"
using namespace std;
AnalysisGen::AnalysisGen(const int &min,const int &max) {

    stringstream fName;
    fName << "C:\\Users\\Peter\\GitHub_remotes\\Fall_UWB_2017\\css 342\\assig3\\GCD_Analysis_for_" << min << "_to_" << max << ".txt";
    cout << fName.str() << endl;
    myFile.open(fName.str());
    myFile << "predicted solutions are\npredicted_i, predicted_A, predicted_B, predicted_gcd,predicted_modcalls\n";
    auto predict_start = chrono::high_resolution_clock::now();
    int predictA = 2, predictB = 3, predNextB = predictA + predictB, predModCalls = 2;
    myFile << 2 << "," << 1 << "," << 2 << "," << 0  << "," <<  1 << endl;
    while(predictB <= max){
        myFile << predictB << "," << predictA << "," << predictB << "," << 1  << "," <<  predModCalls << endl;
        ++predModCalls;
        predictA = predictB, predictB = predNextB, predNextB = predictA + predictB;

    }

    auto predict_end = chrono::high_resolution_clock::now();
    myFile << "the time to calculate prediction took "
         << chrono::duration_cast<std::chrono::nanoseconds>(predict_end - predict_start).count()
         << " nanoseconds\n\n";
    auto brute_start = chrono::high_resolution_clock::now();
    myFile << "i,A,B,gcd,modulus operations\n";
    populateCSV(myFile,min,max);
    auto brute_end = chrono::high_resolution_clock::now();
    myFile << "the time to calculate prediction took "
         << chrono::duration_cast<std::chrono::nanoseconds>(brute_end - brute_start).count()/1000000
         << " nanoseconds\n\n";
    myFile.close();
}

void AnalysisGen::populateCSV(ofstream &file, const int &min, const int &max) {
    GCD forBigVals(1,2,min);
    vector<GCD> rawData;
    rawData.push_back(forBigVals);
    for(int i = min; i <= max; ++i) {
        GCD ofI(1,2,i);
        for (int a = 1; a < i; ++a) {
            for (int b = i; b > a; --b) {
                GCD tmp = GCD(a, b, i);
                if (tmp > ofI)ofI = tmp;
            }// end for b
        }// end for a
        if(ofI > forBigVals){
            if(ofI > rawData.back()){
                file<<ofI << endl;
                rawData.pop_back();
                rawData.push_back(ofI);
            }
        }// end if(ofI > forBigVals)
    }// end for i
}
