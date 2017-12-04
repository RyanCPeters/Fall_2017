#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cassert>
#include "mergesortImproved.cpp"         // implement your mergesort
#include "mergesort.cpp"
#include "quicksort.cpp"
//#include "dist/json/json-forwards.h"
//#include "dist/jsoncpp.cpp"

using namespace std;
static const int MAX_COLLECTION_SIZE = 25000, MAX_INT_VAL = (int)(INT_MAX*.9);
static const int SEED_VALUE = 1;
const chrono::milliseconds waitForPausedTime(1);
static const string SECONDS = "s", MILLI_Seconds = "ms", MICRO_SECONDS = "us", NANO_SECONDS = "ns",
        AUTO_SELECT = "---";
static const string FUNC_NAMES[3] = {"quicksort","mergesort","mergesortImproved"};


/**
 *
 * @tparam Comparable
 * @param array
 * @param funcType
 * @param theFile
 * @param size
 */
template <class Comparable>
void printToConsole(ofstream &theFile,
                    const vector<Comparable> &array,
                    const string &funcType,
                    const int &size,
                    const long double &myTime,
                    const string &unit,
                    const bool &finishedSortState) {
  int i = -1;
  theFile << endl << "Array size = " << size << endl;
  theFile.flush();
  for ( const auto &ele:array) {
    theFile << funcType << "[" << ++i << "] = " << ele << endl;
    theFile.flush();
  }
}

/**
 *
 * @tparam Comparable
 * @param array
 * @param funcType
 * @param theFile
 * @param size
 */
void printFileTerse(ofstream &theFile, const int &funcType, const int &size, const long double &myTime) {
  string endLineChar = (funcType == 2)? "\n" : ", ";
  theFile << FUNC_NAMES[funcType] << "," << size << ", " << myTime << endLineChar;
  theFile.flush();
}

/**
 *
 * @tparam Comparable
 * @param array
 * @param funcType
 * @param theFile
 * @param size
 */
template <class Comparable>
void printFileVerbose(ofstream &theFile,
                      const string &funcType,
                      const int &size,
                      const long double &myTime,
                      const string &unit,
                      const bool &finishedSortState) {
  
  theFile << size << ", " << funcType << ", " << myTime << ", " << unit << ", "
          << finishedSortState << endl;

  theFile.flush();
}

/**
 *
 * @tparam Comparable
 * @param data
 * @param numElems
 * @return
 */
ofstream initOutFile( const string &dataName) {
  stringstream ss;
  ss << "/"<< dataName << "_out_data" << ".txt";
  string fileName = ss.str();
  ss.str(string());
  string dirPath = WorkDir::GetWorkingDirectory();
  dirPath = dirPath+fileName;
  ofstream myfile(dirPath,ofstream::app);
  return myfile;
}

/** void setTimeAndUnits(const long double &totalTime, long double &time, string &units, const string &specificUnitsDesired)
 *
 * @param totalTime the raw elapsed myTime data variable for which you wish to derive a 'time in units'
 *          value for.
 *
 * @param myTime the long double variable where you want the derived myTime value to be stored
 *
 * @param units the string reference for where you want the derived unit string to be stored
 *
 * @param specificUnitsDesired should be one of the following:
 *          "s" for seconds        use the already defined static const string SECONDS
 *          "ms" for milli-seoncds use the already defined static const string MILLI_SECONDS
 *          "us" for micro-seconds use the already defined static const string MICRO_SECONDS
 *          "ns" for nano-seconds  use the already defined static const string NANO_SECONDS
*         defaults to using NANO_SECONDS.
 */
