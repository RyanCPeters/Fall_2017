#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "mergesortImproved.cpp"         // implement your mergesort
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "WorkDir.h"

using namespace std;
static const int MAX_COLLECTION_SIZE = 10000, SUB_COLLECTION_INCREMENTS = 1;
static const int SEED_VALUE = 1;
const chrono::milliseconds waitForPausedTime(1);
static const string SECONDS = "s", MILLI_Seconds = "ms", MICRO_SECONDS = "us", NANO_SECONDS = "ns",
        AUTO_SELECT = "---";
static const string FUNC_NAMES[3] = {"quicksort","mergesort","mergesortImproved"};
static const string ERR_FILE_NAME = "errFile";
stringstream errDataInit;

/**
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param theFile
 * @param array
 * @param funcType
 */
template <class Comparable>
void printToConsole(ofstream &theFile, const vector<Comparable> &array, const string &funcType)
{
  theFile << "Array size = " << array.size() << endl;
  theFile.flush();
//  unsigned int interval = 64,loopMultiplier = 1;
  
//  for (unsigned int i = 0; i+interval*5*loopMultiplier < array.size();) {
//    int lineMultiplier = 0;
//    theFile<< funcType << "[" << setw(5) <<  i << "] = " << setw(5) << array[i+interval*(lineMultiplier++)*loopMultiplier]
//           << ",\t" << funcType << "[" << setw(5) << i+interval << "] = " << setw(5) << array[i+interval*(lineMultiplier++)*loopMultiplier]
//           << ",\t" << funcType << "[" << setw(5) << i+interval*(lineMultiplier)*loopMultiplier << "] = " << setw(5) << array[i+interval*(lineMultiplier++)*loopMultiplier]
//           << ",\t" << funcType << "[" << setw(5) << i+interval*(lineMultiplier)*loopMultiplier << "] = " << setw(5) << array[i+interval*(lineMultiplier++)*loopMultiplier]
//           << ",\t" << funcType << "[" << setw(5) << i+interval*(lineMultiplier)*loopMultiplier << "] = " << setw(5) << array[i+interval*(lineMultiplier++)*loopMultiplier]
//           << ",\t" << funcType << "[" << setw(5) << i+interval*(lineMultiplier)*loopMultiplier << "] = " << setw(5) << array[i+interval*(lineMultiplier)*loopMultiplier]
//           << endl;
//    theFile.flush();
//    if(i > 0 && i % (interval-1) == 0){
//      i = i+interval*(lineMultiplier)*loopMultiplier +1;
//      ++loopMultiplier;
//      theFile << endl;
//    }else{
//      ++i;
//    }
//  }
  
  for (unsigned int i = 1; i < array.size();++i) {
    if(i%10 == 0)theFile<<endl;
    
    theFile<< setw(5) << array[i-1]<< ", ";
    theFile.flush();
    
  }
  theFile << endl << endl;
}

/**
 *
 * @param theFile
 * @param dataSize
 * @param avgTimes
 */
void printFileTerse(ofstream &theFile, const int &dataSize, const vector<long double>  &avgTimes)
{
  theFile << dataSize
          << ", " << FUNC_NAMES[0] << ", " << avgTimes[0]
          << ", " << FUNC_NAMES[1] << ", " << avgTimes[1]
          << ", " << FUNC_NAMES[2] << ", " << avgTimes[2]
          << endl;
  theFile.flush();
}

/** void printToErrFile(ofstream &theFile,const int &funcType,const int &size,const int &idxOfFailur)
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

/** ofstream initOutFile( const string &dataName)
 *
 * @param dataName
 * @return
 */
