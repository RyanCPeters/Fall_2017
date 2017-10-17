

#include <iostream>
#include "Fraction.h"

//main() to test struct Fraction
int main()
{
    // Allocate our first fraction
    Fraction f1;
    cout << "Input the first integer numerator: ";
    cin >> f1.numerator;
    cout << "Input the first integer denominator: ";
    cin >> f1.denominator;
 
    // Allocate our second fraction
    Fraction f2;
    cout << "Input the second integer numerator: ";
    cin >> f2.numerator;
    cout << "Input the second integer denominator: ";
    cin >> f2.denominator;
 
    multiply(f1, f2);
	
	// Declare a new struct object
	
 
    // Member selection using pointer to struct, no need to modify any functions in Fraction.cpp 
    
	
	
    // Your final call
	multiply(f1, f3);
 
    return 0;
}

