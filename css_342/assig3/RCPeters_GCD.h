//
// Created by R.Peters on 11/4/2017.
//
#include <iosfwd>
#ifndef ASSIG3_GCD_H
#define ASSIG3_GCD_H


class GCD {
private:
    long long int I,A,B,R,gcd,modCalls;

    long long int findGCD();


public:
    GCD(const long long int &i):A(0),B(0),R(0),gcd(0),modCalls(0),I(i){};
    GCD(const GCD &copy);
    GCD(const long long int &a, const long long int &b,const long long int &i);

    long long int getGCD()const;

    long long int getModCalls()const;

    long long int getA()const;

    long long int getB()const;

    long long int getI()const;
    friend std::ostream& operator<<(std::ostream &os, const GCD &g);
    bool operator>(const GCD &rhs)const;
    bool operator>=(const GCD &rhs)const;
    bool operator<(const GCD &rhs)const;
    bool operator<=(const GCD &rhs)const;
    bool operator==(const GCD &rhs)const;
    GCD& operator=(const GCD &rhs);

    void setI(long long int I);

};


#endif //ASSIG3_GCD_H
