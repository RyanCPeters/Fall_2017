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
    generatePrediction(_min,_max);
    myFile = setUpNewFile(_min,_max);
}

/**
 *
 * @param aGen
 */
AnalysisGen::AnalysisGen(const AnalysisGen &aGen){

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

/**
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
    fName << name
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
//
//    myFile << "debug"<<endl;
    myFile.flush();
}

/**
 *
 * @param _min
 * @param _max
 * @param padding
 */
void AnalysisGen::expandData(const long long int &_min, const long long int &_max,
                             const long long int  &padding) {
//    myFile << "wtf won't shit write?\n";
    auto t1start = chrono::high_resolution_clock::now();
    auto t1end = chrono::high_resolution_clock::now();
    auto t2start = chrono::high_resolution_clock::now();
    auto t2end = chrono::high_resolution_clock::now();
    auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(t1end - t1start).count()/1000000;
    auto t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2end - t2start).count()/1000000;
    GCD init(_min,_max,-1);

    for(int pad = 0; pad < padding;++pad) {
        for  (long long int i = _min; i <= _max; ++i) {
            t1start = chrono::high_resolution_clock::now();
            GCD ofI(1, 2, i);
            for  (long long int a = 1; a < i; ++a) {
                for  (long long int b = i; b > a; --b) {
                    GCD tmp = GCD(a, b, i);
                    if (tmp == init)ofI = tmp;
                }// end for b
            }// end for a

            if (ofI == init) {
                t1end = chrono::high_resolution_clock::now();
                t2end = t1end;
                ofI.setI(pad);
                myFile << ofI;
                t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(t1end - t1start).count();
                t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2end - t2start).count();
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
                if(t2>1000000000.00){
                    time2 = t2/1000000000.00;
                    unit2 = "s";
                }else if(t2>1000000.00){
                    time2 = t2/1000000.00;
                    unit2 = "ms";
                }else if(t2>1000.00){
                    time2 = t2/1000.00;
                    unit2 = "us";
                }else{
                    time2 = t2;
                    unit2 = "ns";
                }

                myFile << "," << time1 << "," << unit1 << "," << time2 << "," << unit2<<endl;
                myFile.flush();
                t2start = t1end;
            }
        }// end for i
    }// end of for pad



}

/**
 *
 * @param _max
 */
void AnalysisGen::appendToOldFile(const long long int &_max) {
    if(_max > max){
        generatePrediction(min,_max);
        setUpNewFile(min,_max);
    }
    appendToOldFile(min,_max);
}

/**
 *
 */
void AnalysisGen::appendToOldFile() {
    appendToOldFile(min,max);
}

/**
 *
 * @param _min
 * @param _max
 */
void AnalysisGen::generatePrediction(const long long &_min,const long long &_max)
{
    stringstream fName;
    fName << R"(C:\Users\Peter\GitHub_remotes\Fall_UWB_2017\css 342\assig3\GCD_Prediction_for_)"
          << _min << "_to_" << _max << ".txt";
    cout << fName.str() << endl;
    ofstream predictFile;
    predictFile.open(fName.str());
    predictFile << "i,A,B,gcd,modulus operations\n";
    long long int a = 1, b = 2, b2 = a + b, r = 1, countMods = 0;
    if(a >= _min)predictFile << b << "," << a << "," << b << "," << r << "," << countMods << endl;
    while (b2 <= _max) {
        a = b, b = b2, b2 = a + b, ++countMods;
        if(a >= _min) {
            predictFile << b << "," << a << "," << b << "," << r << "," << countMods << endl;
            predictFile.flush();
        }
    }
    predictFile.close();
}

/**
 *
 * @param _min
 * @param _max
 */
void AnalysisGen::populateCSV( const long long int &_min,
                              const long long int &_max)
{
    auto t1start = chrono::high_resolution_clock::now();
    auto t1end = chrono::high_resolution_clock::now();
    auto t2start = chrono::high_resolution_clock::now();
    auto t2end = chrono::high_resolution_clock::now();
    auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(t1end - t1start).count()/1000000;
    auto t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2end - t2start).count()/1000000;
    GCD init(1,2,_min);
    vector<GCD> rawData;
    rawData.push_back(init);
    t2start = chrono::high_resolution_clock::now();
    for (long long int i = _min; i <= _max; ++i) {
        t1start = chrono::high_resolution_clock::now();
        GCD ofI(1,2,i);
        for  (long long int a = 1; a < i; ++a) {
            for  (long long int b = i; b > a; --b) {
                GCD tmp = GCD(a, b, i);
                if (tmp > ofI)ofI = tmp;
            }// end for b
        }// end for a

        if(ofI > rawData.back()){
            t1end = chrono::high_resolution_clock::now();
            t2end = t1end;

            myFile<<ofI;
            rawData.pop_back();
            rawData.push_back(ofI);
            /* t1 is recording the time it takes for a single loop of i to transpire
             * t2 is recording the actual interval between locating each successive greatest mod call conditions.
             * */
            t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(t1end - t1start).count();
            t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(t2end - t2start).count();
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
            if(t2>1000000000.00){
                time2 = t2/1000000000.00;
                unit2 = "s";
            }else if(t2>1000000.00){
                time2 = t2/1000000.00;
                unit2 = "ms";
            }else if(t2>1000.00){
                time2 = t2/1000.00;
                unit2 = "us";
            }else{
                time2 = t2;
                unit2 = "ns";
            }
            myFile << "," << time1 << "," << unit1 << "," << time2 << "," << unit2 << "\n";

            myFile.flush();
            t2start = t1end ;
        }
    }// end for i
}

/** void AnalysisGen::changeMinMax(const long long int &_min, const long long int &_max)
 *
 *  This function is used for messing around with the ranges of min and max without also changing the file
 *  that's being written to. If used irresponsibly, it will result in weird data.
 *
 * @param _min
 * @param _max
 */
void AnalysisGen::changeMinMax(const long long int &_min, const long long int &_max) {
    min = _min; max = _max;
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
