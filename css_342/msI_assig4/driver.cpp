#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <memory>
#include <thread>
#include <random>
#include <functional>
#include "mergesortImproved.hpp"         // implement your mergesort
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "WorkDir.hpp"                   // custom tool for getting a directory path to workspace, platform independent

using namespace std;

//// Setting up static and constant references for driver control
static const unsigned short MAX_COLLECTION_SIZE = 65000, SUB_COLLECTION_INCREMENTS = 1;
static const unsigned short SEED_VALUE = 1;
static const string SECONDS = "s", MILLI_Seconds = "ms", MICRO_SECONDS = "us", NANO_SECONDS = "ns",AUTO_SELECT = "---";
static const string FUNC_NAMES[3] = {"quicksort","mergesort","mergesortImproved"};
static const string ERR_FILE_NAME = "errFile";
stringstream errDataInit;
string outFileNameString;
typedef vector<unsigned int> collection;

/**
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param theOutStream
 * @param array
 * @param funcType
 */
template <class Comparable>
void printToConsole(ostream &theOutStream, const vector<Comparable> &array, const string &funcType)
{
  theOutStream << "Array size = " << array.size() << endl;
	theOutStream << "Using the " << funcType << " algorithm" << endl;
  theOutStream.flush();
	for (unsigned int i = 0; i < array.size();++i) {
		
		theOutStream << "items[" << setw(5) << i << "] = " << setw(5) << array.at(i) << endl;
		
		
	}
	theOutStream.flush();
	theOutStream << endl << endl;
}             // Here is the end of printtoConsole function

/**
 *
 * @param theStream
 * @param dataSize
 * @param avgTimes
 */
void printFileTerse(ostream &theStream, const int &dataSize, const vector<long double> &avgTimes)
{
  theStream <<setw(7) << dataSize
          << "," << setw(7) << avgTimes[0]
          << "," << setw(7) << avgTimes[1]
          << "," << setw(7) << avgTimes[2]
          << endl;
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
	outFileNameString = ss.str();
	ss.flush();
  ss.str(string());
  string dirPath = WorkDir::GetWorkingDirectory();
  dirPath = dirPath+outFileNameString;
  ofstream myfile(dirPath,ofstream::app);
	myfile << endl;
  return myfile;
}

/** void setTimeAndUnits(const double &totalTime, double &myTime, string &units, const string &specificUnitsDesired = AUTO_SELECT)
 *
 *
 * @param totalTime
 * @param myTime
 * @param units
 * @param specificUnitsDesired
 */
long double setTimeAndUnits(const long double &totalTime, string &units,
                     const string &specificUnitsDesired)
{
  if(specificUnitsDesired.size() == 3) {
    if (totalTime > 1E+9) {
	    units = "seconds";
	    return totalTime / 1E+9;
    } else if (totalTime > 1E+6) {
	    units = "milli-seconds";
	    return totalTime / 1E+6;
    } else if (totalTime > 1E+3) {
	    units = "micro-seconds";
	    return totalTime / 1E+3;
    } else {
	    units = "nano-seconds";
	    return totalTime;
    }
  }else{
    string seconds = "s", milli_seconds = "ms", micro_seconds = "us", nano_seconds = "ns";
    if(specificUnitsDesired == seconds){
	    units = "seconds";
	    return totalTime / 1E+9;
    }else if(specificUnitsDesired == milli_seconds){
	    units = "milli-seconds";
	    return totalTime / 1E+6;
    }else if(specificUnitsDesired == micro_seconds){
	    units = "micro-seconds";
	    return totalTime / 1E+3;
    }else if(specificUnitsDesired == nano_seconds){
	    units = "nano-seconds";
      return totalTime;
    }else{
      cout << "wonky input for desired myTime units, defaulting to micro-seconds"<<endl;
	    units = "micro-seconds";
      return totalTime / 1E+3;
    }
  }
}

/** template <class Comparable> void initArray(vector<Comparable> &array, const int &randMax)
 *
 * generates the random values used in sorting algorithm comparisons.
 *
 *
 *
 * @param array the     vector reference to where you want your random values stored
 *
 * @param randMax       a constant int reference to your choice in what the maximum random value should be. This also serves
 *                      the secondary purpose of determining the size of your collection. By having your maximum allowed value
 *                      be the same as the total size of the collection, you can create a set (meaning no duplicated values)
 *                      of random numbers by utilizing the inner-for-loop and the if-statement that follows it.
 */
