//
// Created by R.Peters on 11/4/2017.
//
#include <iosfwd>
#ifndef ASSIG3_GCD_H
#define ASSIG3_GCD_H


class GCD {
private:
    unsigned long long int I,A,B,R,gcd,modCalls;

    unsigned long long int findGCD();


public:
    GCD(const unsigned long long int &i):A(0),B(0),R(0),gcd(0),modCalls(0),I(i){};
    GCD(const GCD &copy);
    GCD(const unsigned long long int &a, const unsigned long long int &b,const unsigned long long int &i);

    unsigned long long int getGCD()const;

    unsigned long long int getModCalls()const;

    unsigned long long int getA()const;

    unsigned long long int getB()const;

    unsigned long long int getI()const;
    friend std::ostream& operator<<(std::ostream &os, const GCD &g);
    bool operator>(const GCD &rhs)const;
    bool operator>=(const GCD &rhs)const;
    bool operator<(const GCD &rhs)const;
    bool operator<=(const GCD &rhs)const;
    GCD& operator=(const GCD &rhs);

};


#endif //ASSIG3_GCD_H
