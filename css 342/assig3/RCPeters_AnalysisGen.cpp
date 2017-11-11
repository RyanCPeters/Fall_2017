//
// Created by R.Peters on 11/5/2017.
//

#include <iostream>
#include <chrono>
#include "RCPeters_AnalysisGen.h"
using namespace std;
AnalysisGen::AnalysisGen(const unsigned long long int &min,const unsigned long long int &max,bool useBrute) {



    stringstream fName;
    fName << "C:\\Users\\Peter\\GitHub_remotes\\Fall_UWB_2017\\css 342\\assig3\\GCD_Prediction_for_" << min << "_to_" << max << ".txt";
    cout << fName.str() << endl;
    ofstream predictFile;
    predictFile.open(fName.str());
    predictFile << "i,A,B,gcd,modulus operations\n";
    auto pred_start = chrono::high_resolution_clock::now();
    unsigned long long int a=1,b=2,b2=a+b,r=1,countMods = 0;
    predictFile << b << "," << a << "," << b << "," << r << "," << countMods << endl;
    while(b2 <= max){
        a=b,b=b2,b2 = a+b,++countMods;
        predictFile << b << "," << a << "," << b << "," << r << "," << countMods << endl;
    }
    auto pred_end = chrono::high_resolution_clock::now();
    predictFile << "finding max mod calls for values between " << min << " and " << max << " took  "
           << std::chrono::duration_cast<std::chrono::nanoseconds>(pred_end - pred_start).count()/1000000.00
           << " milliseconds\n";
    predictFile.close();

    if(useBrute) {
        fName.str(std::string());
        fName << "C:\\Users\\Peter\\GitHub_remotes\\Fall_UWB_2017\\css 342\\assig3\\GCD_Analysis_for_" << min << "_to_"
              << max << ".txt";
        cout << fName.str() << endl;
        myFile.open(fName.str());
        /*
         * for the time measurements we are using the labels t1 and t2.
         * t1 is recording the time, in milliseconds, it takes to find most mod calls gcd for a= [1,i-1], and b = [a+1,i]
         * t2 is recording the time, in milliseconds, between successful max mod call findings.
         */
        myFile << "i,A,B,gcd,modulus operations,t1(s),t2(s)\n";
        auto brute_start = chrono::high_resolution_clock::now();
        populateCSV(myFile, min, max);
        auto brute_end = chrono::high_resolution_clock::now();
        /*
         * this last line of output to myFile simply relates the total time it took to perform the entire task.
         */
        myFile << "finding max mod calls for values between " << min << " and " << max << " took  "
               << std::chrono::duration_cast<std::chrono::nanoseconds>(brute_end - brute_start).count() / 1000000000.00
               << " seconds\n";
        myFile.close();
    }
}

void AnalysisGen::populateCSV(ofstream &file, const unsigned long long int &min, const unsigned long long int &max) {
    auto t1start = chrono::high_resolution_clock::now();
    auto t1end = chrono::high_resolution_clock::now();
    auto t2start = chrono::high_resolution_clock::now();
    auto t2end = chrono::high_resolution_clock::now();
    auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(t1end - t1start).count()/1000000;
    auto t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2end - t2start).count()/1000000;
    GCD init(1,2,min);
    vector<GCD> rawData;
    rawData.push_back(init);
    t2start = chrono::high_resolution_clock::now();
    for(unsigned long long int i = min; i <= max; ++i) {
        t1start = chrono::high_resolution_clock::now();
        GCD ofI(1,2,i);
        for (unsigned long long int a = 1; a < i; ++a) {
            for (unsigned long long int b = i; b > a; --b) {
                GCD tmp = GCD(a, b, i);
                if (tmp > ofI)ofI = tmp;
            }// end for b
        }// end for a


        if(ofI > rawData.back()){
            t1end = chrono::high_resolution_clock::now();
            t2end = t1end;

            file<<ofI;
            rawData.pop_back();
            rawData.push_back(ofI);
            t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(t1end - t1start).count();
            t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2end - t2start).count();
            file << "," << t1/1000000000.00 << "," << t2/1000000000.00 << "\n";

            file.flush();
            t2start = t1end ;
        }
//        }// end if(ofI > init)
    }// end for i

}
