/*
 *  Primitive2.cpp
 *
 *  Created by Rob Nash on 9/26/13.
 *  Copyright (c) 2013 Rob Nash. All rights reserved.
 *
 *  Modified by Michael Stiber on 1/6/14
 */

//---------------------- INSTRUCTION ------------------
// Be sure you understand different conversion methods.
//-----------------------------------------------------

#include <iostream>
#include <cmath>

using namespace std;

int main() {

    int a = 3;
    int b, c;
    b = c = 8;
    int d = a + b + c;

    union U { int a; double b; } u;
    void *x = &u;
    double *y = static_cast<double*>(x);

    // What is that "\n" thing?
    std::cout << "\nHello, World!\n";
    cout << "-----------------------------------------------------";
    cout << endl << endl << "int a = 3;\nint b, c;\nb = c = 8;\nint d = a + b + c;\n";
    cout << endl << "Ugly output; how can we improve it a bit?" << endl;
    cout << "a is " << a << endl;
    cout << "b is " << b << endl;
    cout << "c is " << c << endl;
    cout << "d is " << d << endl;
    cout << "-----------------------------------------------------";

    cout << endl << "Integer division" << endl;
    cout << "b/a is " << b / a << endl;
    cout << "a/b is " << a / b << endl;
    cout << "b%a is " << b % a << endl;
    cout << "a%b is " << a % b << endl;
    cout << "-----------------------------------------------------";

    cout << endl << "Conversion to floating point: try 1" << endl;
    cout << "double(b/a) is " << double(b / a) << endl;
    cout << "double(a/b) is " << double(a / b) << endl;
    cout << "-----------------------------------------------------";

    cout << endl << "Conversion to floating point: try 2" << endl;
    cout << "double(b)/a is " << double(b) / a << endl;
    cout << "double(a)/b is " << double(a) / b << endl;
    cout << "-----------------------------------------------------";

    cout  << endl <<
          "Conversion to floating point: preferred method\n"
          "Says explicitly that you've checked and that this\n"
          "is a safe conversion. No run-time checking done, but\n"
          "the compiler will barf on obviously problematic code.\n";
    cout  << endl << "static_cast<double>(b)/a is " << static_cast<double>(b) / a << endl;
    cout << "static_cast<double>(a)/b is " << static_cast<double>(a) / b << endl;
    cout << "-----------------------------------------------------";

     cout <<
          "\n\nConversion of floating point to integer types: you need to decide\n"
          "what you want to do with the fractional part.\n";
    double e = static_cast<double>(d) / a;
    cout << endl << "e is " << e << endl;
    cout << "ceil(e) is " << ceil(e) << endl;
    cout << "floor(e) is " << floor(e) << endl;
    cout << "trunc(e) is " << trunc(e) << endl;
    cout << "round(e) is " << round(e) << endl;
    cout << "rint(e) is " << rint(e) << endl;

    cout << "ceil(-e) is " << ceil(-e) << endl;
    cout << "floor(-e) is " << floor(-e) << endl;
    cout << "trunc(-e) is " << trunc(-e) << endl;
    cout << "round(-e) is " << round(-e) << endl;
    cout << "rint(-e) is " << rint(-e) << endl;
}
