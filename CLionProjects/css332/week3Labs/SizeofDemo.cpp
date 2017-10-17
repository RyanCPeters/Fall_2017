//
//  SizeofDemo.cpp
//
//  Created by Rob Nash on 10/8/13.
//  Modified by Michael Stiber on 1/30/14.
//  Modified by Morteza Chini Autumn 2017.
//  Copyright (c) 2013 Rob Nash. All rights reserved.
//

#include <iostream>
#include <cstring>

using namespace std;

// ------ YOUR ANSWERS GO HERE ---------------------------------------
// 1.
// 2.
// 3.
// 4.
//
// --------------------------------------------------------------------

int main(int argc, const char * argv[])
{
  //note that sizeof is always returning byte count
  cout << "sizeof bool = " << sizeof(bool)<<endl;
  cout << "sizeof char = " << sizeof(char)<<endl;
  cout << "sizeof short = " << sizeof(short) <<endl;
  cout << "sizeof int = " << sizeof(int) <<endl;
  cout << "sizeof float = " << sizeof(float)<<endl;
  cout << "sizeof double = " << sizeof(double)<<endl;
  cout << "sizeof int* = " << sizeof(int*) <<endl;
  cout << "sizeof void* = " << sizeof(void*) <<endl;
  cout << "sizeof long = " << sizeof(long)<<endl;
  cout << "sizeof long double = " << sizeof(long double)<<endl;
  cout << endl << endl;
    
    
  char word[] = {'T','e','s','t','i','n','g'};  //a proper c-style string?
  char word2[] = "Testing";                     //a proper c-style string?
   
  //why is one string above larger than the other?
  cout << "sizeof word array = " << sizeof(word)<<endl;
  cout << "sizeof word2 array = " << sizeof(word2)<<endl;
  cout << "sizeof word[] element = " << sizeof(word[0])<<endl;
  cout << endl << endl;
  
   // Below, assign the vale "Rope" to word2 array. Explain your observation.


  // Now, Change the output of word[] to "Resting, instead of the original Testing ?
  cout << "\nOriginal word[] looked like this: " ; 
   for (int i = 0; i < strlen(word); i++)            
    cout << (word[i]) << " ";      // What are we seeing here?
  cout << endl;
  
  //Your code here:

  cout << "\nAfter modification word[] looks like this: ";
   for (int i = 0; i < strlen(word); i++)            
	cout << (word[i]) << " ";      // What are we seeing here?
  cout << endl;
   
  //why is one string above larger than the other?
  cout << "sizeof word array = " << sizeof(word)<<endl;
  cout << "sizeof word2 array = " << sizeof(word2)<<endl;
  cout << "sizeof word[] each element = " << sizeof(word[0])<<endl;
  cout << endl << endl;
    
    
    
  int nums[] = {3,2,1};              //3 items, so why does the sizeof report 12?
  cout << "sizeof nums array = " << sizeof(nums)<<endl;
  cout << "sizeof nums element = " << sizeof(nums[0])<<endl;
  cout << "Number of elements in nums array = " 
  //your single line of code to display the number of elements in nums array goes below:
       
	   

  int *moreNums = new int[10];
  cout << "sizeof moreNums array = " << sizeof(moreNums)<<endl;

  cout << "moreNums's contents initially are:" << endl;
  for (int i=0; i<10; i++)   // Let's see the junk there
    cout << moreNums[i] << " ";
  cout << endl;

  // Memset fills BYTES (on your output window: negative numbers indicate junk, positive numbers represent bytes)
  // First parameter: where to fill(pointer to memory), 2nd parameter: how many bytes(what to set each byte to)
  // 3rd parameter: size of array(number of bytes to set))
  
  memset(moreNums, 1, sizeof(moreNums)); // if memset() didn't work as expected, then fix it.
  
  
  cout << "moreNums's contents after memset():" << endl;
  for (int i = 0; i < 10; i++)   // Let's see the junk there
    cout << moreNums[i] << " ";
  cout << endl;
  
    
    
  return 0;
}