void initArray(collection &array, const unsigned int &randMax)
{
//	collection v = {
// 8467, 41,  6334,  6500,  9169,  5724,  1478,  9358,  6962, 4464,  5705,  8145, 3281,  6827,  9961,   491,  2995,  1942,  4827, 5436,  2391,  4604,  3902,   153,   292,  2382,  7421,  8716,  9718, 9895,  5447,  1726,  4771,  1538,  1869,  9912,  5667,  6299, 7035, 9894,  8703,  3811,  1322,   333,  7673,  4664,  5141,  7711,  8253, 6868,  5547,  7644,  2662,  2757,    37,  2859,  8723,  9741,  7529, 778,  2316,  3035,  2190,  1842,   288,   106,  9040,  8942,  9264, 2648,  7446,  3805,  5890,  6729,  4370,  5350,  5006,  1101,  4393, 3548,  9629,  2623,  4084,  9954,  8756,  1840,  4966,  7376,  3931, 6308,  6944,  2439,  4626,  1323,  5537,  1538,  6118,  2082,  2929, 541,  4833,  1115,  4639,  9658,  2704,  9930,  3977,  2306,  1673, 2386,  5021,  8745,  6924,  9072,  6270,  5829,  6777,  5573,  5097,
// 6512,  3986,  3290,  9161,  8636,  2355,  4767,  3655,  5574,  4031, 2052,  7350,  1150,  6941,  1724,  3966,  3430,  1107,   191,  8007, 1337,  5457,  2287,  7753,   383,  4945,  8909,  2209,  9758,  4221, 8588,  6422,  4946,  7506,  3030,  6413,  9168,   900,  2591,  8762, 655,  7410,  6359,  7624,   537,  1548,  6483,  7595,  4041,  3602, 4350,   291,   836,  9374,  1020,  4596,  4021,  7348,  3199,  9668, 4484,  8281,  4734,    53,  1999,  6418,  7938,  6900,  3788,  8127, 467,  3728,  4893,  4648,  2483,  7807,  2421,  4310,  6617,  2813, 9514,  4309,  7616,  8935,  7451,   600,  5249,  6519,  1556,  2798, 303,  6224,  1008,  5844,  2609,  4989,  2702,  3195,   485,  3093, 4343,   523,  1587,  9314,  9503,  7448,  5200,  3458,  6618,   580, 9796,  4798,  5281,  9589,   798,  8009,  7157,   472,  3622,  8538,
// 2292,  6038,  4179,  8190,  9657,  7958,  6191,  9815,  2888,  9156, 1511,  6202,  2634,  4272,    55,   328,  2646,  6362,  4886,  8875, 8433,  9869,   142,  3844,  1416,  1881,  1998,   322,  8651,    21, 5699,  3557,  8476,  7892,  4389,  5075,   712,  2600,  2510,  1003, 869,  7861,  4688,  3401,  9789,  5255,  6423,  5002,   585,  4182, 285,  7088,  1426,  8617,  3757,  9832,   932,  4169,  2154,  5721, 7189,  9976,  1329,  2368,  8692,  1425,   555,  3434,  6549,  7441, 9512,   145,  8060,  1718,  3753,  6139,  2423,  6279,  5996,  6687, 2529,  2549
// };
//	array = v;
	// We use static in order to instantiate the random engine
	// and the distribution once only.
	// It may provoke some thread-safety issues.
	static uniform_int_distribution<unsigned int> distribution(numeric_limits<unsigned int>::min(), randMax);
	static default_random_engine generator;
	
	generate(array.begin(), array.end(), []() { return distribution(generator); });

}// end of initArray function.


