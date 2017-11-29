//
// Created by R.Peters on 10/1/2017.
//
#include <iostream>
#include "readnumbersio.h"

using namespace std;

// This simple function gets the user's input in order to add 2 ints
int readNumber()
{
    cout << "Enter a number: ";
    int intNum;
    cin >> intNum;
    return intNum;
}

// Displays the sum of 2 ints entered by user
void displaySum(int x)
{
    cout << "The answer is "
         << x
         << endl;
}