//
// Created by R.Peters on 10/15/2017.
//

#ifndef WEEK3_FRACTION_H
#define WEEK3_FRACTION_H
#include <iosfwd>

class Fraction {
public:
    int numerator, denominator;

    Fraction():numerator(0),denominator(1){};
    explicit Fraction(int& num):numerator(num),denominator(1){};
    Fraction(int& num, int& den): numerator(num), denominator(den){};

    // istream, ostream overloads.
    friend std::ostream& operator<<(std::ostream &out, const int &printMe);
    friend std::istream& operator>>(std::istream &in, int &readMe);


private:
};


#endif //WEEK3_FRACTION_H
