#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cassert>
#include <iomanip>
#include <fstream>

#include "mergesortImproved.cpp"         // implement your mergesort
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "WorkDir.h"

using namespace std;
static const int MAX_COLLECTION_SIZE = 25000, SUB_COLLECTION_INCREMENTS = 1;
static const int SEED_VALUE = 1;
const chrono::milliseconds waitForPausedTime(1);
static const string SECONDS = "s", MILLI_Seconds = "ms", MICRO_SECONDS = "us", NANO_SECONDS = "ns",
        AUTO_SELECT = "---";
static const string FUNC_NAMES[3] = {"quicksort","mergesort","mergesortImproved"};
static const string ERR_FILE_NAME = "errFile";


/**
 *
 * @tparam Comparable
 * @param theFile
 * @param array
 * @param funcType
 * @param size
 * @param myTime
 * @param unit
 * @param finishedSortState
 */
template <class Comparable>
void printToConsole(ofstream &theFile, const vector<Comparable> &array, const string &funcType,
                    const int &size, const long double &myTime, const string &unit, const bool &finishedSortState)
{
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
 * @param theFile
 * @param funcType
 * @param myTime
 * @param endLineChar
 */
void printFileTerse(ofstream &theFile, const int &funcType, const long double &myTime, const string &endLineChar)
{
  theFile << FUNC_NAMES[funcType] << ", " << myTime << endLineChar;
  theFile.flush();
}

/**
 *
 * @param theFile
 * @param funcType
 * @param size
 * @param idxOfFailur
 */
void printToErrFile(ofstream &theFile,const int &funcType,const int &size,const int &idxOfFailur)
{
  
  theFile << "failure for " << FUNC_NAMES[funcType] << " at idx " << idxOfFailur
          << " in a collection size of "<< size << endl;

  theFile.flush();
}

/**
 *
 * @param dataName
 * @return
 */
ofstream initOutFile( const string &dataName) {
  stringstream ss;
  string fileType = (dataName == ERR_FILE_NAME)? "": "_out_data" ;
  ss << "/"<< dataName << fileType << ".txt";
  string fileName = ss.str();
  ss.str(string());
  string dirPath = WorkDir::GetWorkingDirectory();
  dirPath = dirPath+fileName;
  ofstream myfile(dirPath,ofstream::app);
  return myfile;
}

/**
 *
 * @param totalTime
 * @param myTime
 * @param units
 * @param specificUnitsDesired
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
void initArray(vector<int> &array, const int &randMax)
{
  int tmp, j;
  for ( int i = 0; i < randMax;) {
    tmp =  rand( ) % randMax;
    array.push_back(tmp),++i;
//    for ( j = 0; j < i && array[j] != tmp; ++j );
//    if ( j==i )array.push_back(tmp),++i;
  } // end of for i
}// end of initArray function.

/**
 *
 * @tparam Comparable
 * @param typeSample
 * @param sizeToUse
 * @return
 */
template <class Comparable>
vector<Comparable> initBiggestRandomCollection(const Comparable &typeSample, const int &sizeToUse)
{
  vector<Comparable> tmp;
  initArray(tmp, sizeToUse);
  tmp.shrink_to_fit();
  return tmp;
}

/**
 *
 * @param qs
 * @param ms
 * @param msI
 * @param biggest
 * @param collectionIndex
 * @param cycleSorters
 * @param unit
 * @param myTime
 * @param items
 */
void generateTimeData(quicksort &qs, mergesort &ms, mergesortImproved &msI, vector<int> &biggest,
                             const int &collectionIndex, const int &cycleSorters, string &unit,
                             long double &myTime, vector<int> &items)
{
  items.assign(biggest.begin(), biggest.begin() + collectionIndex);
  
  items.shrink_to_fit();
  
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
      msI.beginSorting(items);
      tStop = chrono::high_resolution_clock::now();
      break;
    default:
      break;
  }
  auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(tStop - tStart).count();
  setTimeAndUnits(elapsedTime,myTime,unit,NANO_SECONDS);
}

/**
 *
 * @param collectionIndex
 * @param cycleSorters
 * @param endLiner
 * @param myTime
 * @param items
 * @param compositeDataFile
 * @param errFile
 */