/**void generateTimeData(quicksort &qs, mergesort &ms, mergesortImproved &msI, const int &cycleSorters, double &elapsedTime, collection &items)
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
                             long double &elapsedTime, collection &items)
{
	
	chrono::high_resolution_clock::time_point tStart, tStop;
  
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
		  msI.beginSort(items);
      tStop = chrono::high_resolution_clock::now();
      break;
    default:
      break;
  }
  elapsedTime = chrono::duration_cast<chrono::nanoseconds>(tStop - tStart).count();
	elapsedTime;
}

/**void validateSort(const int &collectionIndex, const int &cycleSorters, double &myTime, collection &items, ofstream &compositeDataFile, ofstream &errFile)
 *
 * @param collectionIndex
 * @param cycleSorters
 * @param myTime
 * @param items
 * @param compositeDataFile
 * @param errFile
 */
void validateSort(const unsigned int &collectionIndex, const int &cycleSorters, collection &items, ofstream &errFile)
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
  
  while (collectionIndex > 1 && checkAtIdx < items.size()-1 && finishedSortState) finishedSortState = items.at(checkAtIdx) <= items.at(++checkAtIdx);
	
  // this if block is determining whether we need errFile output
  if(!finishedSortState){
    // if errDataInit has something in it, then we must be at our first error and it's time to initialize ofstream errFile;
    if(errDataInit.rdbuf()->in_avail() > 0) {
      errFile = initOutFile("errFile");
      errFile << errDataInit.str();
      errDataInit.str(string()); // now we clear errDataInit to make sure we don't re-initialize errFile.
      
      errFile << "algorithm, collection.size(), numFails, lesserDiff, graterDiff, Ratio" << endl;
    }
  
    unsigned int two_raised_to = 1;
    while(two_raised_to < items.size())two_raised_to <<= 1;
	  
    float greaterDiff, lesserDiff;
    greaterDiff = (two_raised_to - items.size());
    two_raised_to >>= 1;
    lesserDiff = (items.size()-two_raised_to);
    stringstream ss;
    unsigned int numFails = 0;
    for(unsigned int i = 0; i < items.size()-1;++i) {
	    if(items.at(i) > items.at(i+1)){
		    ++numFails;
		    if(numFails>1)ss <<setw(42)<< " , , , , , ";
		    ss << ", " << i<<"[" <<items.at(i) <<"]" <<endl;
	    }
    }
    errFile << FUNC_NAMES[cycleSorters] << ", " << items.size() << ", " << numFails << ", " << lesserDiff << ", " << greaterDiff << ", " << lesserDiff/greaterDiff << ss.str()<< endl;
	  ss.str(string());
  }
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */
int commandLineArgValidation(const int &argc, char** argv){
	
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
	return size;
	
}

/** int main( int argc, char *argv[] )
 *
 * main(arc, argv) will perform the task of initializing sorting classes, output files, and control variables.
 *
 * It will then use three nested for loops to conduct repeated calls to each sorting algorithm, using multiple
 * sub-collections of one common unsorted collection so as to maintain consistancy across samples, this also saves time
 * as we don't have to generate new unsorted samples over and over.
 *
 * @param argc      The number of arguments passed on the command line.
 *                  If argc == 1, then no additional arguments were passed, as the first argument is always the
 *                  name of the executable file.
 *
 * @param argv      An array of c_strings containing any command-line arguments beyond the initial executable's name.
 * @return          the error code should any be thrown, otherwise 0 when all goes well.
 */
