//
// Created by R.Peters on 11/5/2017.
//

#ifndef ASSIG3_ANALYSISGEN_H
#define ASSIG3_ANALYSISGEN_H

#include <iosfwd>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "RCPeters_GCD.h"
#include "WorkDir.h"



using namespace std;

class AnalysisGen {
private:
    string name = R"(~\GitHub_remotes\Fall_UWB_2017\css 342\assig3\GCD_Analysis_for_)";
    ofstream myFile;
    bool printToConsole = false;
    long long int  min, max;
    void populateCSV( const long long int &_min,
                     const long long int &_max);
    ofstream setUpNewFile( const long long int &_min,
                           const long long int &_max);
    void generatePrediction(const long long &_min,const long long  &_max);
public:
    AnalysisGen(const long long int &_min,
                const long long int &_max);
    AnalysisGen(const long long int &_min,
                const long long int &_max,const bool& printToConsole);

    AnalysisGen(const AnalysisGen&);

    ~AnalysisGen();
    void appendToOldFile( const long long int &_min,
                             const long long int &_max);
    void appendToOldFile();

    void insertToFile(const string &s);
};


#endif //ASSIG3_RCPETERS_ANALYSISGEN_H
