//
// Created by R.Peters on 10/9/2017.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include "complex.h"
using namespace std;

// note that the constructors are fully handled in the .h file.

/**
 *
 * @return
 */
double complex::getReal() const {
    return myReal;
}
/**
 *
 * @return
 */
double complex::getImaginary() const {
    return myImaginary;
}




complex &complex::operator=(const complex &rhs) {
    myReal = rhs.getReal();
    myImaginary = rhs.getImaginary();
    return *this;
}

bool complex::operator==(const complex &rhs) const {
    return rhs.getReal() == getReal() &&
           rhs.getImaginary() == getImaginary();
}

bool complex::operator!=(const complex &rhs) const {
    return !(*this == rhs);
}
/* note that the conjugate of a complex expression is best seen as:

        complex objects are displayed as:
        (x) + (y)i

        and that objects conjugate is displayed as:
        (x) + (-y)i

    examples of function call, where objA is a complex expression with
    positive real and imaginary values, and objAConj is the
    complex conjugate of objA:

        complex objAConj = conjugate(
 */
complex complex::conjugate(const complex &conjugateMe) const {
    complex conj = complex(conjugateMe.myReal);
    conj.myImaginary = conjugateMe.myImaginary * -1;
    return conj;
}

complex complex::conjugate() const {
    double imgnry = myImaginary * -1;
    complex tmp = complex(myReal);
    tmp.myImaginary = imgnry;
    return tmp;
}



///////////////////////////////////////////////////////////////////
/////////// I/O operator overlaods
///////////////////////////////////////////////////////////////////

ostream& operator<<(ostream &out, const complex &printMe) {
    out << printMe.makeString();
    return out;
}

istream& operator>>(istream& in, complex& readMe) {
    vector<double> dVect;
    /* the following for loop will split off a substring, delimited by white spaces, and
     * put those substrings into the string subs.
     *
     * subs is then used as the parameter for the stod() function, clever name for the 'string to double'
     * function... these newly converted doubles are stored in a vector for easy access during assignment.
     * */
    for(int twoLoops = 0; twoLoops < 2 && in; twoLoops++){
        // subs scope is now locked to the life cycle of a single loop.
        // Handy for avoiding any possible unexpected black-box-vudu in the string class.
        string subs;
        in >> subs;
        dVect.push_back(std::stod(subs));
    }
    readMe.myReal = dVect.at(0);
    readMe.myImaginary = dVect.at(1);
    return in;
}

/*
 * This is a helper class for the I/O operators, it handles the code for creating a string
 * representation of our complex objects.
 * */
string complex::makeString() const {
    // sanity checker to make sure we even need to do more than say
    // this complex object has a 0 value.
    if(myReal == 0 && myImaginary == 0)return "0";

    stringstream ss; // we'll use this stream to make lighter work of building our return string.

    // by determining if there is a non-zero imaginary component now, we
    // simplify the task of building the string later on.
    string im = (myImaginary!=0)? "i":"",
            // spaces defaults as an empty string, but will become hold a space if we have a non-zero real value
            spaces = "",
            // we can easily see which arithmetic operator we need, if at all, so set that now :)
            oper = (myImaginary < 0)?"-":(myReal != 0)?"+":"";

    if(myReal != 0) {
        ss << myReal;
        /* If we get here, then we must have a real value, and the need for
         * spacing around the arithmetic operator should we also have an imaginary value is real.
         *
         * Assigning the space here lets us avoid having to do a redundant bool check in the next if-block
         * to check again that myReal is non-zero.
        */
        spaces = " ";
    }
    if (myImaginary != 0) {
        if(myImaginary != 1 && myImaginary > 0 ) {
            ss << spaces << oper  << spaces << myImaginary;
        }else if(myImaginary != -1 && myImaginary < 0){
            ss << spaces << oper << spaces << -1*myImaginary;
        }else {
            im = spaces + oper + spaces + im;
        }
    }
    ss << im;

    return ss.str();
}
///////////////////////////////////////////////////////////////////
/////////// addition operator overlaods
///////////////////////////////////////////////////////////////////

complex complex::operator+(const complex &rhs) const {
    return complex(getReal() + rhs.getReal(), getImaginary() + rhs.getImaginary());
}

complex complex::operator+(const double &rhs) const {
    complex tmp = complex(myReal, myImaginary);
    tmp.myReal += rhs;
    return tmp;
}

complex complex::operator+=(const complex &rhs)  {
    return *this + rhs;
}



complex complex::operator+=(const double &rhs)  {
    complex tmp = complex(myReal, myImaginary);
    tmp.myReal += rhs;
    tmp.myImaginary += rhs;
    return tmp;
}


///////////////////////////////////////////////////////////////////
/////////// subtraction operator overlaods
///////////////////////////////////////////////////////////////////
complex complex::operator-(const complex &rhs) const {
    complex tmp = complex(myReal,myImaginary);
    tmp -= rhs;
    return tmp;
}
complex complex::operator-=(const complex &rhs)  {
    myReal -= rhs.myReal;
    myImaginary -= rhs.myImaginary;
    return *this;

}
complex complex::operator-=(const double &rhs)  {
    complex tmp = complex(myReal, myImaginary);
    tmp.myReal -= rhs;
    tmp.myImaginary -= rhs;
    return tmp;
}


///////////////////////////////////////////////////////////////////
/////////// multiplication operator overloads
///////////////////////////////////////////////////////////////////
complex complex::operator*(const complex &rhs) const {
    complex tmp = complex();
    tmp.myReal = myReal*rhs.getReal() - myImaginary*rhs.getImaginary();
    tmp.myImaginary = myReal*rhs.getImaginary() + myImaginary*rhs.getReal();
    return tmp;
}

complex complex::operator*(const double &rhs) const {

    complex tmp = complex(rhs,0);
    return *this * tmp;
}

complex complex::operator*=(const double &rhs)  {
    complex tmp = complex(myReal, myImaginary);
    tmp.myReal *= rhs;
    tmp.myImaginary *= rhs;
    return tmp;
}

complex complex::operator*=(const complex &rhs)  {
    return *this * rhs;
}

// dinking around: 2.90 3.11

///////////////////////////////////////////////////////////////////
/////////// division operator overloads
///////////////////////////////////////////////////////////////////


complex complex::operator/=(const double &rhs)  {
    if (rhs != 0) {
        myReal /= rhs;
        myImaginary /= rhs;

    }else {
        // an error message here should be unneeded.
    }
    return *this;
}

complex complex::operator/(const complex &rhs) const {
    complex tmp = complex(myReal,myImaginary);
    tmp /= rhs;
    return tmp;
}

complex complex::operator/=(const complex &rhs)  {
    if (rhs.getReal() != 0 && rhs.getImaginary() != 0) {
        complex conj = rhs.conjugate();
        complex numer = conj * *this;
        numer/= (rhs.myReal * rhs.myReal + rhs.myImaginary * rhs.myImaginary);
        return *this = numer;
    }else {
        cout << "divide by zero occurred when \n\t"
             << complex::makeString()
             << " / "
             << rhs.makeString() << endl << endl;
        return rhs;
    }
}


