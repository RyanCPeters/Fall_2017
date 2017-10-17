// driver for Problem 6.7, Deitel and Deitel
#include "../sources/rat.h"

// to compile under unix:   g++ rat.cpp ratdriver.cpp

int main() {
   Rational x(-2,6), y(-14,-16), z, w(4);

   x.printRational();  cout << " + ";  y.printRational();
   z = x.add(y);
   cout << " = ";  z.printRational();  cout << endl;
   z.printRational();
   cout << " = ";  z.printRationalAsFloat();  cout << endl << endl;

   x.printRational();  cout << " - ";  y.printRational();
   z = x.subtract(y);
   cout << " = ";  z.printRational();  cout << endl;
   z.printRational();
   cout << " = ";  z.printRationalAsFloat();  cout << endl << endl;

   x.printRational();  cout << " * ";  y.printRational();
   z = x.multiply(y);
   cout << " = ";  z.printRational();  cout << endl;
   z.printRational();
   cout << " = ";  z.printRationalAsFloat();  cout << endl << endl;

   x.printRational();  cout << " / ";  y.printRational();
   z = x.divide(y);
   cout << " = ";  z.printRational();  cout << endl;
   z.printRational();
   cout << " = ";  z.printRationalAsFloat();  cout << endl;

   return 0;
}

