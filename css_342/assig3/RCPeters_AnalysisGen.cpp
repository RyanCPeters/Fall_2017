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
AnalysisGen::AnalysisGen(const long long int &_min, const long long int &_max):printToConsole(false)
{
//
//    char buffer[MAX_PATH];
//    GetModuleFileName( NULL, buffer, MAX_PATH );
//    string::size_type pos = string( buffer ).find_last_of( "css_342" )+7;
//    name = string( buffer ).substr( 0, pos);

    stringstream ss;
    ss << WorkDir::GetWorkingDirectory();
    name = ss.str();
//    cout << name << endl;
    name += "/GCD_";

    generatePrediction(_min,_max);
    myFile = setUpNewFile(_min,_max);
}

/** AnalysisGen::AnalysisGen(const long long int &_min, const long long int &_max, const bool &pToConsole):printToConsole(pToConsole)
 *
 * This constructor performs the initial set up of the class member ofstream myFile for later use as the data output storage.
 *
 *
 * @param _min the minimum value of i that shall be calculated
 * @param _max the maximum value of i that shall be calculated
 * @param pToConsole a boolean object that's used to indicate if output should also be sent to the console. Regardless of
 * what is passed to pToConsole, data will still be sent to the output file as always.
 */
AnalysisGen::AnalysisGen(const long long int &_min, const long long int &_max, const bool &pToConsole):printToConsole(pToConsole)
{
    stringstream ss;
    ss << WorkDir::GetWorkingDirectory();
    name = ss.str();
//    cout << name << endl;
    name += "/GCD_";

    generatePrediction(_min,_max);
    myFile = setUpNewFile(_min,_max);
}

/** AnalysisGen::AnalysisGen(const AnalysisGen &aGen)
 *
 * basic copy constructor, nothing to see here, move along ;)
 *
 * @param aGen the AnalysisGen object to be copied.
 */
AnalysisGen::AnalysisGen(const AnalysisGen &aGen){
    name = aGen.name;
    myFile = setUpNewFile(aGen.min,aGen.max);
    generatePrediction(min,max);
}

 /** AnalysisGen::~AnalysisGen()
 * Simple assures that the class member ofstream myFile is properly closed when the
 * program terminates.
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
 * This is a private function that helps with modularity by compartmentalizing the process of automatically
 * getting accurate directory path names for creating the output file for the text based csv data generated when the
 * driver file calls AnalysisGen::populateCSV(min,max).
 *
 * @param _min the minimum value of i that shall be calculated
 * @param _max the maximum value of i that shall be calculated
 * @return
 */
ofstream AnalysisGen::setUpNewFile( const long long int &_min,
                                   const long long int &_max)
{
    min = _min, max = _max;
    stringstream fName;
    ofstream myFile;
    fName << name << "Analysis_for_" << _min << "_to_" << _max << ".txt";
    cout << fName.str() << endl;
    myFile.open(fName.str(),ofstream::app);

    /*
     * for the time measurements we are using the labels t1 and t2.
     * t1 is recording the time, in milliseconds, it takes to find most mod calls gcd for a= [1,i-1], and b = [a+1,i]
     * t2 is recording the time, in milliseconds, between successful _max mod call findings.
     */
    myFile << "i,A,B,gcd, Mod Ops,T1,T1 Units,T2,T2 Units\n";
    return myFile;
}

/** void AnalysisGen::appendToOldFile( const long long int &_min,
 *                                  const long long int &_max)
 *
 * This function is writen with the assumption that the class member ofstream myFile has already been instanciated.
 *
 * Under that assumption, it checks to make sure that the values being passed to it do not violate the bounds expressed
 * in the name of the file. If they do, it will create a new file which states that it contains data withen the new bounds.
 *
 * @param _min the minimum integer value which shall be considered in the calculations.
 * @param _max the maximum integer value which shall be considered in the calculations.
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

/** void AnalysisGen::generatePrediction(const long long &_min,const long long &_max)
 *
 * This function uses a cheater algorithm to very quickly generate a condensed list of data which explicitly shows which
 * values of A and B in GCD will result in the next greatest number of modulus operations.
 *
 * @param _min the minimum integer value which shall be considered in the calculations.
 * @param _max the maximum integer value which shall be considered in the calculations.
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
    if(a >= _min){
        predictFile << b << "," << a << "," << b << "," << r << "," << countMods << endl;
//        cout << "At i = "<< _min << "; gcd ("<<a<<","<<b<<") = "<<r<<" took "<<countMods<<" modulus operations\n";
        if(!printToConsole)printf("At i=%-4lli; gcd (%-4lli,%-4lli) = %-lli took %-3lli modulus operations\n",b,a,b,r,countMods);
    }
    while (b2 <= _max) {
        a = b, b = b2, b2 = a + b, ++countMods;
        if(b >= _min) {
            predictFile << b << "," << a << "," << b << "," << r << "," << countMods << endl;
            predictFile.flush();
//            cout << "At i = "<< _min << "; gcd ("<<a<<","<<b<<") = "<<r<<" took "<<countMods<<" modulus operations\n";
            if(!printToConsole)printf("At i=%-4lli; gcd (%-4lli,%-4lli) = %-lli took %-3lli modulus operations\n",b,a,b,r,countMods);
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
 * @param _min the minimum integer value which shall be considered in the calculations.
 * @param _max the maximum integer value which shall be considered in the calculations.
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
                if(printToConsole)printf("At i=%-4lli; gcd (%-4lli,%-4lli) = %-lli took %-3lli modulus operations\n",tmp.getI(),tmp.getA(),tmp.getB(),tmp.getGCD(), tmp.getModCalls());
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


/** void AnalysisGen::insertToFile(const string &s)
 *
 * This function serves as an interface for client programs to append lines of data or specific flag values into
 * the output file for later reference.
 *
 * If I knew more about how to properly utilize excel spreadsheets, this function would have been better utilized in
 * creating earmarked data points for more readable data.
 *
 * @param s the string representation of the data to be appended to the output file.
 */
void AnalysisGen::insertToFile(const string &s) {
    if(myFile.is_open()){
        myFile<<s;
        myFile.flush();
    }
    else cout<<"shit went sideways when s = " << s << endl;

}





