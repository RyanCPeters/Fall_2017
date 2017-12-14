#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <memory>
#include <thread>
#include <random>
#include <functional>
#include "mergesortImproved.cpp"         // implement your mergesort
#include "mergesort.cpp"
#include "quicksort.cpp"
#include "WorkDir.hpp"                   // custom tool for getting a directory path to workspace, platform independent

using namespace std;

//// Setting up static and constant references for driver control
static const unsigned short MAX_COLLECTION_SIZE = 60000, SUB_COLLECTION_INCREMENTS = 1;
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
void printToConsole(ostream &theOutStream, const collection &array, const string &funcType)
{
  theOutStream << "Array size = " << array.size() << endl;
	theOutStream << "Using the " << funcType << " algorithm" << endl;
  theOutStream.flush();
	if(array.size() > 0 )theOutStream << "items[" << setw(5) << 0 << "] = " << setw(5) << array.at(0) << endl;
	unsigned int i = 1;
	for ( ; i < array.size()-1;++i) {
		if(array.at(i) < array.at(i-1)) theOutStream << "items[" << setw(5) << i << "] = " << setw(5) << array.at(i)<< " failed"  << endl;
		else if( array.at(i) > array.at(i+1)) theOutStream << "items[" << setw(5) << i << "] = " <<  setw(5) << array.at(i) << " failed" << endl;
		else  theOutStream << "items[" << setw(5) << i << "] = " << setw(5) << array.at(i) << endl;
	}
	if(array.at(i) < array.at(i-1)) theOutStream << "items[" << setw(5) << i << "] = " << setw(5) << array.at(i)<< " failed"  << endl;
	else  theOutStream << "items[" << setw(5) << i << "] = " << setw(5) << array.at(i) << endl;
	
	theOutStream << endl << endl;
} // Here is the end of printtoConsole function

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
 * @param array 				The vector reference to where you want your random values stored
 * 											Note: array should already have its size reserved, as this function uses the vector's .begin() and
 * 											.end() iterator calls to set the bounds when allocating randome values.
 *
 * @param randMax       a constant int reference to your choice in what the maximum random value should be. This also serves
 *                      the secondary purpose of determining the size of your collection. By having your maximum allowed value
 *                      be the same as the total size of the collection, you can create a set (meaning no duplicated values)
 *                      of random numbers by utilizing the inner-for-loop and the if-statement that follows it.
 */
