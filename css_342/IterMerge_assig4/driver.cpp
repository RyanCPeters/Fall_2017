#include <iostream>
#include <vector>
#include <cstdlib>
#include <sys/time.h>
#include "mergesortImproved.h"         // implement your mergesort
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
void printArray( vector<int> &array, char arrayName[] ) {
    int size = array.size( );

    for ( int i = 0; i < size; ++i ) {
        cout << arrayName << "[" << i << "] = " << array[i] << endl;
    }
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

    srand( 1 );
    vector<int> items( size );
    cout << "size = " << size << endl;
    initArray( items, size );
    cout << "initial:" << endl;   // comment out when evaluating performance only
    char c[6] = {'i','t','e','m','s','\0'};
    printArray( items, c ); // comment out when evaluating performance only

    // mergesort
    struct timeval startTime, endTime;
    gettimeofday( &startTime, nullptr );
    mergesortImproved msI( items );
    gettimeofday( &endTime, nullptr );
    cout << "elapsed time: " << elapsed( startTime, endTime ) << endl;

    cout << "sorted:" << endl;    // comment out when evaluating performance only
    printArray( items, c ); // comment out when evaluating performance only

    return 0;
} 