void sortedCollectionValidation(int collectionIndex, int cycleSorters, const string &endLiner, long double myTime,
                                vector<int> &items, ofstream &compositeDataFile, ofstream &errFile)
{
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
  
  while (collectionIndex > 1 && checkAtIdx < items.size()-1 && finishedSortState) {
    finishedSortState = items.at(checkAtIdx) <= items.at(checkAtIdx+1);
    ++checkAtIdx;
  } // end of while loop
  
  // this if block is determining whether we need errFile output
  if(finishedSortState) {
    printFileTerse(compositeDataFile, cycleSorters, myTime, endLiner);
  }else{
    cout << "failure for " << FUNC_NAMES[cycleSorters] << " at idx " << checkAtIdx
         << " in a collection size of "<< collectionIndex << endl;
    int failedAt = static_cast<int>(checkAtIdx);
    printToErrFile(errFile,cycleSorters,collectionIndex,failedAt);
    compositeDataFile << FUNC_NAMES[cycleSorters] << " error" << ", " << "-" << checkAtIdx << endLiner;
  }
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int main( int argc, char *argv[] )
{
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
  
  
  srand(SEED_VALUE);
  
  cout << "Please wait while the item collections are randomly generated with a seed value of "
       << SEED_VALUE << endl;
  vector<int> biggest = initBiggestRandomCollection(1, MAX_COLLECTION_SIZE);
  
  cout << "random data has been generated, now to begin testing the sorting algos."<< endl;
  
  
  // setting up control variables
  int     dataBuilderMax = 20, // this simply adds loop-passes at each sorter/collection configuration for averaging later
          startCycleSorters = 0,
          endCycleSorters = 3;
  
  int numOfSubCOllections = static_cast<int>(biggest.size())/SUB_COLLECTION_INCREMENTS ;
  
  float maxTotalLoops = (numOfSubCOllections) * dataBuilderMax * (endCycleSorters - startCycleSorters);
  
  ofstream  compositeDataFile= initOutFile("composite_time"),
           errFile = initOutFile("errFile");
  
  /*
   setting up an error output file in order to track the results of different changes while debugging.
   */
  errFile  << endl << endl << "new run --" << endl << "conditions:" << endl
          << "\t" << setw(16) << "static const int" << left << setw(27)<< " MAX_COLLECTION_SIZE" << "= " << MAX_COLLECTION_SIZE << endl
          << "\t" << setw(16) << "static const int" << left << setw(27)<< " SUB_COLLECTION_INCREMENTS" << "= " << SUB_COLLECTION_INCREMENTS << endl
          << "\t" << setw(16) << "static const int" << left << setw(27)<< " SEED_VALUE" << "= " << SEED_VALUE << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " dataBuilderMax" << "= " << dataBuilderMax << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " startCycleSorters" << "= " << startCycleSorters << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " endCycleSorters" << "= " << endCycleSorters << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " numOfSubCOllections" << "= " << numOfSubCOllections << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " maxTotalLoops" << "= " << maxTotalLoops << endl;
  
  errFile.flush();
  
  compositeDataFile << "size, qsort,qs time,msort,ms time,msortImp,msi time\n";
  
  compositeDataFile.flush();
  
  quicksort qs;
  mergesort ms;
  mergesortImproved msI;
  
  
  float loopCount = 0;
  int curPercent = 0;
  for(int collectionIndex = 0; collectionIndex < biggest.size(); collectionIndex += SUB_COLLECTION_INCREMENTS){
    compositeDataFile << collectionIndex << ", ";
    for(int cycleSorters = startCycleSorters;cycleSorters < endCycleSorters ; ++cycleSorters) {
      for(int dataBuildingLoop = 0; dataBuildingLoop < dataBuilderMax; ++dataBuildingLoop){
        ++loopCount;
        string endLiner = (cycleSorters+1 == endCycleSorters)?"\n" : ", ";
        double percent = (loopCount/maxTotalLoops)*100;
        if(static_cast<int>(percent )> curPercent){
          curPercent = static_cast<int>(percent);
          cout << curPercent << "% complete" << endl;
        }
        
        long double myTime = 0;
        string unit;
        vector<int> items;
        
        generateTimeData(qs, ms, msI, biggest, collectionIndex, cycleSorters, unit, myTime, items);
        
        // this call compartmentalizes the process of
        sortedCollectionValidation(collectionIndex, cycleSorters, endLiner, myTime, items, compositeDataFile, errFile);
        
        compositeDataFile.flush();
      }// end of for-cycleSorters loop
    } // end for-dataBuildingLoop loop :P
  } // end of for- collectionIndex loop
  compositeDataFile.close();
  errFile.close();
  return 0;
}