void initArray(collection &array, const unsigned int &randMax)
{
	for(unsigned int i = 0; i<array.size();++i)array.at(i) = i;
	shuffle(array.begin(), array.end(), default_random_engine(1));
	
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
		  qs.qsBeginSorting(items);
      tStop = chrono::high_resolution_clock::now();
      break;
    case 1://collecting myTime data for the mergesort algo on the unsorted items vector.
      tStart = chrono::high_resolution_clock::now();
		  ms.msBeginSorting(items);
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
	
	
	

	
	/* This is the BS code I got side tracked on early on in the assignment, creating a status bar to let me know
	 * the program hadn't gotten hung-up on larger collection tests.
	 * */
	stringstream spinnerBit;
	string spiffySpinner[18] = {"  (>'')>",
	                            " ^('')^",
	                            "<(''<)",
	                            " ^('')^",
	                            "  (>'')>",
	                            " ^('')^",
	                            "<(''<)",
	                            " ^('')^",
	                            "  (>'')>",
	                            "    (( )>",
	                            " ^( | )^",
	                            "<( ))",
	                            " ^( | )^",
	                            "    (( )>",
	                            " ^( | )^",
	                            "<( ))",
	                            "<(''<)",
	                            " ^('')^"};
	int write_at_width = 60;
	int spiffyIdx = 0;
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
	chrono::steady_clock::time_point tStart = chrono::steady_clock::now(), tStop = chrono::steady_clock::now();
	auto totalTime = chrono::duration_cast<chrono::milliseconds>(tStop - tStart).count();
	
	
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
  int extraDataMax = 10;
  ofstream compositeDataFile= initOutFile("composite_time");
	ofstream thirtyOut = initOutFile("Dirty_Thirty_out");
  ofstream errFile;

	
  /*
   collecting the relevant data that will be used should an error case be found in the sorted datas.
   */
//  errDataInit  << endl << endl << "new run --" << endl << "conditions:" << endl
//          << "\t" << setw(16) << "int" << left << setw(27)<< " sizeToUse" << "= " << sizeToUse << endl
//          << "\t" << setw(16) << "static const int" << left << setw(27)<< " SUB_COLLECTION_INCREMENTS" << "= " << SUB_COLLECTION_INCREMENTS << endl
//          << "\t" << setw(16) << "static const int" << left << setw(27)<< " SEED_VALUE" << "= " << SEED_VALUE << endl
//          << "\t" << setw(16) << "int" << left << setw(27)<< " extraDataMax" << "= " << extraDataMax << endl
//          << "\t" << setw(16) << "int" << left << setw(27)<< " startCycleSorters" << "= " << startCycleSorters << endl
//          << "\t" << setw(16) << "int" << left << setw(27)<< " endCycleSorters" << "= " << endCycleSorters << endl
//          << "\t" << setw(16) << "int" << left << setw(27)<< " maxTotalLoops" << "= " << maxTotalLoops << endl;
  
  compositeDataFile <<  setw(7) << "size" << ","
                    <<  setw(7) << "qs time" << ","
                    <<  setw(7) << "ms time" << ","
                    <<  setw(7) << "msi time" << endl;
  
  quicksort qs;
  mergesort ms;
  mergesortImproved msI;
	
	collection dirtyThirty(30);
	initArray(dirtyThirty,30);
	printToConsole(thirtyOut,dirtyThirty,"unsorted");
	msI.beginSort(dirtyThirty);
	printToConsole(thirtyOut,dirtyThirty,"msI");
	
			//  to generate an outputfile of the random collection being used, uncomment the following line for a single pass of the program.
//  ofstream unsortedCollectionRef = initOutFile("rawCollections");
//	printToConsole(unsortedCollectionRef,biggest,"");
//	unsortedCollectionRef.close();
  
  float loopCount = 0;  // only used in the generation of the percentage values output to the console as status updates.
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
    if(short(loopCount/expectedTotalLoopCount*100) > curPercent){
      curPercent = short(loopCount/expectedTotalLoopCount*100);
    }
		tStop = chrono::steady_clock::now();
		if(chrono::duration_cast<chrono::milliseconds>(tStop - tStart).count() - totalTime > 250) {
			totalTime = chrono::duration_cast<chrono::milliseconds>(tStop - tStart).count();
			spiffyIdx %= 18;
			// The spinner doesn't quite work right in windows cmd console, but looks great on the linux bash console! ;)
			spinnerBit << spiffySpinner[spiffyIdx++];
			cout << setw(write_at_width) << "And now for your entertainment, Kirby will present a little dance while the algorithms sort... "
							<< left << setw(16)  << spinnerBit.str() << right << setw(5) << curPercent  << "%\r";
			spinnerBit.str(string());
			flush(cout);
			this_thread::sleep_for(chrono::microseconds(1));
		}
		
  } // end of for- desiredCollectionSize loop
	
  // closing up all of the files used in the program.
  compositeDataFile.close();
	thirtyOut.close();
  errFile.close();
	string finalUnits = " seconds";
	using namespace chrono;
	tStop = steady_clock::now();
	totalTime = duration_cast<seconds>(tStop - tStart).count();
	if(totalTime > 3600){
		totalTime /= 3600;
		finalUnits = " hours";
	} else if (totalTime > 60.0) {
		totalTime /= 60;
		finalUnits = " minutes";
	}
	cout << "\ncompleting the program took:\n\t"<< totalTime << finalUnits <<endl;
  return 0;
} // end of main function


