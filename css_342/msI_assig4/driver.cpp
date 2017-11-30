#include <iostream>
#include <vector>
#include <sys/time.h>
#include <chrono>
#include "mergesortImproved.cpp"         // implement your mergesort
#include "mergesort.cpp"
#include "quicksort.cpp"
using namespace std;

/**
 *  array initialization with random numbers
 * @param array
 * @param randMax
 */
void initArray( vector<int> &array, int randMax ) {
  int size = array.size( );
  
  for ( int i = 0; i < size;) {
    int tmp = ( randMax == -1 ) ? rand( ) : rand( ) % randMax;
    bool hit = false;
    for ( int j = 0; j < i && !hit; ++j ) {
      hit = array[j] == tmp;
    } //  end of for j
    if ( !hit ){
      array[i] = tmp, ++i;
    }
  } // end of for i
}

// array printing
template <class Comparable>
void printArray( vector<Comparable> &array, char arrayName[], unsigned int size ) {
  int i = 0;
  for ( const auto &ele:array)cout << arrayName << "[" << i++ << "] = " << ele<< endl;
  cout << endl;
}

// array printing
template <class Comparable>
void printFile( const vector<Comparable> &array, const char arrayName[],ofstream &theFile, unsigned int size ) {
  int i = 0;
  theFile << endl << "Array size = " << size << endl;
  theFile.flush();
  for ( const auto &ele:array) {
    theFile << arrayName << "[" << i++ << "] = " << ele << endl;
    theFile.flush();
  }
  theFile << endl;
  theFile.flush();
}

/**
 *
 * @tparam Comparable
 * @param data
 * @param numElems
 * @return
 */
template<class Comparable>
ofstream initOutFile(const vector<Comparable> &data, const string &dataName) {
  stringstream ss;
  ss << "/"<< dataName << "out_data" << ".txt";
  string fileName = ss.str();
  ss.str(string());
  string dirPath =  WorkDir::GetWorkingDirectory();
  dirPath = dirPath+fileName;
  ofstream myfile(dirPath,ofstream::app);
  return myfile;
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
  auto size = (unsigned int)strtol( argv[1], nullptr, 10 );
  if ( size <= 0 ) {
    cerr << "array size must be positive" << endl;
    return -1;
  }
  
  typedef void(*RequiredFunction)();
  string name1 = "items1",name2 = "items2",name3 = "items3";
  vector<string> names = {name1,name2,name3};
  vector<string> funcNames = {"quicksort","mergesort","mergesortImproved"};
  quicksort qs;
  mergesort ms;
  mergesortImproved msi;
  
// cout << "size(int), func, time, units, endState\n";
  for(int j = 0; j < 1000; ++j){
    // array generation
    for(int loopinSize = size; loopinSize<=size*10*10*10; loopinSize*=10) {
      srand(1);
      vector<int> collectionRef;
      initArray(collectionRef, loopinSize);
      collectionRef.shrink_to_fit();
    
    
      for(int cycleSorters = 0;cycleSorters < 3; ++cycleSorters) {
        string name = names[cycleSorters], func = funcNames[cycleSorters];
        
        vector<int> items = collectionRef;
        ofstream file = initOutFile(items, func);
        if(loopinSize == 1)file << "size(int), func, time, units, endState\n";
        auto tStart0 = chrono::high_resolution_clock::now(), tStop0 = chrono::high_resolution_clock::now();
        switch (cycleSorters){
          case 0:
            tStart0 = chrono::high_resolution_clock::now();
            qs.beginSorting(items);
            tStop0 = chrono::high_resolution_clock::now();
            break;
          case 1:
            tStart0 = chrono::high_resolution_clock::now();
            ms.beginSorting(items);
            tStop0 = chrono::high_resolution_clock::now();
            break;
          case 2:
            tStart0 = chrono::high_resolution_clock::now();
            msi.beginSorting(items);
            tStop0 = chrono::high_resolution_clock::now();
            break;
          default:
            break;
        }
        auto Totaltime0 = std::chrono::duration_cast<std::chrono::nanoseconds>(tStop0 - tStart0).count();
        double time;
        string unit;
        if (Totaltime0 > 1000000000.00) {
          time = Totaltime0 / 1000000000.00;
          unit = "second(s)";
        } else if (Totaltime0 > 1000000.00) {
          time = Totaltime0 / 1000000.00;
          unit = "milli-seconds";
        } else if (Totaltime0 > 1000.00) {
          time = Totaltime0 / 1000.00;
          unit = "micro-seconds";
        } else {
          time = Totaltime0;
          unit = "nano-seconds";
        }
        
        bool endState = true;
        unsigned int checkAgainst = 0;
        while (checkAgainst < items.size() ) {
          endState = items.at(checkAgainst) == checkAgainst++;
          if(!endState)break;
        }
        
        file << loopinSize << ", " << func << ", " << time << ", " << unit << ", " << endState
             << endl;
        file.flush();
        file.close();
//        cout << loopinSize << ", " << func << ", " << time << ", " << unit << ", " << endState
//                 << endl;
    
      } // end for-cycleSorters
    } // end for-loopinSize
    
  }
  
  return 0;
} 
