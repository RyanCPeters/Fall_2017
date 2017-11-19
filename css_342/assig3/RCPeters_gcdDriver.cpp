#include <iostream>
#include <chrono>
#include "RCPeters_AnalysisGen.h"
using namespace std;

int main(int argc, char** argv) {
    bool printVerbose = false;
    long long int a =1,b=2,b2 = a+b, min = 1, max = 3000, padding = 100;
    if(argc < 3) {
        cout << "it appears that you only entered " << argc -1 << " command line arguments\nso we will need to double check"
             << "those values with the following 2 data prompts.\n\n";
        cout << "Please enter the minimum value you want to consider for this run of data generation.";
        cin >> min;
        cout << "Please enter the max value you want to consider for this run of data generation.";
        cin >> max;
    }else{
        stringstream ss;
        ss << argv[1] << " " <<argv[2];
        ss >> min;
        ss >> max;

    }

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