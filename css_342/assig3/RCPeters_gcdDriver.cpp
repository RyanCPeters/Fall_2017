#include <iostream>
#include <chrono>
#include "RCPeters_AnalysisGen.h"
using namespace std;

int main() {
//    bool buildLowValTimeValidation = false;
    long long int a =1,b=2,b2 = a+b, min = 1, max = 3000, padding = 100;
    cout << "Please enter the minimum value you want to consider for this run of data generation.";
    cin >> min;
    cout << "Please enter the max value you want to consider for this run of data generation.";
    cin >> max;

//    AnalysisGen aGen = AnalysisGen(min,max);
//    cout << "a = " << a << "\tb = " << b << endl;

//    while (buildLowValTimeValidation && b<=0377){
//        stringstream ss;
//        AnalysisGen aGen = AnalysisGen(a,b);
//
//        auto brute_start = chrono::high_resolution_clock::now();
//        aGen.buildDataSet(a, b, padding);
//        auto brute_end = chrono::high_resolution_clock::now();
//        /*
//         * this last line of output to myFile simply relates the total time it took to perform the entire task.
//         */
//        string unit1;
//        auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(brute_end - brute_start).count();
//        double time1;
//        if(t1>1000000000.00){
//            time1 = t1/1000000000.00;
//            unit1 = "s";
//        }else if(t1>1000000.00){
//            time1 = t1/1000000.00;
//            unit1 = "ms";
//        }else if(t1>1000.00){
//            time1 = t1/1000.00;
//            unit1 = "us";
//        }else{
//            time1 = t1;
//            unit1 = "ns";
//        }
//        ss << "-1,"<< a <<","<< b <<",0,0,0,ns,"
//               << time1
//                <<","<<unit1<< endl;
//        aGen.insertToFile(ss.str());
//        a = b,b=b2,b2=a+b;
//    }
    AnalysisGen aGen = AnalysisGen(min,max);
    auto tStart = chrono::high_resolution_clock::now();
    aGen.appendToOldFile();
    auto tStop = chrono::high_resolution_clock::now();
    auto Totaltime = std::chrono::duration_cast<std::chrono::nanoseconds>(tStop - tStart).count();
    double time;
    string unit;
    if (Totaltime > 1000000000.00) {
        time = Totaltime / 1000000000.00;
        unit = "s";
    } else if (Totaltime > 1000000.00) {
        time = Totaltime / 1000000.00;
        unit = "ms";
    } else if (Totaltime > 1000.00) {
        time = Totaltime / 1000.00;
        unit = "us";
    } else {
        time = Totaltime;
        unit = "ns";
    }
    stringstream timeToStr;
    timeToStr << max << ',' << '0' << ',' << '0' << ',' << '0' << ',' << '0' << ',' << '0' << ',' << "NA" << ',' << time << ',' << unit << endl;
    aGen.insertToFile(timeToStr.str());
    return 0;
}