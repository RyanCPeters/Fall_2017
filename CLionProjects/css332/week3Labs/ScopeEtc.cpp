/*
 * ScopeEtc.cpp
 *
 * Code to show some things about scope, variable lifespan, and lvalues.
 *
 * Created by Michael Stiber on 1/31/14
 * Modified by Morteza Chini Autumn 2017
 */

#include <iostream>
#include "SuperInt.h"

using namespace std;

// ---- YOUR ANSWERS GO HERE -----------------------------------------
// 1.
// 2.
// 3.
// 4.
// -------------------------------------------------------------------

SuperInt var(0, "global");

int main()
{
  cout << "At start of main()" << endl;

  cout << "var's value is " << var.theValue() << endl << endl;

  SuperInt var2(1, "Main");
  cout << "var2's value is " << var2.theValue() << endl << endl;


  cout << "Entering top block" << endl;
  {
    SuperInt var2(2, "block");
    cout << "var2's value is " << var2.theValue() << endl << endl;
  }
  cout << "Exiting top block" << endl << endl;;


  cout << "Entering bottom block" << endl;
  {
    static SuperInt var2(2, "static");
    cout << "var2's value is " << var2.theValue() << endl << endl;
  }
  cout << "Exiting bottom block" << endl << endl;

  int i = var2.theValue();
  
  //----- Add your code for item 3 here, test your result using this line of code -----
  
  
  //cout << "Value of var2.theValue() was set to: " << var2.theValue() << endl;
  //-----------------------------------------------------------------------------------

  SuperInt* pvar = new SuperInt(3, "dynamic");

  cout << "At end of main()" << endl;
 
  // Display myValue(private data member) of the object that pvar is pointing to.
  // How would you prevent memory leak here?

  

  // Display (myValue, private data member) of the object that pvar is pointing to to test your solution.
  // How do you know if your solution is working?


  
}   

