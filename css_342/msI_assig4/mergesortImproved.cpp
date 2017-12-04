//
// Created by R.Peters on 11/20/2017.
//

#ifndef MERGESORTiMPROVED_CPP
#define MERGESORTiMPROVED_CPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include "WorkDir.h"

using namespace std;

#define TERMINATOR_SIGN(num) ~num-1;

class mergesortImproved {
public:
  
  template<class Comparable>
  explicit mergesortImproved( vector<Comparable> &data );
  
  mergesortImproved()=default;
  
  template <class Comparable>
  void beginSorting(vector<Comparable> &data );


private:
//  string fileName;
  
  template<class Comparable>
  int inPlaceMerge(vector<Comparable> &data, const int &first, const int &mid, const int &last);
  
  template<class Comparable>
  int insertionSort(vector<Comparable> &data, const int &first, const int &last);
  
  template<class Comparable>
  int combineArrays(vector<Comparable> &data, const int &first, const int &mid, const int &last);
  
  template<class Comparable>
  void swap(vector<Comparable> &data, const int &low, const int &hi);
  
  
};

/**
 *
 * @tparam Comparable Any data type that has a natural order that permits the use of equality opperators.
 * @param data
 */
template <class Comparable>
mergesortImproved::mergesortImproved(vector<Comparable> &data) {
  beginSorting(data);
}


/** int mergesortImproved::combineArrays(vector<Comparable> &data,int first, int last)
 *
 * As the name implies, this function recombines our pointer-bounded subsections of the original array.
 * This function will inevitably have to create n/2 temporary holding arrays for the task of moving data points.
 *
 * @tparam Comparable
 * @param data
 * @param first
 * @param mid
 * @param last
 * @return
 */
template <class Comparable>
int mergesortImproved::combineArrays(vector<Comparable> &data, const int &first, const int &mid, const int &last)
{
  if(first > last || first < 0 || last < 0) return 0;
  if(last == first )return 1;
  /* If this subsection of the array is longer than 10 elements, then we should use a sorting approach that is
   * appropriate for larger data sets, in this case that is an iterative emulation of the mergesort algo.
   */
  if(last - first <= 10){
    return insertionSort(data,first, last);
  }// end of if(last-first <=10)  -- insertion block
  else{ // the subsection to sort is greater than 10, we need a more efficient algorithm than  insertion.
    return inPlaceMerge(data,first,mid,last);
  }
} // end of combineArrays function

/**
 *
 * @tparam Comparable
 * @param data
 * @param first
 * @param mid
 * @param last
 * @return
 */
template <class Comparable>
int mergesortImproved::inPlaceMerge(vector<Comparable> &data, const int &first, const int &mid, const int &last)
{
  auto a1 = first, a2 = mid - 1;
  auto b1 = mid, b2 = last;
  
  /* because we start to encounter some compounding rounding errors as data.size() gets very large, we
   * need to apply some course corrections to make sure we don't lose track of calculated indices*/
  if(data[b1]> data[b1+1]) {
      ++a2,++b1;
    } else if(data[a2] < data[a2-1]) {
      --a2,--b1;
    }
  // when the end of the left subsection is smaller than or equal to the start of the right subsection we can
  // conclude that the subsections are conveniently in order already.
  if (data[a2] <= data[b1])return 1;
  if (data[first] > data[last]) {
      auto len = a2 - a1 + 1;
      for (auto i = a1; i <= a2; ++i) {
        this->swap(data, i, i + len);
      }
      return 1;
    }
  auto dataSize = data.size();
  vector<Comparable> data2;
  data2.assign(data.begin()+a1,data.begin()+a2);
  // d1 and d2 are the index pointers for data2
  int d1 = 0, d2 = (int)data2.size(), masterIter = a1;
  if(d2+a1 == b1)--d2;
  Comparable dObj = data2[d1], bObj = data[b1];
  int complete = (int)TERMINATOR_SIGN(dataSize);
  // ToDo: describe logic of this while loop
  while(masterIter <= last){
      
      // if bObj == complete, then bObj is < 0, so dObj should never be <= bObj unless both are complete,
      // in which case we don't want it to succeed... hence the ^ operator (XOR)
      while(masterIter <= last && d1 <= d2 && dObj >= 0 && ((bObj == complete) ^ (dObj <= bObj))){
//        assert(masterIter <= b1+1 || b1 == b2);
        data[masterIter++] = dObj;
        dObj = data2[d1+1];
        ++d1;
      }
      // if dObj == complete, then dObj is < 0, so bObj should never be <= dObj unless both are complete,
      // in which case we don't want it to succeed... hence the ^ operator (XOR)
      while( masterIter <= last && b1 <= b2 && bObj >= 0 && ((dObj == complete) ^ (bObj < dObj))){
        // In the event that masterIter catches up to b1, we will encounter a slow section in sorting
        // process as the following swap-fest-shit-show will transpire until b1 == b2;
        if(masterIter >= b1+1){
          --d1; // decrement d1 so that we don't overwrite any relevant data at d1's current location.
          data2[d1] = dObj;
          dObj = data[b1+1];
          data[masterIter++] = bObj;
          bObj = dObj;
          ++b1;
          dObj = data2[d1];
          ++d1;
        }else {
          data[masterIter++] = bObj;
          assert(masterIter <= b1+1 || b1 == b2);
          bObj = data[b1 + 1];
          ++b1;
        }
      }
      
      if(b1 > b2)bObj = complete;
      if(d1 > d2)dObj = complete;
    }// end of while loop
  return 1;
}


