//
// Created by R.Peters on 11/5/2017.
//

#include <iostream>
#include <chrono>
#include "RCPeters_AnalysisGen.h"


using namespace std;


/**
 *
 * @param _min
 * @param _max
 */
AnalysisGen::AnalysisGen(const long long int &_min, const long long int &_max)
{
//
//    char buffer[MAX_PATH];
//    GetModuleFileName( NULL, buffer, MAX_PATH );
//    string::size_type pos = string( buffer ).find_last_of( "css_342" )+7;
//    name = string( buffer ).substr( 0, pos);

    stringstream ss;
    ss << WorkDir::GetWorkingDirectory();
    name = ss.str();
    cout << name << endl;
    name += "/GCD_";

    generatePrediction(_min,_max);
    myFile = setUpNewFile(_min,_max);
}



string AnalysisGen::getCurrDirectory() {

    return std::__cxx11::string();
}

/**
 *
 * @param aGen
 */
AnalysisGen::AnalysisGen(const AnalysisGen &aGen){
    name = aGen.name;
    myFile = setUpNewFile(aGen.min,aGen.max);
    generatePrediction(min,max);
}

/**
 *
 */
AnalysisGen::~AnalysisGen() {
    if(myFile.is_open()){
        myFile.flush();
        myFile.close();
    }
}


/**ofstream AnalysisGen::setUpNewFile( const long long int &_min,
 *                                 const long long int &_max)
 *
 * This is a private function that helps with modularity by seperating the process of getting directory path names
 * for creating the output file for the text based csv data generated when the driver file calls AnalysisGen::populateCSV(min,max)
 *
 * @param _min
 * @param _max
 * @return
 */
ofstream AnalysisGen::setUpNewFile( const long long int &_min,
                                   const long long int &_max)
{
    min = _min;
    max = _max;
    stringstream fName;
    ofstream myFile;
    fName << name << "Analysis_for_"
          << _min << "_to_" << _max << ".txt";
    cout << fName.str() << endl;
    myFile.open(fName.str(),ofstream::app);

    /*
     * for the time measurements we are using the labels t1 and t2.
     * t1 is recording the time, in milliseconds, it takes to find most mod calls gcd for a= [1,i-1], and b = [a+1,i]
     * t2 is recording the time, in milliseconds, between successful _max mod call findings.
     */
    myFile << "i,A,B,gcd,modulus operations,t1,t1Units,t2,t2Units\n";
    return myFile;
}

/**
 *
 * @param _min
 * @param _max
 */
void AnalysisGen::appendToOldFile( const long long int &_min,
                                   const long long int &_max)
{
    if(_min < min || _max > max){
        setUpNewFile( _min<min?_min:min, _max>max?_max:max );
        generatePrediction(_min<min?_min:min, _max>max?_max:max);
    }
    populateCSV(_min, _max);
    myFile.flush();
}


/**
 *
 */
void AnalysisGen::appendToOldFile() { appendToOldFile(min,max); }

/**
 *
 * @param _min
 * @param _max
 */
void AnalysisGen::generatePrediction(const long long &_min,const long long &_max)
{
    stringstream fName;
    fName << name<<"Prediction_for_"
          << _min << "_to_" << _max << ".txt";
    cout << fName.str() << endl;
    ofstream predictFile;
    predictFile.open(fName.str());
    predictFile << "i,A,B,gcd,modulus operations\n";
    long long int a = 1, b = 2, b2 = a + b, r = 1, countMods = 0;
    if(a >= _min)predictFile << b << "," << a << "," << b << "," << r << "," << countMods << endl;
    while (b2 <= _max) {
        a = b, b = b2, b2 = a + b, ++countMods;
        if(b >= _min) {
            predictFile << b << "," << a << "," << b << "," << r << "," << countMods << endl;
            predictFile.flush();
        }
    }
    predictFile.flush();
    predictFile.close();
}

/** void AnalysisGen::populateCSV( const long long int &_min,
 *                             const long long int &_max)
 *
 * This function populates the ofstream myfile class member with csv output data that provides detailed information
 * on each gcd calculation for i from _min to _max.
 *
 * @param _min
 * @param _max
 */
void AnalysisGen::populateCSV( const long long int &_min,
                              const long long int &_max)
{
    GCD mostMod = GCD(1,2,_min);
    double carryThemModTime = 0;
    auto t1start = chrono::high_resolution_clock::now();
    auto tend = chrono::high_resolution_clock::now();
    auto t2start = chrono::high_resolution_clock::now();
    t2start = chrono::high_resolution_clock::now();
    for (long long int i = _min; i <= _max; ++i) {
        t1start = chrono::high_resolution_clock::now();
        GCD ofI(1,2,i);
        for  (long long int a = 1; a < i; ++a) {
            for  (long long int b = i; b > a; --b) {
                GCD tmp = GCD(a, b, i);
                if (tmp >= ofI)ofI = tmp;
            }// end for b
        }// end for a


        tend = chrono::high_resolution_clock::now();
        bool newT2 = ofI > mostMod;
        myFile<<ofI;
        /* t1 is recording the time it takes for a single loop of i to transpire
         * t2 is recording the actual interval between locating each successive greatest mod call conditions.
         * */
        auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(tend - t1start).count();
        auto t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(tend - t2start).count();
        string unit1,unit2;
        double time1,time2;
        if(t1>1000000000.00){
            time1 = t1/1000000000.00;
            unit1 = "s";
        }else if(t1>1000000.00){
            time1 = t1/1000000.00;
            unit1 = "ms";
        }else if(t1>1000.00){
            time1 = t1/1000.00;
            unit1 = "us";
        }else{
            time1 = t1;
            unit1 = "ns";
        }
        if(newT2) {
            if (t2 > 1000000000.00) {
                time2 = t2 / 1000000000.00;
                unit2 = "s";
            } else if (t2 > 1000000.00) {
                time2 = t2 / 1000000.00;
                unit2 = "ms";
            } else if (t2 > 1000.00) {
                time2 = t2 / 1000.00;
                unit2 = "us";
            } else {
                time2 = t2;
                unit2 = "ns";
            }
            carryThemModTime = time2;
        }else{
            time2 = carryThemModTime;
            unit2 = "NA";
        }
        myFile << "," << time1 << "," << unit1 << "," << time2 << "," << unit2 << "\n";

        myFile.flush();

        if(newT2){
            mostMod = ofI;
            t2start = chrono::high_resolution_clock::now();
        }
    }// end for i
}



void AnalysisGen::insertToFile(const string &s) {
    if(myFile.is_open()){
        myFile<<s;
        myFile.flush();
    }
    else cout<<"shit went sideways when s = " << s << endl;

}

bool AnalysisGen::isFileOpen() {
    return myFile.is_open();
}


