/*
 *  ReadNumber.cpp
 *
 *  Created by Morteza Chini on 09/06/2017
 *  
 */

#include <iostream>
#include "readnumbersio.h"

using namespace std;

//-----------------------------------------------------------------------------//
//1.	Build and compile this code and report your findings in this box:

/* YOUR OBSERVATION HERE:
Initially, there either needed to be a forward declaration for the displaySum function
 or the main function needed to be moved bellow displaySum.

The subsequent task of moving displaySum and readNumber functions to a separate file
 also required appropriate use of the header file in order to get around the multiple
 definition error when simply making forward declarations.
//*/

//2.	What is std::cin and std::endl used for and how can you eliminate repeating them?

/*
      by using the declaration of:
      using namespace std;

      This appears to preform a similar function to importing class files in Java, such as:
      import java.awt.Color;

      In both java, and c++, the above mentioned calls allow the programmer to declare the
      intended scope of specific function calls for the entire file.
//*/

//3.	Be sure your code compiles.
//
//      Now, modify your code so that readNumber() and
//	    displaySum() live in a separate file called “ReadNumbersIO.cpp”. The main method
//      will remain in the readNumber.cpp.
//
//      Use a forward declaration to access them from main().

//4.	Finally, further modify your latest code to a more conventional style of having
//		a header file (named readnumbersio.h) to access the functions instead of using
//      forward declarations directly in your code. Name your (.cpp) files. Make sure your
//      header file uses header guards.(Ask me about header guards if you are not familiar
//	    with them)
//---------------------------------------------------------------------//


// Driver to test our code

int main()
{
    int x = readNumber();
    int y = readNumber();
    displaySum(x + y);   // using operator + to pass the sum of x and y to displaySum()
    cout << "Did you remember to eliminate std::cout and std::endl in your code? "
         << endl;
    return 0;

}