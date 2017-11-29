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
void printArray( vector<Comparable> &array, char arrayName[] ) {
    int size = array.size( );
    int i = 0;
    for ( const auto &ele:array) {
        cout << arrayName << "[" << i++ << "] = " << ele<< endl;
    }
    cout << endl;
}

// array printing
template <class Comparable>
void printFile( const vector<Comparable> &array, const char arrayName[],ofstream &theFile) {
    int size = array.size( );
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
 * performance evaluation
 * @param startTime
 * @param endTime
 * @return
 */
int elapsed( timeval &startTime, timeval &endTime ) {
    return ( endTime.tv_sec - startTime.tv_sec ) * 1000000
           + ( endTime.tv_usec - startTime.tv_usec );
}

/**
 *
 * @tparam Comparable
 * @param data
 * @param numElems
 * @return
 */
template<class Comparable>
ofstream printOutput(const vector<Comparable> &data, const int &numElems)  {
    stringstream ss;
    ss << "improved_merge_for_n_" << numElems << ".txt";
    string fileName = ss.str();
    string dirPath =  WorkDir::GetWorkingDirectory();
    while(dirPath.back()!='\\' && dirPath.back() != '/')dirPath.pop_back();
    dirPath = dirPath+fileName;
    ofstream myfile(dirPath,ofstream::app);
    char c[6] = {'i', 't', 'e', 'm', 's', '\0'};
    printFile(data,c,myfile);
    myfile.flush();
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


    int size = strtol( argv[1], nullptr, 10 );
    if ( size <= 0 ) {
        cerr << "array size must be positive" << endl;
        return -1;
    }

    // array generation
    for(int loopinSize = size; loopinSize<=size; loopinSize+=loopinSize) {
        srand(1);
        vector<int> items((unsigned int)loopinSize);
        vector<int> items2 = items, items3 = items;
        vector<vector<int>> itemMaster;
        itemMaster.emplace_back({items,items2,items3});
        itemMaster.shrink_to_fit();
//        cout << "size = " << loopinSize << endl;
        initArray(items, loopinSize);
        cout << "initial:" << endl << "size = " << loopinSize << endl;   // comment out when evaluating performance only
//        char c[6] = {'i', 't', 'e', 'm', 's', '\0'};
//        printArray(items, c); // comment out when evaluating performance only

        ofstream file = printOutput(items, items.size());
        auto tStart0 = chrono::high_resolution_clock::now();
        mergesortImproved msI(items);         // This is a change to original code I made in order to avoid errors
        auto tStop0 = chrono::high_resolution_clock::now();
        auto Totaltime0 = std::chrono::duration_cast<std::chrono::nanoseconds>(tStop0 - tStart0).count();
        double time;
        string unit;
        if (Totaltime0 > 1000000000.00) {
            time = Totaltime0 / 1000000000.00;
            unit = "s";
        } else if (Totaltime0 > 1000000.00) {
            time = Totaltime0 / 1000000.00;
            unit = "ms";
        } else if (Totaltime0 > 1000.00) {
            time = Totaltime0 / 1000.00;
            unit = "us";
        } else {
            time = Totaltime0;
            unit = "ns";
        }
        // mergesort
        file = printOutput(items, items.size());
        file << "ellapsed time for array size " << loopinSize << " was " << time << " " << unit << endl << endl;
        cout << "ellapsed time for array size " << loopinSize << " was " << time << " " << unit << endl << endl;
        cout << endl << "sorted:" << endl;    // comment out when evaluating performance only
        file.flush();
        file.close();
//        printArray(items, c); // comment out when evaluating performance only
    }

    return 0;
} 
