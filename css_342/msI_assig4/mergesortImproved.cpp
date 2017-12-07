//
// Created by R.Peters on 11/20/2017.
//

#ifndef MERGESORTiMPROVED_CPP
#define MERGESORTiMPROVED_CPP

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class mergesortImproved
{
public:
  
  template<class Comparable>
  explicit mergesortImproved( vector<Comparable> &data );
  
  mergesortImproved()=default;
  
  template <class Comparable>
  void beginSorting(vector<Comparable> &data );


private:
  static const unsigned short INSERTION_SORT_THRESHOLD = 7;
//  string fileName;
  template<class Comparable>
  void inPlaceMerge(vector<Comparable> &data, const int &first, const int &mid, const int &last);
  
  template<class Comparable>
  void insertionSort(vector<Comparable> &data, const int &first, const int &last);
  
  template<class Comparable>
  void combineArrays(vector<Comparable> &data, const int &first, const int &mid, const int &last);
  
  template<class Comparable>
  void swap(vector<Comparable> &data, const int &low, const int &hi);
};

/** template <class Comparable> mergesortImproved::mergesortImproved(vector<Comparable> &data)
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param data          The vector<Comparable> that is to be sorted
 */
template <class Comparable>
mergesortImproved::mergesortImproved(vector<Comparable> &data)
{
  beginSorting(data);
}


/** template <class Comparable> int mergesortImproved::combineArrays(vector<Comparable> &data, const int &first, const int &mid, const int &last)
 *
 * As the name implies, this function recombines our pointer-bounded subsections of the original array.
 * This function will inevitably have to create n/2 temporary holding arrays for the task of moving data points.
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param data          The vector<Comparable> that is to be sorted
 *
 * @param first         the low-bound for the subsection of vector<Comparable> data that we are going to be sorting.
 *
 * @param mid           The index value that falls in the middle of first and last, used to subdevide the section we are
 *                      about to sort.
 *
 * @param last          The high-bound for the subsection of vector<Comparable> data that we are going to be sorting.
 */
template <class Comparable>
void mergesortImproved::combineArrays(vector<Comparable> &data, const int &first, const int &mid, const int &last)
{
  if(first > last || first < 0 || last < 0) return;
  if(last == first )return;
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

/** template <class Comparable> int mergesortImproved::inPlaceMerge(vector<Comparable> &data, const int &first, const int &mid, const int &last)
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param data          The vector<Comparable> that is to be sorted
 *
 * @param first         the low-bound for the subsection of vector<Comparable> data that we are going to be sorting.
 *
 * @param mid           The index value that falls in the middle of first and last, used to subdevide the section we are
 *                      about to sort.
 *
 * @param last          The high-bound for the subsection of vector<Comparable> data that we are going to be sorting.
 */
template <class Comparable>
void mergesortImproved::inPlaceMerge(vector<Comparable> &data, const int &first, const int &mid, const int &last)
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
  if (data[a2] <= data[b])return;
  if (data[first] > data[last]) {
      auto len = a2 - a1 + 1;
      for (auto i = a1; i <= a2; ++i) {
        this->swap(data, i, i + len);
      }
      return;
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
  
  return;
}


/** template <class Comparable> int mergesortImproved::insertionSort(vector<Comparable> &data, const int &first, const int &last)
 *
 * if sub-array is short, then use insertion sort.
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param data          The vector<Comparable> that is to be sorted
 *
 * @param first         the low-bound for the subsection of vector<Comparable> data that we are going to be sorting.
 *
 *
 * @param last           The high-bound for the subsection of vector<Comparable> data that we are going to be sorting.
 */
template <class Comparable>
void mergesortImproved::insertionSort(vector<Comparable> &data, const int &first, const int &last)
{
  for (unsigned short  i = first; i < last; ++i){
    unsigned short  smallest = i;
    for (unsigned short  j = i+1; j <= last; ++j ) if (data[j] >= 0 && data[j] < data[smallest]) smallest = j;
    if(smallest == i) continue;
    
    // if we get here, then smallest > i, and we have something to swap
    this->swap(data,smallest,i);
  }// end of for i
}// end of combineArrays(data,first,last) function

/** template <class Comparable> void mergesortImproved::swap(vector<Comparable> &data, const int &low, const int &hi)
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param data          The vector<Comparable> that is to be sorted
 *
 * @param low           The lower indexed value from the vector<Comparable> data that we are going to be swapping.
 *
 * @param hi            the higher indexed value from the vector<Comparable> data that we are going to be swapping.
 */
template <class Comparable>
void mergesortImproved::swap(vector<Comparable> &data, const int &low, const int &hi)
{
  int tmp = data[low];
  data[low] = data[hi];
  data[hi] = tmp;
}

/** template<class Comparable> void mergesortImproved::beginSorting(vector<Comparable> &data)
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param data          The vector<Comparable> that is to be sorted
 */
template<class Comparable>
void mergesortImproved::beginSorting(vector<Comparable> &data)
{
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
  stack<stack<unsigned short>> levelStack;
  /*
    This check is against threshold*2 because anything less than that will be handled in two sequential calls to
    insertionSort. This saves a small amount of time when sorting small collections.
    
    */
  if (n > INSERTION_SORT_THRESHOLD*2) {
    
    while(n/two_raisedTo_k > INSERTION_SORT_THRESHOLD){
      ++k;
      two_raisedTo_k = static_cast<unsigned short>(1<< (k-1));
    }
    // while the number of elements per subsection is >= INSERTION_SORT_THRESHOLD, increment k and
    // update two_raisedTo_k
    while (n / two_raisedTo_k < n) {
      if(n/two_raisedTo_k > INSERTION_SORT_THRESHOLD) {
        long double shift = n / (static_cast<float>(two_raisedTo_k)), temp = 0;
        stack<unsigned short> idxPtrStk;
        while (temp <= n) {
          idxPtrStk.push(static_cast<unsigned short>(temp));
          temp += shift;
        }
        levelStack.push(idxPtrStk);
      }
      --k;
      two_raisedTo_k = static_cast<unsigned short>(1<< (k-1));
    }
    
    /* k == 0 we have nearly finished combining sub-sections of the array,
     * k == 0 is the final level of recombination*/
    while (!levelStack.empty()) {
      stack<unsigned short> idxPtrStk = levelStack.top();
      levelStack.pop();
      
      while (!idxPtrStk.empty()) {
        unsigned short hi = idxPtrStk.top();
        idxPtrStk.pop();
        unsigned short mid = idxPtrStk.top();
        idxPtrStk.pop();
        unsigned short low = idxPtrStk.top();
        idxPtrStk.pop();
        combineArrays(data, low, mid, hi);
      }
    }
  }else{
    insertionSort(data,0,n-1);
  }
}


#endif //MERGESORTiMPROVED_CPP