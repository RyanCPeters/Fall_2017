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
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir getcwd

#elif __linux__ // must be in linux
#include <unistd.h>
#define GetCurrentDir getcwd

#elif __linux
#include <unistd.h>
#define GetCurrentDir getcwd

#elif linux
#include <unistd.h>
#define GetCurrentDir getcwd

#endif


using namespace std;

class AnalysisGen {
private:
    string name = R"(~\GitHub_remotes\Fall_UWB_2017\css 342\assig3\GCD_Analysis_for_)";
    ofstream myFile;
    long long int  min,// =  long long int )1,
                            max;// =  long long int )14757395258967641292;
    void populateCSV( const long long int &_min,
                     const long long int &_max);
    ofstream setUpNewFile( const long long int &_min,
                           const long long int &_max);
    void generatePrediction(const long long &_min,const long long  &_max);
    string getCurrDirectory();
public:
    AnalysisGen(const long long int &_min,
                const long long int &_max);

    AnalysisGen(const AnalysisGen&);

    ~AnalysisGen();
    void buildDataSet(const long long int &_min,
                      const long long int &_max,
                      const long long int &padding);
    void appendToOldFile( const long long int &_min,
                             const long long int &_max);
    void appendToOldFile( const long long int &_max);
    void appendToOldFile();
    bool isFileOpen();

    void changeMinMax(const long long int &_min,
                      const long long int &_max);

    void insertToFile(const string &s);
};


#endif //ASSIG3_RCPETERS_ANALYSISGEN_H
