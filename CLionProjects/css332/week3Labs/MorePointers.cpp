//
//  MorePointers.cpp
//
//  Created by Michael Stiber sometime.
//  Modified by him on 1/30/14
//

#include <iostream>
#include <cstring> // <--- Look here, this is important
using namespace std;

//----- Please comment this file with your observations; answer questions here -------
//
//
//
//
//------------------------------------------------------------------------------------
int main (int argc, char * const argv[])
{
	int i, j;
	int* ip, *ip2;
	char s[20];
	char* cp;
	
	// Initialize i and j, make pointers to them, manipulate
	i = 1;
	j = 2;
	ip = &i;
	ip2 = &j;
	cout << "The value of i is " << i << "; the value of j is " << j << endl;
	cout << "Via pointers: " << *ip << ", " << *ip2 << endl;

	ip2 = ip;
	*ip = 7;
	cout << "Both pointers point to same thing: " << *ip << ", " 
	     << *ip2 << " (i = " << i << ")" << endl;
	ip2 = &j;
	cout << "j is unmodified; it's still " << *ip2 << endl;
	*ip2 = 10;
	cout << "\tbut now it is: " << j << " = " << *ip2 << endl << endl;
	
	// Now, demonstrate how C strings, arrays, and pointers are all related
	strcpy(s, "Hello");           // C string are null '\0' terminated
	cout << "Our test string is \"" << s << "\"" << endl;
	cout << "One character at a time, that is:" << endl;
	
	for (int k=0; k<strlen(s); k++) {
		cout << "\ts[" << k << "] = '" << s[k] << "'" << endl;
	}
	cout << "And just past the end is a char with ASCII value " 
	     << static_cast<int>(s[strlen(s)]) << endl << endl;
	
	cout << "Using a pointer:" << endl;
	cp = s;
	while (*cp != '\0') {
		cout << "\tnext character is '" << *cp << "'" << endl;
		cp++;
	}
	cout << "And the next char has the ASCII value " 
	     << static_cast<int>(*cp) << endl << endl;


    return 0;
}
