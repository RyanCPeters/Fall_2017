//
// Created by R.Peters on 11/5/2017.
//

#include <iostream>
#include "RCPeters_AnalysisGen.h"

AnalysisGen::AnalysisGen(const int &min,const int &max):biggest(0) {

    stringstream fName;
    fName << "C:\\Users\\Peter\\GitHub_remotes\\Fall_UWB_2017\\css 342\\assig3\\GCD_Analysis_for_" << min << "_to_" << max << ".txt";
    cout << fName.str() << endl;
    myFile.open(fName.str());

    myFile << "i,A,B,gcd,modulus operations\n";
    biggest = populateCSV(myFile,min,max);
    myFile.close();
}

GCD AnalysisGen::populateCSV(ofstream &file, const int &min, const int &max) {
    GCD forBigVals(1,2,min);
    vector<GCD> rawData;
    rawData.push_back(forBigVals);

    for(int i = min; i <= max; ++i)
    {
        GCD ofI(1,2,i);
        for (int a = 1; a < i; ++a) {
            for (int b = i; b > a; --b) {
                GCD tmp = GCD(a, b, i);
                if (tmp > ofI)ofI = tmp;
            }
        }
        if(ofI > forBigVals){
            if(ofI > rawData.back()){
                file<<ofI << endl;
                rawData.pop_back();
                rawData.push_back(ofI);
            }
        }
    }
    file << endl << endl;
    return rawData.back();
}
