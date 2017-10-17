
#include <iomanip>
#include <sstream>
#include <iostream>
#include "complex.h"

using namespace std;

void spaceMaker(char fill, int width){
    cout << endl;
    cout << std::setfill(fill) << std::setw(width) ;
    cout << ""<< endl;
    cout << std::setfill(fill) << std::setw(width) ;
    cout << ""<< endl << endl;
}

int main() {
    complex c1
    , c2(1.2, 4.9)
    , c3(2.2, 1.0)
    , c4(-7.0, 9.6)
    , c5(8.1, -4.3)
    , c6(0.0, -7.1)
    , c7(6.4)
    , c8(0.0, 1.0)
    , c9(0.0, 4.1)
    , c10(0.0, -1.0)
    , c11
    ,testAgent;

    cout << "type two doubles for c11: ";
    bool test_istream_overload = false;// set true if you wish to test istream overloads, else set false for fast testing
    if(test_istream_overload) cin >> c11;
    else c11 = complex(2.90, 3.11);

    cout << "did c11 get its value? c11 = " << c11 << endl << endl;
    cout << "now we test" << endl;
    cout << "c1 = \t\t" << c1 << endl;
    cout << "c2 = \t\t" << c2 << "\nexpected =\t1.2 + 4.9i" << endl<<endl;
    cout << "c3 = \t\t" << c3 << "\nexpected =\t2.2 + i" << endl << endl;
    cout << "c4 = \t\t" << c4 << "\nexpected =\t-7.0 + 9.6i" << endl<< endl;
    cout << "c5 = \t\t" << c5 << "\nexpected =\t8.1 - 4.3i" << endl<< endl;
    cout << "c6 = \t\t" << c6 << "\nexpected =\t-7.1i" << endl<< endl;
    cout << "c7 = \t\t" << c7 << "\nexpected =\t6.4" << endl<< endl;
    cout << "c8 = \t\t" << c8 << "\nexpected =\ti" << endl<< endl;
    cout << "c9 = \t\t" << c9 << "\nexpected =\t4.1i" << endl<< endl;
    cout << "c10 = \t\t" << c10 << "\nexpected =\t-i" << endl<< endl;
    cout << "c11 = \t\t" << c11 << "\nexpected = your inputs" << endl<<endl;

    spaceMaker('-',30);


    // begin operator testing
    int testNum = 0;


    // caese 1: simple addition.
    cout << "test case "<< ++testNum << "\n";
    cout << "c1 + c2 + c3 = \n"
         << "(" << c1 << ") + "<< "(" << c2 << ") + " << "(" << c3 << ") "<< endl;
    testAgent = c1 + c2 + c3;
    cout <<"\t\t= "<< testAgent << endl
         << "expected \t= 3.4 + 5.9i" << endl << endl;

    spaceMaker('-',30);

    // 2
    cout << "test case "<< ++testNum << "\n";
    cout << "c7 - c8 - c9= \n"
         << "(" << c7 << ") - "<< "(" << c8 << ") - " << "(" << c9 << ") "<< endl;
    testAgent = c7 - c8 - c9;
    cout <<"\t\t= "<< testAgent.makeString() << endl
         << "expected \t= 6.4 - 5.1i" << endl << endl;

    spaceMaker('-',30);

    // 3
    testAgent = c2 * 22;
    cout << "test case "<< ++testNum << "\n";
    cout << "c2 * 22 = \n"
         <<"("<<c2<<") * ("<<22<<") " << endl
         <<"\t\t= " << testAgent << endl
         << "expected \t= 26.4 + 107.8i" << endl << endl;

    spaceMaker('-',30);

    // 4
    testAgent = c2 * c3;
    cout << "test case "<< ++testNum << "\n";
    cout << "c2 * c3 -> \n"
         <<"("<<c2<<") * ("<<c3<<") " << endl
         <<"\t\t= "<< testAgent << endl
         << "expected \t= -2.26 + 11.98i" << endl << endl;

    spaceMaker('-',30);

    // 5
    testAgent = c2 / c3 ;
    cout << "test case "<< ++testNum << "\n";
    cout << "c2 / c3 = \n"
         <<"("<<c2<<") / ("<<c3<<") " << endl
         <<"\t\t= "<< testAgent << endl
         << "expected \t= 1.29110 + 1.64041i" << endl << endl;

    spaceMaker('-',30);

    // 6
    testAgent = c2 / c1 ;
    cout << "test case "<< ++testNum << "\n";
    cout << "c2 / c1 = \n"
         <<"("<<c2<<") / ("<<c1<<") " << endl
         <<"\t\t= "<< testAgent << endl
         << "expected \t= values for c1 and an error statement" << endl << endl;

    spaceMaker('-',30);

    // 7
    cout << "test case "<< ++testNum << "\n";
    cout << " c2 / c5 = \n"
         <<"("<<c2<<") / ("<<c5<<") " << endl;
    testAgent = c2 / c5 ;
    cout <<"\t\t= "<< testAgent << endl
         << "expected \t= -0.13496 + 0.53329i" << endl << endl;


    spaceMaker('-',30);

    // 8
    cout << "test case "<< ++testNum << "\n";
    cout << "c4 == c4 is " << ((c4 == c4) ? "true" : "false") << endl;

    spaceMaker('-',30);

    // 9
    cout << "test case "<< ++testNum << "\n";
    cout << "c4 != c4 is " << ((c4 != c4) ? "true" : "false") << endl;

    spaceMaker('-',30);

    // 10
    cout << "test case "<< ++testNum << "\n";
    cout << "Conjugate of " << c5 << " is " << c5.conjugate() << endl;

    spaceMaker('-',30);

    // 11
    cout << "test case "<< ++testNum << "\n";
    cout << "Real of " << c3 << " is " << c3.getReal() << endl;

    spaceMaker('-',30);

    // 12
    cout << "test case "<< ++testNum << "\n";
    cout << "Imaginary of " << c4 << " is " << c4.getImaginary() << endl;

    spaceMaker('-',30);

    // 13
    cout << "test case "<< ++testNum << "\n";
    cout << "(c5 += c2) += c3 is:\n"
         << "((" << c5 << ") += ("<< c2 <<")) += ("<< c3 <<") is:\n"
         << ((c5 += c2) += c3) << endl;

    spaceMaker('-',30);

    // 14
    cout << "test case "<< ++testNum << "\n";
    cout << "(c5 -= c1) -= c2 is " << ((c5 -= c1) -= c2) << endl;

    spaceMaker('-',30);

    // 15
    cout << "test case "<< ++testNum << "\n";
    cout << "(c5 *= 22) *= 13 is " << ((c5 *= 22) *= 13) << endl;

    spaceMaker('-',30);

    // 16
    cout << "test case "<< ++testNum << "\n";
    cout << "(c5 *= c4) *= c4 is " << ((c5 *= c4) *= c4) << endl;

    spaceMaker('-',30);

    // 17
    cout << "test case "<< ++testNum << "\n";

    cout << " (c3 /= 2) / c3 is \n"
         <<"(("<<c3<<") /= "<<2<<")  / (" << c3 << ") = ";
    testAgent = (c3 /= 2) / c3  ;
    cout << testAgent << endl << "expected is: 0.5 if c3 were held constant... \n\nbut " <<
            "the fact that we will first do (c3/=2) means\n"<<
            "the later division of(expression)/c3 will be \n"<<
            "conducted with an updated value for c3.\n\nexpected is thus 1.";

    spaceMaker('-',30);

    // 18
    cout << "test case "<< ++testNum << "\n";
    cout << "c4 is " << c4 << endl;

    spaceMaker('-',30);

    // 19
    cout << "test case "<< ++testNum << "\n";
    cout << "(c4 /= c1) / c1 is " << ((c4 /= c1) / c1) << endl;

    spaceMaker('-',30);

    // 20
    cout << "test case "<< ++testNum << "\n";
    cout << "c4 is " << c4 << endl;

    spaceMaker('-',30);


} 
// 2.90 3.11
