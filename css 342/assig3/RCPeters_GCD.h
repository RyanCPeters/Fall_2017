//
// Created by R.Peters on 11/4/2017.
//
#include <iosfwd>
#ifndef ASSIG3_GCD_H
#define ASSIG3_GCD_H


class GCD {
private:
    int I,A,B,R,gcd,modCalls;

    int findGCD();


public:
    GCD(const int &i):A(0),B(0),R(0),gcd(0),modCalls(0),I(i){};
    GCD(const GCD &copy);
    GCD(const int &a, const int &b,const int &i);
    int getGCD()const;
    int getModCalls()const;
    int getA()const;
    int getB()const;
    int getI()const;
    friend std::ostream& operator<<(std::ostream &os, const GCD &g);
    bool operator>(const GCD &rhs)const;
    bool operator>=(const GCD &rhs)const;
    bool operator<(const GCD &rhs)const;
    bool operator<=(const GCD &rhs)const;
    GCD& operator=(const GCD &rhs);

};


#endif //ASSIG3_GCD_H
