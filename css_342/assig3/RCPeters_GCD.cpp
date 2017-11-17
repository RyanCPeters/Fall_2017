//
// Created by R.Peters on 11/4/2017.
//
#include <iostream>
#include "RCPeters_GCD.h"

/** GCD(const GCD &copy):A(copy.getA()), B(copy.getB()), R(0), modCalls(0),gcd(0),I(copy.getI())
 * serves as the copy constructor for the off chance we need to create copies of a given GCD object.
 * @param copy the GCD object needing to be copied
 */
GCD::GCD(const GCD &copy):A(copy.A), B(copy.B), R(copy.R), modCalls(copy.modCalls),gcd(copy.gcd),I(copy.I) {};

/**
 *
 * @param a
 * @param b
 * @param i
 */
GCD::GCD(const long long int &a, const long long int &b,const long long int &i):A(a),B(b),R(0),modCalls(0),gcd(0),I(i) {

    if(A == 0 || B == 0)gcd = A+B;
    else gcd = findGCD();
}
 long long int GCD::findGCD() {
     long long int r, a, b;
     if (A < B) a = B, b = A;
     else a = A, b = B;
     r = a%b,++modCalls;
     while(r > 0) {
         a=b, b=r,r=a%b, ++modCalls;
     }
     return b;
}
 long long int GCD::getGCD() const { return gcd; }
 long long int GCD::getModCalls() const { return modCalls; }
 long long int GCD::getA() const { return A; }
 long long int GCD::getB() const { return B; }
 long long int GCD::getI() const { return I; }


std::ostream &operator<<(std::ostream &os, const GCD &g) {
    os << g.getI() << "," << g.getA() << "," << g.getB() << "," << g.getGCD() << "," << g.getModCalls();
    return os;
}

bool GCD::operator>(const GCD &rhs) const { return modCalls > rhs.modCalls; }

bool GCD::operator>=(const GCD &rhs) const { return modCalls >= rhs.modCalls; }

bool GCD::operator<(const GCD &rhs) const { return modCalls < rhs.modCalls; }

bool GCD::operator<=(const GCD &rhs) const { return modCalls <= rhs.modCalls; }

bool GCD::operator==(const GCD &rhs) const {

    return modCalls == rhs.modCalls && A == rhs.A && B == rhs.B;

}

GCD &GCD::operator=(const GCD &rhs) {
    I = rhs.getI();
    A = rhs.getA();
    B = rhs.getB();
    gcd = rhs.getGCD();
    modCalls = rhs.getModCalls();
    return *this;
}

void GCD::setI(long long int I) {
    GCD::I = I;
}
