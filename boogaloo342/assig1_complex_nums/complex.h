//
// Created by R.Peters on 10/9/2017.
//

#ifndef CSS_342_COMPLEX_H
#define CSS_342_COMPLEX_H


#include <iosfwd>

class complex {
public:
    // constructor set up
    complex(): myReal(0.0), myImaginary(0.0){};
    explicit complex(const double &r): myReal(r), myImaginary(0.0){};
    complex(const double &r, const double &im):myReal(r), myImaginary(im){};


    // getter prototypes
    double getReal() const;
    double getImaginary() const;

    // arithmetic operator overload functions
    complex operator*(const complex &rhs) const;
    complex operator*(const double &rhs) const;
    complex operator/(const complex &rhs) const;
    complex operator-(const complex &rhs) const;
    complex operator+(const complex &rhs) const;
    complex operator+(const double &rhs) const;

    // assignment arithmetic operator overloads
    complex& operator=(const complex& rhs);
    complex operator*=(const complex &rhs) ;
    complex operator*=(const double &rhs) ;
    complex operator/=(const complex &rhs) ;
    complex operator/=(const double &rhs) ;
    complex operator-=(const complex &rhs) ;
    complex operator-=(const double &rhs) ;
    complex operator+=(const complex &rhs) ;
    complex operator+=(const double &rhs) ;

    complex conjugate(const complex &conjugateMe) const;
    complex conjugate()const;

    friend std::ostream& operator<<(std::ostream &out, const complex &printMe);
    friend std::istream& operator>>(std::istream &in, complex &readMe);
    std::string makeString()const;


    bool operator==(const complex &rhs) const;

    bool operator!=(const complex &rhs) const;


private:
    complex divide(const complex& rhs);
    double myReal, myImaginary;
};
#endif //CSS_342_COMPLEX_H