ofstream initOutFile( const string &dataName)
{
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

/** void setTimeAndUnits(const long double &totalTime, long double &myTime, string &units, const string &specificUnitsDesired = AUTO_SELECT)
 *
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

/** template <class Comparable> void initArray(vector<Comparable> &array, const int &randMax)
 *
 * generates the random values used in sorting algorithm comparisons.
 *
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param array the     vector reference to where you want your random values stored
 *
 * @param randMax       a constant int reference to your choice in what the maximum random value should be. This also serves
 *                      the secondary purpose of determining the size of your collection. By having your maximum allowed value
 *                      be the same as the total size of the collection, you can create a set (meaning no duplicated values)
 *                      of random numbers by utilizing the inner-for-loop and the if-statement that follows it.
 */
template <class Comparable>
void initArray(vector<Comparable> &array, const int &randMax)
{
  int tmp, j;
  for ( int i = 0; i < randMax;) {
    tmp =  rand( ) % randMax; // using the modulus operator with randMax ensures we never get values larger than randMax
    
    /* Note that the following line, and the two commented lines that follow it should be treated as mutually-exclusive.
     *
     * Meaning, if you wish to have a set of all unique values:
     *    Comment out the following line of code
     *    then, un-comment the subsequent two lines.
     */
    array.push_back(tmp),++i;               // This will permit duplicate values in the collection.
    
//    for (j=0; j<i && array[j]!=tmp; ++j); // This, and the next, line of code will prevent any duplicate values
//    if ( j==i )array.push_back(tmp),++i;  // in your collection; however, note that it can also take a lot longer to
                                            // build large collections. (large as in values over 1000)
  } // end of for i
}// end of initArray function.


/**void generateTimeData(quicksort &qs, mergesort &ms, mergesortImproved &msI, const int &cycleSorters, long double &elapsedTime, vector<int> &items)
 *
 *
 * @param qs
 * @param ms
 * @param msI
 * @param cycleSorters
 * @param elapsedTime
 * @param items
 */
void generateTimeData(quicksort &qs, mergesort &ms, mergesortImproved &msI, const int &cycleSorters,
                             long double &elapsedTime, vector<int> &items)
{
  
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
  elapsedTime = chrono::duration_cast<chrono::nanoseconds>(tStop - tStart).count();
}

/**void validateSort(const int &collectionIndex, const int &cycleSorters, long double &myTime, vector<int> &items, ofstream &compositeDataFile, ofstream &errFile, vector<long double> &timeSums)
 *
 * @param collectionIndex
 * @param cycleSorters
 * @param myTime
 * @param items
 * @param compositeDataFile
 * @param errFile
 * @param timeSums
 */
void validateSort(const int &collectionIndex, const int &cycleSorters, long double &myTime,
                  vector<int> &items, ofstream &compositeDataFile, ofstream &errFile, vector<long double> &timeSums)
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
    timeSums[cycleSorters] += myTime;
  }else{
    // if errDataInit has something in it, then we must be at our first error and it's time to initialize ofstream errFile;
    if(errDataInit.rdbuf()->in_avail() > 0) {
      errFile = initOutFile("errFile");
      errFile << errDataInit.str();
      errDataInit.str(string()); // now we clear errDataInit to make sure we don't re-initialize errFile.
    }
    int failedAt = static_cast<int>(checkAtIdx);
    printToErrFile(errFile,cycleSorters,collectionIndex,failedAt);
  
    errFile << endl << setfill('/') << setw(75)  << " " << endl << endl;
    errFile << setfill(' ');
    for(unsigned int i = 0; i < items.size()-1;++i)
      if( items.at(i) > items.at(i+1)) {
        
        errFile << FUNC_NAMES[cycleSorters] << "[" << setw(5) << i-1 << "] = " << setw(5) << items[i-1] << endl;
        errFile << FUNC_NAMES[cycleSorters] << "[" << setw(5) << i << "] = " << setw(5) << items[i] << "<--"<< endl;
        errFile << FUNC_NAMES[cycleSorters] << "[" << setw(5) << i+1 << "] = " << setw(5) << items[i+1] << endl << endl;
      }
  }
}

/** int main( int argc, char *argv[] )
 *
 * @param argc      The number of arguments passed on the command line.
 *                  If argc == 1, then no additional arguments were passed, as the first argument is always the
 *                  name of the executable file.
 *
 * @param argv      An array of c_strings containing any command-line arguments beyond the initial executable's name.
 * @return  the error code should any be thrown, otherwise 0 when all goes well.
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
  vector<int> biggest;
  
  cout << "Please wait while the item collections are randomly generated with a seed value of "
       << SEED_VALUE << endl;
  initArray(biggest,MAX_COLLECTION_SIZE);
  cout << "random data has been generated, now to begin testing the sorting algos."<< endl;
  
  
  // setting-up loop-control variables
  
  /*
   startCycleSorters -- Determines the starting index for the cycleSorters loop variable. Changing this value allows you
                        to bypass a particular sorter if you wish.
                        
   endCycleSorters   -- Determines the ending index for the cycleSorters loop variable. Changing this value allows you
                        to bypass a particular sorter if you wish.
                        
   The sorting algorithms by index:
                                    0 -- Quicksort
                                    1 -- Mergesort
                                    2 -- MergesortImproved
   */
  int startCycleSorters = 0,
      endCycleSorters = 3;
  
  /*
   extraDataMax expresses the desired number of additional loop-passes at each collection size for each sorter,
   these additional loops will be used to generate more accurate averages of time complexity later on.
   */
  int extraDataMax = 1;
  
  int numOfSubCOllections = static_cast<int>(biggest.size())/SUB_COLLECTION_INCREMENTS ;
  
  float maxTotalLoops = (numOfSubCOllections) * extraDataMax * (endCycleSorters - startCycleSorters);
  
  ofstream  compositeDataFile= initOutFile("composite_time");
  ofstream errFile;
