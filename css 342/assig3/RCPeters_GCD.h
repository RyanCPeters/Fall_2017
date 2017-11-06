//
// Created by R.Peters on 11/4/2017.
//

#ifndef ASSIG3_GCD_H
#define ASSIG3_GCD_H


class GCD {
private:
    int A,B,R,gcd,modCalls;

    int findGCD();


public:
    GCD():A(0),B(0),R(0),gcd(0),modCalls(0){};
    GCD(const GCD &copy);
    GCD(int A, int B);
    int getGCD()const;
    int getModCalls()const;
    int getA()const;
    int getB()const;

};


#endif //ASSIG3_GCD_H
