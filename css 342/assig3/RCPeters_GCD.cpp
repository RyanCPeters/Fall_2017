//
// Created by R.Peters on 11/4/2017.
//
#include <iostream>
#include "RCPeters_GCD.h"

/** GCD(const GCD &copy):A(copy.getA()), B(copy.getB()), R(0), modCalls(0),gcd(0),I(copy.getI())
 * serves as the copy constructor for the off chance we need to create copies of a given GCD object.
 * @param copy the GCD object needing to be copied
 */
GCD::GCD(const GCD &copy):A(copy.getA()), B(copy.getB()), R(0), modCalls(0),gcd(0),I(copy.getI()) {
    gcd = findGCD();
}

/**
 *
 * @param a
 * @param b
 * @param i
 */
GCD::GCD(const unsigned int &a, const unsigned int &b,const unsigned int &i):A(a),B(b),R(0),modCalls(0),gcd(0),I(i) {
    gcd = findGCD();
}

unsigned int GCD::findGCD() {
    unsigned int r = 0, a = (A > B)?A:B, b = (A > B)?B:A;
    if(a == 0 || b == 0)return a+b;
    while(b > 1) r = a%b, ++modCalls, a=b, b=r;
    return b;
}

unsigned int GCD::getGCD() const { return gcd; }

unsigned int GCD::getModCalls() const { return modCalls; }

unsigned int GCD::getA() const { return A; }

unsigned int GCD::getB() const { return B; }

unsigned int GCD::getI() const { return I; }


std::ostream &operator<<(std::ostream &os, const GCD &g) {
    os << g.getI() << "," << g.getA() << "," << g.getB() << "," << g.getGCD() << "," << g.getModCalls();
    return os;
}

bool GCD::operator>(const GCD &rhs) const { return modCalls > rhs.getModCalls(); }

bool GCD::operator>=(const GCD &rhs) const { return modCalls >= rhs.getModCalls(); }

bool GCD::operator<(const GCD &rhs) const { return modCalls < rhs.getModCalls(); }

bool GCD::operator<=(const GCD &rhs) const { return modCalls <= rhs.getModCalls(); }

GCD &GCD::operator=(const GCD &rhs) {
    I = rhs.getI();
    A = rhs.getA();
    B = rhs.getB();
    gcd = rhs.getGCD();
    modCalls = rhs.getModCalls();
    return *this;
}
