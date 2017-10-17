/*
 * Command line example code 
 * Winter 2014 Michael Stiber 
 *
 */

#include <iostream>
using namespace std;

int main (int argc, char * const argv[]) {

	cout << argc << " arguments passed to this program" << endl;
	cout << "\tProgram name: " << argv[0] << endl;
	
	for (int i=1; i<argc; i++) {
		cout << "\t\targv[" << i << "] = " << argv[i] << endl;
	}
	
    return 0;
}
