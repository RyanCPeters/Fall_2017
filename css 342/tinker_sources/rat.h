// a Rational object holds one Rational number, one fraction

#ifndef RAT_H
#define RAT_H
#include <iostream>
using namespace std;

class Rational {                           // not fully commented
public:
   Rational(int = 0, int = 1);             // default constructor
   Rational add(const Rational &);
   Rational subtract(const Rational &);
   Rational multiply(const Rational &);
   Rational divide(const Rational &);
   void printRational();
   void printRationalAsFloat();
private:
   int numerator;
   int denominator;

   void reduce();                 // utility function, reduce to lowest terms
};

#endif

