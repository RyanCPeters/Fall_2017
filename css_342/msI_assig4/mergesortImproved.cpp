//
// Created by R.Peters on 11/20/2017.
//

#ifndef MERGESORTiMPROVED_CPP
#define MERGESORTiMPROVED_CPP

#include <iostream>
#include <vector>

using namespace std;

class mergesortImproved {
public:
  
  template<class Comparable>
  explicit mergesortImproved( vector<Comparable> &data );
  
  mergesortImproved()=default;
  
  template <class Comparable>
  void beginSorting(vector<Comparable> &data );


private:
  static const unsigned short INSERTION_SORT_THRESHOLD = 10;
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
  /* If this subsection of the array is longer than INSERTION_SORT_THRESHOLD elements, then we should use a sorting approach that is
   * appropriate for larger data sets, in this case that is an iterative emulation of the mergesort algo.
   */
  if(last - first < INSERTION_SORT_THRESHOLD){
    return insertionSort(data,first, last);
  }// end of if(last-first <=INSERTION_SORT_THRESHOLD)  -- insertion block
  else{ // the subsection to sort is greater than INSERTION_SORT_THRESHOLD, we need a more efficient algorithm than  insertion.
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
  auto a1 = first, a2 = mid;
  auto b = mid+1, bEnd = last+1;
  
  /* because we start to encounter some compounding rounding errors as data.size() gets very large, we
   * need to apply some course corrections to make sure we don't lose track of calculated indices*/
//  if(data[b]> data[b+1]) {
//      ++a2,++b;
//    } else if(data[a2] < data[a2-1]) {
//      --a2,--b;
//    }
  // when the end of the left subsection is smaller than or equal to the start of the right subsection we can
  // conclude that the subsections are conveniently in order already.
  if (data[a2] <= data[b])return 1;
  if (data[first] > data[last]) {
      auto len = a2 - a1 + 1;
      for (auto i = a1; i <= a2; ++i) {
        this->swap(data, i, i + len);
      }
      return 1;
    }
  int dataSize = static_cast<int>(data.size());
  vector<Comparable> data2;
  data2.assign(data.rbegin()+(dataSize-a2)-1,data.rend()-a1);
  // d1 and d2 are the index pointers for data2
  int masterIter = first;
  Comparable dObj = data2.back(),bObj = data[b];
  ++b,data2.pop_back();
  int complete = -dataSize;
  // ToDo: describe logic of this while loop
  while( masterIter <= last && (bObj != complete || dObj != complete) ){
    uint8_t mergeState = 0;
  
    if(dObj != complete) mergeState += 1;
    if(bObj != complete) mergeState += 10;
    if(mergeState == 11){// if true, then it is safe to compare dObj and bObj
      if(dObj <= bObj) mergeState += 100;
    }
    switch(mergeState){
      case 10: // if cases 10 or 11 are true, then bObj has the next value
      case 11:
        data[masterIter++] = bObj;
        if(b < bEnd) bObj = data[b++];
        else bObj = complete;
        break;
      case 1:
      case 111:
        data[masterIter++] = dObj;
        if(!data2.empty()) dObj = data2.back(), data2.pop_back();
        else dObj = complete;
      break;
      default:
        break;
    }
  }// end of while loop
  
  return 1;
}


/**
 * if sub-array is short, then use insertion sort.
 */
template <class Comparable>
int mergesortImproved::insertionSort(vector<Comparable> &data, const int &first, const int &last) {
  for (unsigned short  i = first; i < last; ++i){
    unsigned short  smallest = i;
    for (unsigned short  j = i+1; j <= last; ++j ) if (data[j] >= 0 && data[j] < data[smallest]) smallest = j;
    if(smallest == i){
      continue;
    }
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
   *                    using 1<<(k-1).
   *
   *                k = number of divisions.
   * n/two_raisedTo_k = The number of elements per subsection
   */
  unsigned short n = static_cast<unsigned short>(data.size()), k = 1, two_raisedTo_k = static_cast<unsigned short>( 1<<(k-1));
  vector<uint16_t> myPointers;
  if (n > INSERTION_SORT_THRESHOLD*2) {
    
    // while the number of elements per subsection is >= INSERTION_SORT_THRESHOLD, increment k and
    // update two_raisedTo_k
    while (n / two_raisedTo_k >1) {
      ++k;
      two_raisedTo_k = 1 << (k-1);
    }
    
    // with k established, we can derive the minimum subsection length, and save it as 'shift.'
    long double shift = n / (static_cast<float>(two_raisedTo_k)), temp = 0;
    
    while (temp <= n){
      myPointers.push_back(static_cast<uint16_t>(temp));
      temp+=shift;
    }
    myPointers.shrink_to_fit();
    if(myPointers.size()-1 != two_raisedTo_k){
      cerr << "wtf did shit go sideways in msI?" << endl;
    }
    k = 1;
    two_raisedTo_k = 1<<(k-1);
    while(n/two_raisedTo_k>INSERTION_SORT_THRESHOLD){
      ++k;
      two_raisedTo_k = 1 << (k-1);
    }
    /* k == 0 we have nearly finished combining sub-sections of the array,
     * k == 0 is the final level of recombination*/
    while (n/two_raisedTo_k > 1) {
  
      /* correctlySorted is used to track the number of sub-sections that
       * return +1 from combineArrays method.*/
      int correctlySorted = 0;
      /* the following for-loop accounts for points in the iteration where subdivisions
       * of the data array would result in segments having fractional element counts. As per
       * the expression (n/(2)^k) = 'elements-per-subdivision.'
       *
       * So, to deal with this we use two index tracking devices, one that tracks the fractional portion
       * of shift so that we get that extra +1 when we need it, and the other handles the whole number
       * part of shift until that
       *
       *          This loop will use variable 'i' to update the low and hi bounds as
       *          we iterate through the data array.
       *
       *          Variable 'i' will grow in increments determined by the integer portion
       *          of shift (type float)
       *
       *
       * @pre i < n
       */
      for (unsigned short node = 0; node < myPointers.size(); )
      {
        unsigned short nodeLow = node;
        unsigned short nodeHi = (node+two_raisedTo_k -1 == nodeLow)?node+ two_raisedTo_k: node+ two_raisedTo_k-1;
        unsigned short nodeMid = nodeLow+(nodeHi-nodeLow)/2;
        unsigned short low = myPointers[nodeLow];
        unsigned short hi = myPointers[nodeHi];
        unsigned short mid = myPointers[nodeMid];
  
        node += (node + two_raisedTo_k == nodeHi)?two_raisedTo_k+1 : two_raisedTo_k;
        
        correctlySorted += combineArrays(data, low, mid, hi);
      }
    
      // recall that 1<<(k-1) is the number of expected sub-sections for this level of k
      // so only proceed if correctlySorted == 1<<(k-1)
      ++k;
      two_raisedTo_k = static_cast<uint16_t >(1 << (k-1));
      
    }// end of while(k >= 0) loop
  }else{
    insertionSort(data,0,n-1);
  }
}


#endif //MERGESORTiMPROVED_CPP