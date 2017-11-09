//
// Created by R.Peters on 11/4/2017.
//
#include <iosfwd>
#ifndef ASSIG3_GCD_H
#define ASSIG3_GCD_H


class GCD {
private:
    unsigned int I,A,B,R,gcd,modCalls;

    unsigned int findGCD();


public:
    GCD(const unsigned int &i):A(0),B(0),R(0),gcd(0),modCalls(0),I(i){};
    GCD(const GCD &copy);
    GCD(const unsigned int &a, const unsigned int &b,const unsigned int &i);

    unsigned int getGCD()const;

    unsigned int getModCalls()const;

    unsigned int getA()const;

    unsigned int getB()const;

    unsigned int getI()const;
    friend std::ostream& operator<<(std::ostream &os, const GCD &g);
    bool operator>(const GCD &rhs)const;
    bool operator>=(const GCD &rhs)const;
    bool operator<(const GCD &rhs)const;
    bool operator<=(const GCD &rhs)const;
    GCD& operator=(const GCD &rhs);

};


#endif //ASSIG3_GCD_H
