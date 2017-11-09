//
// Created by R.Peters on 11/5/2017.
//

#ifndef ASSIG3_ANALYSISGEN_H
#define ASSIG3_ANALYSISGEN_H

#include <iosfwd>
#include <vector>
#include <fstream>
#include <sstream>
#include "RCPeters_GCD.h"


using namespace std;

class AnalysisGen {
private:
    ofstream myFile;

    AnalysisGen();

    void populateCSV(ofstream &file,const unsigned int &min, const unsigned int &max);

public:
    AnalysisGen(const unsigned int &min,const double &max);
};


#endif //ASSIG3_RCPETERS_ANALYSISGEN_H
