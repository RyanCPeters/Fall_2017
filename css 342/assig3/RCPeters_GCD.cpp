//
// Created by R.Peters on 11/4/2017.
//

#include "RCPeters_GCD.h"

//using namespace std;

GCD::GCD(const GCD &copy):A(copy.getA()), B(copy.getB()), R(0), modCalls(0),gcd(0) {
    gcd = findGCD();
}

GCD::GCD(int a, int b):A(a),B(b),R(0),modCalls(0),gcd(0) {
    gcd = findGCD();
}

int GCD::findGCD() {
    int r = 0, a = A, b = B;

    modCalls = 0;

    if(a == 0 || b == 0)return a+b;
    r = a%b;

    while(true)
    {
        ++modCalls, a=b,b=r;
        if(a == 0 || b == 0)return a+b;
        r = a%b;
    }
}

int GCD::getGCD() const {
    return gcd;
}

int GCD::getModCalls() const {
    return modCalls;
}

int GCD::getA() const {
    return A;
}

int GCD::getB() const {
    return B;
}
