/*
 * SuperInt.cpp
 *
 * This is a class that acts like an int, but outputs various useful
 * stuff. You can add to this to experiment!
 *
 * Created by Michael Stiber on 1/31/14
 */

#include <iostream>
#include "SuperInt.h"

using namespace std;

// Name helps us see which variable
SuperInt::SuperInt(int init, const char *name): myValue(init), myName(name)
{
  cout << "Created a SuperInt called " + myName << endl;
}

SuperInt::~SuperInt()
{
  cout << "Destroyed a SuperInt called " + myName << endl;
}

// Post-increment
int SuperInt::operator++(int)
{
  int previousValue = myValue;
  myValue++;
  
  cout << "Incrementing a SuperInt called " + myName << endl;

  return previousValue;
}

const int& SuperInt::theValue(void) const
{
  cout << "Getting value (can't use as lvalue) of a SuperInt called " + myName << endl;

  return myValue;
}