//  ofstream unsortedCollectionRef = initOutFile("rawCollections");
  
  /*
   collecting the relevant data that will be used should an error case be found in the sorted datas.
   */
  errDataInit  << endl << endl << "new run --" << endl << "conditions:" << endl
          << "\t" << setw(16) << "static const int" << left << setw(27)<< " MAX_COLLECTION_SIZE" << "= " << MAX_COLLECTION_SIZE << endl
          << "\t" << setw(16) << "static const int" << left << setw(27)<< " SUB_COLLECTION_INCREMENTS" << "= " << SUB_COLLECTION_INCREMENTS << endl
          << "\t" << setw(16) << "static const int" << left << setw(27)<< " SEED_VALUE" << "= " << SEED_VALUE << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " extraDataMax" << "= " << extraDataMax << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " startCycleSorters" << "= " << startCycleSorters << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " endCycleSorters" << "= " << endCycleSorters << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " numOfSubCOllections" << "= " << numOfSubCOllections << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " maxTotalLoops" << "= " << maxTotalLoops << endl;
  
  compositeDataFile <<  setw(12) << "size" << ","
                    <<  setw(12) << "qsort" << ","
                    <<  setw(12) << "qs time" << ","
                    <<  setw(12) << "msort" << ","
                    <<  setw(12) << "ms time" << ","
                    <<  setw(12) << "msortImp" << ","
                    <<  setw(12) << "msi time" << endl;
  
  compositeDataFile.flush();
  
  quicksort qs;
  mergesort ms;
  mergesortImproved msI;
  
  // This print is just to generate a reference file for what the unsorted values in the collection look like.
//  printToConsole(unsortedCollectionRef,biggest,"");
  
  
  float loopCount = 0;  // only used in the generation of the percentage values output to the console as status updates.
  int curPercent = 0;   // only used in the generation of the percentage values output to the console as status updates.
  vector<long double> avgTimes = {0,0,0};
  for(int desiredCollectionSize = 0; desiredCollectionSize < biggest.size(); desiredCollectionSize += SUB_COLLECTION_INCREMENTS){
    
    /*
      An intermediate collection that represents the unsorted collection for this loop's desiredCollectionSize.
      This is vector is meant to provide time savings by allowing us to not have to assign the specified range of values
      from vector<int> biggest with each pass of the inner loops.
     */
    vector<int> itemsRef;
    itemsRef.assign(biggest.begin(), biggest.begin() + desiredCollectionSize);
    itemsRef.shrink_to_fit();
    
    /*
      The vector<long double> timeSums will be used to collect and sum the time it takes for each of our algorithms to
      sort the current size of the random-values collection.
     
      It will later be used with the vector<long double> avgTimes  in the computation of each algorithm's average time to
      sort a collection sized according to the current loop of desiredCollectionSize.
     */
    vector<long double> timeSums = {0,0,0};
    
    /*
      This loop manages the variable used in determining which algorithm will be used on the current set of
      extraDataLooper-loops
     */
    for(int cycleTheSorters = startCycleSorters;cycleTheSorters < endCycleSorters ; ++cycleTheSorters) {
      for(int extraDataLooper = 0; extraDataLooper <= extraDataMax; ++extraDataLooper){
        ++loopCount;
        double percent = (loopCount/maxTotalLoops)*100;
        if(static_cast<int>(percent) > curPercent){
          curPercent = static_cast<int>(percent);
          cout << curPercent << "% complete" << endl;
        }
        
        // setting-up the variables used in generating time data, and the not-yet-sorted collection
        long double elapsedTime,myTime = 0;
        string unit;
        vector<int> items = itemsRef;
        
        /*
          The task of timing the given algorithm according to the loop variable cycleTheSorters is handled in
          this function call.
         */
        generateTimeData(qs, ms, msI, cycleTheSorters,elapsedTime, items);
  
        setTimeAndUnits(elapsedTime,myTime,unit,NANO_SECONDS);// Note that this call also handles printing the output data to compositDataFile
        
        
        // sort validation only needs to be done on the first pass. Otherwise we end up with shitload of redundant data.
        if(extraDataLooper == 0) {
          // This call will iterate through the now-sorted collection and ensure that it's valid checking that each
          // sequential index of the collection contains a value that is greater than the one that preceeded it.
          validateSort(desiredCollectionSize, cycleTheSorters, myTime, items, compositeDataFile, errFile, timeSums);
        }// end of if(extraDataLooper == 0) block
      }// end of for-cycleTheSorters loop
    } // end for-extraDataLooper loop :P
    
    /* just generating the averaged values real quick before we enter them in the data file*/
    for(unsigned int i = 0; i < endCycleSorters-startCycleSorters; ++i) avgTimes[i] = (timeSums.at(i)/static_cast<long double>(extraDataMax));
    
    /*
      this is where we actually insert the data we've collected into the data file. This represents the averaged time of
      the work done by each sorting algorithm, that have indices between startCycleSorters and endCycleSorters.
     */
    printFileTerse(compositeDataFile, desiredCollectionSize, avgTimes);
    
  } // end of for- collectionIndex loop
  
  // closing up all of the files used in the program.
  compositeDataFile.close();
  errFile.close();
//  unsortedCollectionRef.close();
  return 0;
}


