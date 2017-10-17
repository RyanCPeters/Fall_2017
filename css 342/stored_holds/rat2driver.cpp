// driver for problem 8.17, Deitel and Deitel
#include "rat2.h"

// demonstrate Rational numbers, operator overloading, etc.

int main() {
   Rational w(4), x(7,3), y(3,9), z, copy(x);

   cout << "The copy object looks just like its parameter, copy = " << copy
	<< endl;
   z = x + y;
   cout << x << " + " << y << " = " << z << endl;

   z = w + y;
   cout << w << " + " << y << " = " << z << endl;

   z = x - y;
   cout << x << " - " << y << " = " << z << endl;

   z = x * y;
   cout << x << " * " << y << " = " << z << endl;

   z = x / y;
   cout << x << " / " << y << " = " << z << endl;

   z = x + 5;
   cout << x << " + " << 5 << " = " << z << endl;

   //ERROR -- no match for operator +(int, class Rational)
   // z = 5 + x;    

   z = Rational(5) + x;
   cout << 5 << " + " << x << " = " << z << endl;
 
   //ERROR -- no match for operator -(class Rational, class Rational)
   // z -= x;                    

   cout << x << " is:" << endl;

   cout << ((x > y) ? "    > " : "    not > ");
   cout << y << " according to the overloaded > operator\n";

   cout << ((x < y) ? "    < " : "    not < ");
   cout << y << " according to the overloaded < operator\n";

   cout << ((x >= y) ? "    >= " : "    not >= ");
   cout << y << " according to the overloaded >= operator\n";

   cout << ((x <= y) ? "    <= " : "    not <= ");
   cout << y << " according to the overloaded <= operator\n";

   cout << ((x == y) ? "    == " : "    not == ");
   cout << y << " according to the overloaded == operator\n";

   cout << ((x != y) ? "    != " : "    not != ");
   cout << y << " according to the overloaded != operator" << endl;

   cout << x << " + " << y;
   x += y;
   cout << " = the now changed " << x << endl;

   return 0;
}