void setTimeAndUnits(const long double &totalTime, long double &myTime, string &units,
                     const string &specificUnitsDesired = AUTO_SELECT)
{
  if(specificUnitsDesired.size() == 3) {
    if (totalTime > 1E+9) {
      myTime = totalTime / 1E+9;
      units = "seconds";
    } else if (totalTime > 1E+6) {
      myTime = totalTime / 1E+6;
      units = "milli-seconds";
    } else if (totalTime > 1E+3) {
      myTime = totalTime / 1E+3;
      units = "micro-seconds";
    } else {
      myTime = totalTime;
      units = "nano-seconds";
    }
  }else{
    string seconds = "s", milli_seconds = "ms", micro_seconds = "us", nano_seconds = "ns";
    if(specificUnitsDesired == seconds){
      myTime = totalTime / 1E+9;
      units = "seconds";
    }else if(specificUnitsDesired == milli_seconds){
      myTime = totalTime / 1E+6;
      units = "milli-seconds";
    }else if(specificUnitsDesired == micro_seconds){
      myTime = totalTime / 1E+3;
      units = "micro-seconds";
    }else if(specificUnitsDesired == nano_seconds){
      myTime = totalTime;
      units = "nano-seconds";
    }else{
      cout << "wonky input for desired myTime units, defaulting to micro-seconds"<<endl;
      myTime = totalTime / 1E+3;
      units = "micro-seconds";
    }
  }
}

/**
 *
 * @param array
 * @param randMax
 */
void initArray(vector<int> &array, const int &randMax) {
  int tmp, j;
  for ( int i = 0; i < randMax;) {
    tmp =  rand( ) % randMax;
    for ( j = 0; j < i && array[j] != tmp; ++j );
    if ( j==i )array.push_back(tmp),++i;
  } // end of for i
}// end of initArray function.

template <class Comparable>
vector<Comparable> initCollectionRef(const Comparable &typeSample, const int &sizeToUse) {
  vector<Comparable> tmp;
  initArray(tmp, sizeToUse);
  tmp.shrink_to_fit();
  return tmp;
}

