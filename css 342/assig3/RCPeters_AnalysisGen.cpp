//
// Created by R.Peters on 11/5/2017.
//

#include <iostream>
#include "RCPeters_AnalysisGen.h"

AnalysisGen::AnalysisGen(const int &min,const int &max) {

    stringstream fName;
    fName << R"(C:\Users\Peter\GitHub_remotes\Fall_UWB_2017\css 342\assig3\GCD_Analysis_for_)" << min << "_to_" << max << ".txt";
    cout << fName.str() << endl;
    myFile.open(fName.str());

    myFile << "i,A,B,gcd,modulus operations\n";
    populateCSV(myFile,min,max);
    myFile.close();
}

void AnalysisGen::populateCSV(ofstream &file, const int &min, const int &max) {
    vector<vector<int>> rawData;
    for(int i = min; i <= max; ++i){
        for(int a = 1; a < i; a += (i/100 > 1)?i/100:++a) {
            for(int b = a+1; b<=i;b += (i/100 > 1)?i/100:++b) {
                GCD tmp = GCD(a, b);
                if (rawData.size() > 0)
                {
                    if (i < 900)
                    {
                        if (rawData.size() > 0 && rawData.back()[0] == i)
                        {
                            if (rawData.back()[4] < tmp.getModCalls())
                            {
                                rawData.pop_back();
                                rawData.push_back({i, tmp.getA(), tmp.getB(), tmp.getGCD(), tmp.getModCalls()});
                            }
                        } else rawData.push_back({i, tmp.getA(), tmp.getB(), tmp.getGCD(), tmp.getModCalls()});
                    } else {
                        if (rawData.back()[4] < tmp.getModCalls()) rawData.push_back({i, tmp.getA(), tmp.getB(), tmp.getGCD(), tmp.getModCalls()});
                    }
                }else rawData.push_back({i, tmp.getA(), tmp.getB(), tmp.getGCD(), tmp.getModCalls()});
            }
        }
    }
    file << endl << endl;
    for(const auto &vec : rawData){
        file << vec[0] <<","<<
             vec[1]<<","<<
             vec[2]<<","<<
             vec[3]<<","<<
             vec[4]<<endl;
        file.flush();
    }

}
