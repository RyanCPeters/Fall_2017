//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2016 __Pearson Education__. All rights reserved.

#include <iostream>
#include <vector>

using namespace std;
class quicksort{
public:
  quicksort() = default;
  template <class Comparable>
  void qsBeginSorting(vector<Comparable> &data);
private:
  template<class Comparable>
  void insertionSort(vector<Comparable> &theArray, const int &first, const int &last);
  
  template<class Comparable>
  void order(vector<Comparable> &theArray, const int &i, const int &j);
  
  template<class Comparable>
  int sortFirstMiddleLast(vector<Comparable> &data, const int &first, const int &last);
  
  template<class Comparable>
  int partition(vector<Comparable> &data, const int &first, const int &last);
  
  template<class Comparable>
  void quickSort(vector<Comparable> &data, const int &first, const int &last);
  
  template<class Comparable>
  void swap(Comparable &a, Comparable &b);
};
static const int MIN_SIZE  = 10; // Smallest size of an array that quicksort will sort

/** Sorts the items in an array into ascending order.
 * @pre  None.
 * @post  theArray is sorted into ascending order; n is unchanged.
 * @param theArray  The given array.
 * @param n  The size of theArray.
 */
template<class Comparable>
void quicksort::insertionSort(vector<Comparable> &theArray, const int &first, const int &last)
{
  // unsorted = first index of the unsorted region,
  // loc = index of insertion in the sorted region,
  // nextItem = next item in the unsorted region.
  // Initially, sorted region is theArray[0],
  // unsorted region is theArray[1..n-1].
  // In general, sorted region is theArray[0..unsorted-1],
  // unsorted region theArray[unsorted..n-1]
  for (int unsorted = first + 1; unsorted <= last; unsorted++)
  {
    // At this point, theArray[first..unsorted-1] is sorted.
    // Find the right position (loc) in theArray[first..unsorted]
    // for theArray[unsorted], which is the first entry in the
    // unsorted region; shift, if necessary, to make room
    Comparable nextItem = theArray[unsorted];
    int loc = unsorted;
    while ((loc > first) && (theArray[loc - 1] > nextItem))
    {
      // Shift theArray[loc - 1] to the right
      theArray[loc] = theArray[loc - 1];
      --loc;
    }  // end while
    
    // At this point, theArray[loc] is where nextItem belongs
    theArray[loc] = nextItem; // Insert nextItem into sorted region
  }  // end for
}  // end insertionSort

/** template<class Comparable> void quicksort::order(vector<Comparable> &theArray, const int &i, const int &j)
 *
 * Arranges two specified array entries into sorted order by
 * exchanging them, if necessary.
 *
 *@param theArray  The given array.
 *@param i  The index of the first entry to consider in theArray.
 *@param j  The index of the second entry to consider in theArray.
 */
template<class Comparable>
void quicksort::order(vector<Comparable> &theArray, const int &i, const int &j)
{
  if (theArray[i] > theArray[j])
    quicksort::swap(theArray[i], theArray[j]); // Exchange entries
}  // end order

/** Arranges the first, middle, and last entry in an array in sorted order.
 @pre  theArray[first..last] is an array; first <= last.
 @post  theArray[first..last] is is arranged so that its
 first, middle, and last entries are in sorted order.
 @param theArray  The given array.
 @param first  The first entry to consider in theArray.
 @param last  The last entry to consider in theArray.
 @return  The index of the middle entry. */
template<class Comparable>
int quicksort::sortFirstMiddleLast(vector<Comparable> &theArray, const int &first, const int &last)
{
  int mid = first + (last - first) / 2;
  order(theArray, first, mid); // Make theArray[first] <= theArray[mid]
  order(theArray, mid, last);  // Make theArray[mid] <= theArray[last]
  order(theArray, first, mid); // Make theArray[first] <= theArray[mid]
  
  return mid;
}  // end sortFirstMiddleLast