int main( int argc, char *argv[] )
{
  // verify arguments
	auto sizeToUse = static_cast<unsigned int>(commandLineArgValidation(argc,argv));
	sizeToUse = (sizeToUse <= MAX_COLLECTION_SIZE)? sizeToUse : MAX_COLLECTION_SIZE;
	
	
	
  collection biggest(sizeToUse);
	if(sizeToUse > 0) {
		cout << "Please wait while the item collections are randomly generated with a desired collection size of: " << sizeToUse << endl;
		chrono::high_resolution_clock::time_point tStart = chrono::high_resolution_clock::now();
		initArray(biggest, sizeToUse);
		chrono::high_resolution_clock::time_point tStop = chrono::high_resolution_clock::now();
		cout << "random data has been generated, now to begin testing the sorting algos."
		     << "\nBuilding the random reference collection took:\n\t" << chrono::duration_cast<chrono::nanoseconds>(tStop - tStart).count()
		     << " nano-seconds." <<endl;
	}else return 0;
	chrono::steady_clock::time_point tStart = chrono::steady_clock::now();
	char spiffySpinner[8] = {'|','/','-','\\','|','/','-','\\'};
	int spiffyIdx = 0;
  // setting-up loop-control variables
  
  /* startCycleSorters -- Determines the starting index for the cycleSorters loop variable. Changing this value allows you
   *                      to bypass a particular sorter if you wish.
   * endCycleSorters   -- Determines the ending index for the cycleSorters loop variable. Changing this value allows you
   *                      to bypass a particular sorter if you wish.
   * The sorting algorithms by index:
   *                                 0 -- Quicksort
   *                                 1 -- Mergesort
   *                                 2 -- MergesortImproved
   */
	unsigned startCycleSorters = 0,
      endCycleSorters = 3;
  
  /*
   extraDataMax expresses the desired number of additional loop-passes at each collection size for each sorter,
   these additional loops will be used to generate more accurate averages of time complexity later on.
   */
  int extraDataMax = 20;
  float maxTotalLoops = sizeToUse * extraDataMax;
  ofstream compositeDataFile= initOutFile("composite_time");
	ofstream thirtyOut = initOutFile("Thirty_out");
  ofstream errFile;
  /*
   collecting the relevant data that will be used should an error case be found in the sorted datas.
   */
  errDataInit  << endl << endl << "new run --" << endl << "conditions:" << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " sizeToUse" << "= " << sizeToUse << endl
          << "\t" << setw(16) << "static const int" << left << setw(27)<< " SUB_COLLECTION_INCREMENTS" << "= " << SUB_COLLECTION_INCREMENTS << endl
          << "\t" << setw(16) << "static const int" << left << setw(27)<< " SEED_VALUE" << "= " << SEED_VALUE << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " extraDataMax" << "= " << extraDataMax << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " startCycleSorters" << "= " << startCycleSorters << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " endCycleSorters" << "= " << endCycleSorters << endl
          << "\t" << setw(16) << "int" << left << setw(27)<< " maxTotalLoops" << "= " << maxTotalLoops << endl;
  
  compositeDataFile <<  setw(7) << "size" << ","
                    <<  setw(7) << "qs time" << ","
                    <<  setw(7) << "ms time" << ","
                    <<  setw(7) << "msi time" << endl;
  
  quicksort qs;
  mergesort ms;
  mergesortImproved msI;
	
			//  to generate an outputfile of the random collection being used, uncomment the following line for a single pass of the program.
//  ofstream unsortedCollectionRef = initOutFile("rawCollections");
//	printToConsole(unsortedCollectionRef,biggest,"");
//	unsortedCollectionRef.close();
  
  float loopCount = 0, progress = 0;  // only used in the generation of the percentage values output to the console as status updates.
	short curPercent = 0;   // only used in the generation of the percentage values output to the console as status updates.
  vector<long double> avgTimes = {0,0,0};
//	short numOfSizes = 7;
//	unsigned int testSizes[numOfSizes] = {10,30,100,1000,10000,30000,MAX_COLLECTION_SIZE};
	
	
  float expectedTotalLoopCount = sizeToUse/2 * extraDataMax;

	for(unsigned int desiredCollectionSize = sizeToUse; desiredCollectionSize > 0; desiredCollectionSize-=2 ){
    /*
      The vector<double> timeSums will be used to collect and sum the time it takes for each of our algorithms to
        sort the current size of the random-values collection.
      It will later be used with the vector<double> avgTimes  in the computation of each algorithm's average time to
        sort a collection sized according to the current loop of desiredCollectionSize.
     */
    vector<long double> timeSums = {0,0,0};
    
    /*
      This loop manages the variable used in determining which algorithm will be used on the current set of
        extraDataLooper-loops
     */
      for(int extraDataLooper = 1; extraDataLooper <= extraDataMax; ++extraDataLooper){
//	      for(int cycleTheSorters = endCycleSorters-1;cycleTheSorters >= startCycleSorters; --cycleTheSorters) {
	      ++loopCount;
        
        // setting-up the variables used in generating time data, and the not-yet-sorted collection
        long double elapsedTime = 0; //elapsedTime will be used to collect the raw nanosecond-time of each funciton
				          // myTime will be used to express the collected time in terms of more readable time units
        string unit;
        collection items0,items1,items2;
	      items0.assign(biggest.begin(),biggest.begin() + desiredCollectionSize);
        items0.shrink_to_fit();
	      items2 = items1 = items0;
        /*The task of timing the given algorithm according to the loop variable cycleTheSorters is handled in
          this function call. */
	      
	      generateTimeData(qs, ms, msI, 2,elapsedTime, items2);
	      timeSums.at(2) += setTimeAndUnits(elapsedTime,unit,MICRO_SECONDS);
	      
        generateTimeData(qs, ms, msI, 0,elapsedTime, items0);
	      timeSums.at(0) += setTimeAndUnits(elapsedTime,unit,MICRO_SECONDS);
	      
	      
	      generateTimeData(qs, ms, msI, 1,elapsedTime, items1);
	      timeSums.at(1) += setTimeAndUnits(elapsedTime,unit,MICRO_SECONDS);
	
				if(extraDataLooper > 1) {
					/* just generating the averaged values real quick before we enter them in the data file*/
					for (unsigned int i = endCycleSorters; i < endCycleSorters - startCycleSorters; ++i) {
						avgTimes.at(i) = ((timeSums.at(i)+ avgTimes.at(i)) / 2.0);
					}
				}else{
					for (unsigned int i = startCycleSorters; i < endCycleSorters; ++i) {
						avgTimes.at(i) = timeSums.at(i);
					}
				}
//	      if(items.size() == 30 && extraDataLooper==1 && cycleTheSorters == 2 ) printToConsole(thirtyOut,items,FUNC_NAMES[cycleTheSorters]);
	     
        // sort validation only needs to be done on the first pass. Otherwise we end up with shitload of redundant data.
        if(extraDataLooper == 0) {
          // This call will iterate through the now-sorted collection and ensure that it's valid checking that each
          // sequential index of the collection contains a value that is greater than the one that preceeded it.
	        validateSort(desiredCollectionSize, 0, items0, errFile);
	        validateSort(desiredCollectionSize, 1, items1, errFile);
	        validateSort(desiredCollectionSize, 2, items2, errFile);
        }// end of if(extraDataLooper == 0) block
//      }// end of for-cycleTheSorters loop
    } // end for-extraDataLooper loop :P
		
		
		/*
			this is where we actually insert the data we've collected into the data file. This represents the averaged time of
			the work done by each sorting algorithm, that have indices between startCycleSorters and endCycleSorters.
		 */
		printFileTerse(compositeDataFile, desiredCollectionSize, avgTimes);
		
		// giving a status update to show the programs is still running
    if(short(loopCount/expectedTotalLoopCount*100)+.5 > curPercent){
      curPercent = short(loopCount/expectedTotalLoopCount*100);
	    stringstream spinnerBit;
	    // The spinner doesn't quite work right in windows cmd console, but looks great on the bash console! ;)
	    spinnerBit << spiffySpinner[spiffyIdx++];
      int write_at_width = 70;
      cout << setw(write_at_width)<< spinnerBit.str() << curPercent << "  %\r";
	    flush(cout);
	    spiffyIdx %= 8;
      this_thread::sleep_for(chrono::microseconds(1));
    }else if(loopCount/expectedTotalLoopCount*100.0 - short(loopCount/expectedTotalLoopCount*100) > .4 || loopCount/expectedTotalLoopCount*100.0 - short(loopCount/expectedTotalLoopCount*100) < .6 ){
	    stringstream spinnerBit;
	    spinnerBit << spiffySpinner[(spiffyIdx++)%8];
	    int write_at_width = 70;
	    cout << setw(write_at_width)<< spinnerBit.str() << curPercent << "  %\r";
	    flush(cout);
    }
    
		
  } // end of for- collectionIndex loop
	
  // closing up all of the files used in the program.
  compositeDataFile.close();
	thirtyOut.close();
  errFile.close();
	string finalUnits = "seconds";
	using namespace chrono;
	steady_clock::time_point tStop = steady_clock::now();
	auto totalTime = duration_cast<seconds>(tStop - tStart).count();
	if (totalTime > 60.0) {
		totalTime /= 60;
		finalUnits = " minutes";
	} else if(totalTime > 3600){
		totalTime /= 3600;
		finalUnits = " hours";
	}
	cout << "\ncompleting the program took:\n\t"<< finalUnits <<endl;
  return 0;
} // end of main function