template <class Comparable>
void populateCollectionRef(vector<vector<Comparable>> &collectionRef, const vector<Comparable> &randomSourceVect)
{
  int internalRefSize = 1;
  while (internalRefSize < randomSourceVect.size()-1){
    vector<Comparable> internalRef;
    internalRef.assign( randomSourceVect.begin(),randomSourceVect.end()-(MAX_COLLECTION_SIZE - internalRefSize));
    internalRef.shrink_to_fit();
    collectionRef.push_back(internalRef);
    internalRefSize += 20;
  }
  collectionRef.push_back(randomSourceVect);
  collectionRef.shrink_to_fit();
  
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main( int argc, char *argv[] ) {
  // verify arguments
  
  if ( argc != 2 ) {
    cerr << "usage: a.out size" << endl;
    return -1;
  }
  
  // verify an array size
  auto size = strtol( argv[1], nullptr, 10 );
  if ( size <= 0 ) {
    cerr << "array size must be positive" << endl;
    return -1;
  }
  
  ofstream  compositeDataFile= initOutFile("composite_time");
  
  compositeDataFile << "qsort,size,time,msort,size,time,msortImp,size,time\n";
  
  compositeDataFile.flush();
  
  quicksort qs;
  mergesort ms;
  mergesortImproved msi;
  
  srand(SEED_VALUE);

  cout << "Please wait while the item collections are randomly generated with a seed value of "
       << SEED_VALUE << endl;
  vector<vector<int>> collectionRef;
  vector<int> biggest = initCollectionRef(1,MAX_COLLECTION_SIZE);
  
  populateCollectionRef(collectionRef, biggest);
  cout << "random data has been generated, now to begin testing the sorting algos."<< endl;
  
  int dataBuilderMax = 20;
  int maxTotalLoops = (int)collectionRef.size() * dataBuilderMax * 3,
  loopCount = 0, modVal = maxTotalLoops/10,tenPercent = 1;
  
  for(int collectionIndex = 1; collectionIndex < collectionRef.size()/*this is 1000 * micro-seconds*/;++collectionIndex){
    for(int dataBuildingLoop = 0; dataBuildingLoop < dataBuilderMax; ++dataBuildingLoop){
      for(int cycleSorters = 0;cycleSorters < 3 ; ++cycleSorters) {
        ++loopCount;
        string endLiner = (cycleSorters == 2)?"\n" : ", ";
        if(loopCount%modVal == 0)cout << (tenPercent++)*10 << "% of loops complete\ncurrently performing "
                                      << FUNC_NAMES[cycleSorters] << endl;
        vector<int> items = collectionRef.at(collectionIndex);
        
        items.shrink_to_fit();
        
        auto theSize = (int)items.size();
        
        auto tStart = chrono::high_resolution_clock::now(), tStop = chrono::high_resolution_clock::now();
        
        switch (cycleSorters){
          case 0://collecting myTime data for the quicksort algo on the unsorted items vector.
            tStart = chrono::high_resolution_clock::now();
            qs.beginSorting(items);
            tStop = chrono::high_resolution_clock::now();
            break;
          case 1://collecting myTime data for the mergesort algo on the unsorted items vector.
            tStart = chrono::high_resolution_clock::now();
            ms.beginSorting(items);
            tStop = chrono::high_resolution_clock::now();
            break;
          case 2://collecting myTime data for the mergesortImproved algo on the unsorted items vector.
            tStart = chrono::high_resolution_clock::now();
            msi.beginSorting(items);
            tStop = chrono::high_resolution_clock::now();
            break;
          default:
            break;
        }
        
        long double myTime = 0;
        auto elapsedTime = chrono::duration_cast<std::chrono::nanoseconds>(tStop - tStart).count();
        string unit;
        // if you desire the data to be sent to the output file in a myTime unit other than
        // micro-seconds,
        // then replace the last parameter with the unit specifier you desire from the static const
        // strings at the top of the file.
        setTimeAndUnits(elapsedTime,myTime,unit,NANO_SECONDS);
        
        
        
        /* Explanation for bool finishedSortState:
         *
         * finishedSortState is used in the debugging process to mark where a collection was or was not
         * successfully sorted. This checking device only works for decimal values where the values
         * range from 0 to MAX_COLLECTION_SIZE.
         *
         * finishedSortState is true so long as items.at(checkAtIdx) <= items.at(checkAtIdx+1).
         *
         */
        bool finishedSortState = true;
        
        /* Explanation on the use of checkAtIdx bellow:
         *
         * checkAtIdx is just an index marker used for checking that the values of sequential indices
         * are always growing.
         *
         * These collections use 0-based indexing, so a collection will contain values between 0 and
         * collectionSize-1; where each value will be stored at an index position that matches its value.
         */
        unsigned int checkAtIdx = 0;
        
        while (theSize > 1 && checkAtIdx < items.size()-1 && finishedSortState ) {
          if(finishedSortState)finishedSortState = items.at(checkAtIdx) <= items.at(checkAtIdx+1);
          ++checkAtIdx;
        } // end of while loop
  
        printFileTerse(compositeDataFile, cycleSorters, theSize, myTime);
        compositeDataFile.flush();
        
        if(!finishedSortState){
          this_thread::sleep_for(waitForPausedTime);
          cerr << "failure occured \nAlgorithm:" << FUNC_NAMES[cycleSorters]
               << "\ncollection size: " << theSize
               << "\ncollectionIndex: " << collectionIndex
               << "\nindex of failure (checkAtIdx): " << checkAtIdx
               << endl << endl;
          cerr.flush();
          this_thread::sleep_for(waitForPausedTime);
        }
        compositeDataFile.flush();
      }// end of for-cycleSorters loop
//      qsortDFile.flush(), msortDFile.flush(), mIsortDfile.flush();
    } // end for-dataBuildingLoop loop :P
  } // end of for- collectionIndex loop
  compositeDataFile.close();
//  qsortDFile.close(), msortDFile.close(), mIsortDfile.close();
  return 0;
} 