/**
 * if sub-array is short, then use insertion sort.
 */
template <class Comparable>
int mergesortImproved::insertionSort(vector<Comparable> &data, const int &first, const int &last) {
  for (auto i = first; i < last; ++i){
    auto smallest = i;
    for (auto j = i+1; j <= last; ++j ) if (data[j] >= 0 && data[j] < data[smallest]) smallest = j;
    if(smallest == i)continue;
    // if smallest is not greater than i, then we have nothing to swap
    mergesortImproved::swap(data,smallest,i);
  }// end of for i
  return 1; // this return is only accessed if we end up using insertion sort.
}// end of combineArrays(data,first,last) function

/**
 *
 * @param data
 * @param low
 * @param hi
 */
template <class Comparable>
void mergesortImproved::swap(vector<Comparable> &data, const int &low, const int &hi) {
  int tmp = data[low];
  data[low] = data[hi];
  data[hi] = tmp;
}

template<class Comparable>
void mergesortImproved::beginSorting(vector<Comparable> &data) {
  /* setting control variables where:
   *
   *                n = total number of elements in data
   *
   *  two_raisedTo_k  = the number of subsections in data after k divisions,
   *                    expressed in math notation as (2)^k, and derived here
   *                    using 1<<k.
   *
   *                k = number of divisions.
   * n/two_raisedTo_k = The number of elements per subsection
   */
  int n = (int)data.size(), k = 0, two_raisedTo_k = 1<<k;
  if (n <= 10){
    combineArrays(data,0,0,n-1);
    return;
  }
  
  // while the number of elements per subsection is >= 10, increment k and
  // update two_raisedTo_k
  while(n/two_raisedTo_k >= 10 ) two_raisedTo_k = 1<<(++k);
  
  // with k established, we can derive the minimum subsection length, and save it as 'shift.'
  auto shift = n/((float)two_raisedTo_k);
  
  /* k == 0 we have nearly finished combining sub-sections of the array,
   * k == 0 is the final level of recombination*/
  while(k >= 0){
    
    auto idx = 0.0;
    
    /* correctlySorted is used to track the number of sub-sections that
     * return +1 from combineArrays method.*/
    int correctlySorted = 0;
    
    /* the following for-loop accounts for points in the iteration where subdivisions
     * of the data array would result in segments having fractional element counts. As per
     * the expression (n/(2)^k) = 'elements-per-subdivision.'
     *
     * So, to deal with this we use two index tracking devices, one that tracks the fractional portion
     * of shift so that we get that extra +1 when we need it, and the other handles the whole number
     * part of shift until that +1 happens.
     *
     *          This loop will use variable 'i' to update the low and hi bounds as
     *          we iterate through the data array.
     *
     *          Variable 'i' will grow in increments determined by the integer portion
     *          of shift (type float
     *         )
     *
     *
     * @pre i < n
     */
    for(int i = 0; i < n;){
      auto low = i;
      idx+=shift;
      i = (int)idx;
      auto mid = low+(int)((shift/2));
      auto hi = (i-1 > low)?i-1 : i;
      correctlySorted += combineArrays(data, low, mid, hi);
    }
    
    // recall that 1<<k is the number of expected sub-sections for this level of k
    // so only proceed if correctlySorted == 1<<k
    if(correctlySorted == two_raisedTo_k) {
      --k;
      two_raisedTo_k = 1<<k;
      shift = n/(float)two_raisedTo_k;
    }
  }// end of while(k >= 0) loop
}
#endif //MERGESORTiMPROVED_CPP