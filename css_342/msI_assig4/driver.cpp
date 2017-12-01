#include <iostream>
#include <vector>
#include <chrono>
#include <climits>
#include "mergesortImproved.cpp"         // implement your mergesort
#include "mergesort.cpp"
#include "quicksort.cpp"
using namespace std;

/**
 *  array initialization with random numbers
 * @param array
 * @param randMax
 */
void initArray(vector<int> &array, const int &randMax) {
  int size = randMax;
  
  for ( int i = 0; i < size;) {
    int tmp = ( randMax == -1 ) ? rand( ) : rand( ) % randMax;
    bool hit = false;
    for ( int j = 0; j < i && !hit; ++j ){
      hit = array[j] == tmp;
    }
    
    if ( !hit ){
      array.push_back(tmp);
      ++i;
    }
  } // end of for i
}

// array printing
template <class Comparable>
void printArray( vector<Comparable> &array, char arrayName[], unsigned int size ) {
  int i = -1;
  for ( const auto &ele:array)cout << arrayName << "[" << ++i << "] = " << ele<< endl;
  cout << endl;
}

// array printing
template <class Comparable>
void printFile(const vector<Comparable> &array, const string &funcType, ofstream &theFile, const int &size) {
  int i = -1;
  theFile << endl << "Array size = " << size << endl;
  theFile.flush();
  for ( const auto &ele:array) {
    theFile << funcType << "[" << ++i << "] = " << ele << endl;
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
  string dirPath = WorkDir::GetWorkingDirectory();
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
  auto size = strtol( argv[1], nullptr, 10 );
  if ( size <= 0 ) {
    cerr << "array size must be positive" << endl;
    return -1;
  }
  
  vector<string> funcNames = {"quicksort","mergesort","mergesortImproved"};
  
  quicksort qs;
  mergesort ms;
  mergesortImproved msi;
  
 cout << "size(int), func, time, units, endState\n";
  int initVal= 1;
//  for(int j = 0; j < 10; ++j){
    // array generation
    // see the typedef preceeding the for- int j loop for the definition of int
    for(int loopinSize = initVal; loopinSize<= INT_MAX; loopinSize += loopinSize) {
      srand(1);
      vector<int> collectionRef;
      initArray(collectionRef, loopinSize);
      collectionRef.shrink_to_fit();
    
    
      for(int cycleSorters = 0;cycleSorters < 3; ++cycleSorters) {
        string func = funcNames[cycleSorters];
        vector<int> items;
        items.assign(collectionRef.begin(),collectionRef.end());
        int theSize = (int)items.size();
        ofstream file = initOutFile(items, func);
        if(loopinSize == 1)file << "size(int), func, time, units, endState\n";
        auto tStart = chrono::high_resolution_clock::now(), tStop = chrono::high_resolution_clock::now();
        switch (cycleSorters){
          case 0:
            tStart = chrono::high_resolution_clock::now();
            qs.beginSorting(items);
            tStop = chrono::high_resolution_clock::now();
            break;
          case 1:
            tStart = chrono::high_resolution_clock::now();
            ms.beginSorting(items);
            tStop = chrono::high_resolution_clock::now();
            break;
          case 2:
            tStart = chrono::high_resolution_clock::now();
            msi.beginSorting(items);
            tStop = chrono::high_resolution_clock::now();
            break;
          default:
            break;
        }
        auto Totaltime = std::chrono::duration_cast<std::chrono::nanoseconds>(tStop - tStart).count();
        long double time;
        string unit;
        if (Totaltime > 1E+9) {
          time = Totaltime / 1E+9;
          unit = "second(s)";
        } else if (Totaltime > 1E+6) {
          time = Totaltime / 1E+6;
          unit = "milli-seconds";
        } else if (Totaltime > 1E+3) {
          time = Totaltime / 1E+3;
          unit = "micro-seconds";
        } else {
          time = Totaltime;
          unit = "nano-seconds";
        }
        
        bool endState = false;
        int checkAgainst = 0;
        printFile(items,func,file,theSize);
        while (checkAgainst < items.size() ) {
          endState = items.at(checkAgainst) == checkAgainst++;
//          cout << cycleSorters << " ";
//          if(cycleSorters == 2)cout << "[" << checkAgainst << "] = " << items.at(checkAgainst) << endl;
          if(!endState)break;
        }
//
        file << theSize << ", " << func << ", " << time << ", " << unit << ", " << endState << endl;
        file.flush();
        file.close();
        cout << theSize << ", " << func << ", " << time << ", " << unit << ", " << endState << endl;
    
      } // end for-cycleSorters
    } // end for-loopinSize
    
//  } // end for- int j loop
  
  return 0;
} 
