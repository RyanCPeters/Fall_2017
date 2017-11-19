//
// Created by r.Peters on 11/4/2017.
//
#include <iostream>
#include <sstream>
#include "rCPeters_GCD.h"

/** GCD(const GCD &copy):A(copy.getA()), B(copy.getB()), r(0), modCalls(0),gcd(0),I(copy.getI())
 * serves as the copy constructor for the off chance we need to create copies of a given GCD object.
 *
 * No logic or evaluation is done if this call is made. It's simply a way to duplicate a GCD objects.
 * @param copy the GCD object needing to be copied
 */
GCD::GCD(const GCD &copy):A(copy.A), B(copy.B), modCalls(copy.modCalls),gcd(copy.gcd),I(copy.I) {};

/**GCD::GCD(const long long int &a, const long long int &b,const long long int &i):A(a),B(b),modCalls(0),gcd(1),I(i)
 *
 * This constructor takes initial values and assigns them to class members for reference and comparison later.
 *
 * It also checks if either A or B are zero. If either one is zero, then gcd = the sum of A and B. It's the lazy way of
 * making sure gcd gets assigned the right value.
 *
 * @param a any integer value less than or equal to i
 * @param b any integer value less than or equal to i
 * @param i for the specific purposes of this assingment, i is stored with the GCD objects for convenient printing of
 * the data later.
 */
GCD::GCD(const long long int &a, const long long int &b,const long long int &i):A(a),B(b),modCalls(0),gcd(1),I(i) {

    if(A == 0 || B == 0)gcd = A+B;
    else findGCD();
}

/** void GCD::findGCD()
 * findGCD() will create temporary scoped copies of A and B, then it will repeatedly perform modulus operations of,
 * r = a%b until we get r = 0;
 *
 * It is worth mentioning that the precondition checking done before findGCD is called ensures that neither A or B are zero.
 *
 * It should also be said that as the local variables a and b are assigned, a will always be assigned the larger value
 * out of  A and B.
 *
 * Note that instead of creating a redundant variable named r, gcd is used to store the results of the modulus operations
 * and is then set equal to b after a remainder of 0 is found.
 */
 void GCD::findGCD() {
     long long int a, b;
     if (A < B) a = B, b = A;
     else a = A, b = B;
     gcd = a%b,++modCalls;
     while(gcd > 0) {
         a=b, b=gcd,gcd=a%b, ++modCalls;
     }
     gcd = b;
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

bool GCD::operator==(const GCD &rhs) const { return modCalls == rhs.modCalls && A == rhs.A && B == rhs.B; }

GCD &GCD::operator=(const GCD &rhs) {
    I = rhs.getI();
    A = rhs.getA();
    B = rhs.getB();
    gcd = rhs.getGCD();
    modCalls = rhs.getModCalls();
    return *this;
}