/** Partitions the entries in an array about a pivot entry for quicksort.
 @pre  theArray[first..last] is an array; first <= last.
 @post  theArray[first..last] is partitioned such that:
 S1 = theArray[first..pivotIndex-1] <= pivot
 theArray[pivotIndex]          == pivot
 S2 = theArray[pivotIndex+1..last]  >= pivot
 @param theArray  The given array.
 @param first  The first entry to consider in theArray.
 @param last  The last entry to consider in theArray.
 @return  The index of the pivot. */
template<class Comparable>
int quicksort::partition(vector<Comparable> &theArray, const int &first, const int &last)
{
  // Choose pivot using median-of-three selection
  int pivotIndex = sortFirstMiddleLast(theArray, first, last);
  
  // Reposition pivot so it is last in the array
  quicksort::swap(theArray[pivotIndex], theArray[last - 1]);
  pivotIndex = last - 1;
  Comparable pivot = theArray[pivotIndex];
  
  // Determine the regions S1 and S2
  int indexFromLeft = first + 1;
  int indexFromRight = last - 2;
  
  bool done = false;
  while (!done)
  {
    // Locate first entry on left that is >= pivot
    while (theArray[indexFromLeft] < pivot) ++indexFromLeft;
    
    // Locate first entry on right that is <= pivot
    while (theArray[indexFromRight] > pivot) --indexFromRight;
    
    if (indexFromLeft < indexFromRight)
    {
      quicksort::swap(theArray[indexFromLeft], theArray[indexFromRight]);
      ++indexFromLeft;
      --indexFromRight;
    }
    else
      done = true;
  }  // end while
  
  // Place pivot in proper position between S1 and S2, and mark its new location
  quicksort::swap(theArray[pivotIndex], theArray[indexFromLeft]);
  pivotIndex = indexFromLeft;
  
  return pivotIndex;
}  // end partition



// Listing 11-5.
/** Sorts an array into ascending order. Uses the quick sort with
 median-of-three pivot selection for arrays of at least MIN_SIZE
 entries, and uses the insertion sort for other arrays.
 @pre  theArray[first..last] is an array.
 @post  theArray[first..last] is sorted.
 @param theArray  The given array.
 @param first  The first element to consider in theArray.
 @param last  The last element to consider in theArray. */
template<class Comparable>
void quicksort::quickSort(vector<Comparable> &theArray, const int &first, const int &last)
{
  if (last - first + 1 < MIN_SIZE)
  {
    insertionSort(theArray, first, last);
  }
  else
  {
    // Create the partition: S1 | Pivot | S2
    int pivotIndex = partition(theArray, first, last);
    
    // Sort subarrays S1 and S2
    quickSort(theArray, first, pivotIndex - 1);
    quickSort(theArray, pivotIndex + 1, last);
  }  // end if
}

template<class Comparable>
void quicksort::qsBeginSorting(vector<Comparable> &data) {
  if(data.size() > 1) quickSort(data, 0, (int)data.size()-1);
}

template<class Comparable>
void quicksort::swap(Comparable &a, Comparable &b) {
  Comparable tmp = a;
  a = b;
  b = tmp;
}
// end quickSort

//int main()
//{
//   vector<string> a = {"Z", "X", "R", "K", "F", "B"};
//   quickSort(a, 0, 5);
//   for (int i = 0; i < 6; i++)
//      cout << a[i] << " ";
//   cout << std::endl;
//
//   string b[26] = {"Z", "Y", "X", "W", "V", "U", "T", "S", "R", "Q", "P", "O", "N", "M", "L", "K", "J", "I", "H", "G", "F", "E", "D", "C", "B", "A"};
//   quickSort(b, 0, 25);
//   for (int i = 0; i < 26; i++)
//      cout << b[i] << " ";
//   cout << std::endl;
//}  // end main

/*
 
 B F K R X Z
 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 
 */