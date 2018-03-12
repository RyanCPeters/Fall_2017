//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2016 __Pearson Education__. All rights reserved.

// Listing 11-4.

#include <iostream>
#include <vector>

using namespace std;
class mergesort{
public:
  mergesort() = default;
  template <class Comparable>
  void msBeginSorting(vector<Comparable> &data);
private:
  template<class Comparable>
  void merge(vector<Comparable> &theArray, unsigned int first, unsigned int mid, unsigned int last);
  template<class Comparable>
  void mergeSort(vector<Comparable> &theArray, unsigned int first, unsigned int last);
  
};
const unsigned int MAX_SIZE = 50;


/** Merges two sorted array segments theArray[first..mid] and
    theArray[mid+1..last] into one sorted array.
 @pre  first <= mid <= last. The subarrays theArray[first..mid] and
    theArray[mid+1..last] are each sorted in increasing order.
 @post  theArray[first..last] is sorted.
 @param theArray  The given array.
 @param first  The index of the beginning of the first segment in theArray.
 @param mid  The index of the end of the first segment in theArray;
    mid + 1 marks the beginning of the second segment.
 @param last  The index of the last element in the second segment in theArray.
 @note  This function merges the two subarrays into a temporary
    array and copies the result into the original array theArray. */

template<class Comparable>
void mergesort::merge(vector<Comparable> &theArray, unsigned int first, unsigned int mid, unsigned int last) {
	if(theArray.size() == 0)return;
  vector<Comparable> tempArray;  // Temporary array
  tempArray.reserve(theArray.size());
  // Initialize the local indices to indicate the subarrays
  unsigned int first1 = first;            // Beginning of first subarray
  unsigned int last1 = mid;               // End of first subarray
  unsigned int first2 = mid + 1;          // Beginning of second subarray
  unsigned int last2 = last;              // End of second subarray
  
  // While both subarrays are not empty, copy the
  // smaller item into the temporary array
  unsigned int index = first1;            // Next available location in tempArray
  while ((first1 <= last1) && (first2 <= last2))
  {
    // At this point, tempArray[first..index-1] is in order
    if (theArray[first1] <= theArray[first2])
    {
      tempArray[index] = theArray[first1];
      ++first1;
    }
    else
    {
	    tempArray[index] = theArray[first2];
      ++first2;
    }  // end if
    ++index;
  }  // end while
  
  // Finish off the first subarray, if necessary
  while (first1 <= last1)
  {
    // At this point, tempArray[first..index-1] is in order
    tempArray[index] = theArray[first1];
	  ++first1;
	  ++index;
  }  // end while
  
  // Finish off the second subarray, if necessary
  while (first2 <= last2)
  {
    // At this point, tempArray[first..index-1] is in order
	  tempArray[index] = theArray[first2];
    ++first2;
	  ++index;
  }  // end for
  
  // Copy the result back into the original array
  for (index = first; index <= last; ++index)
    theArray[index] = tempArray[index];
}
// end merge

/** Sorts the items in an array into ascending order.
 @pre  theArray[first..last] is an array.
 @post  theArray[first..last] is sorted in ascending order.
 @param theArray  The given array.
 @param first  The index of the first element to consider in theArray.
 @param last  The index of the last element to consider in theArray. */
template<class ItemType>
void mergesort::mergeSort(vector<ItemType> &theArray, unsigned int first, unsigned int last) {
  if (first < last)
  {
    // Sort each half
    unsigned int mid = first + (last - first) / 2; // Index of midpoint
    
    // Sort left half theArray[first..mid]
    mergeSort(theArray, first, mid);
    
    // Sort right half theArray[mid+1..last]
    mergeSort(theArray, mid + 1, last);
    
    // Merge the two halves
    merge(theArray, first, mid, last);
  }  // end if
}
// end mergeSort
template <class Comparable>
void mergesort::msBeginSorting(vector<Comparable> &theArray){
 
	if(theArray.size() > 1 ){
		unsigned int first = 0, last = static_cast<unsigned int>(theArray.size()-1);
		mergeSort(theArray,first,last);
	}
}

//int main()
//{
//   vector<string> a = {"Z", "X", "R", "K", "F", "B"};
//   mergeSort(a, 0, 5);
//   for (int i = 0; i < 6; i++)
//      std::cout << a[i] << " ";
//   std::cout << std::endl;
//
//}  // end main

/*

 B F K R X Z 
 
 */

