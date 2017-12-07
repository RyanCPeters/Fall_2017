//
// Created by R.Peters on 12/7/2017.
//

#ifndef MSI_ASSIG4_MERGESORTIMPROVED_H
#define MSI_ASSIG4_MERGESORTIMPROVED_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

class mergesortImproved
{
public:
  
  template<class Comparable>
  explicit mergesortImproved( std::vector<Comparable> &data );
  
  mergesortImproved()=default;
  
  
  template<class Comparable>
  void beginSorting(std::vector<Comparable> &data);


private:
  static const unsigned short INSERTION_SORT_THRESHOLD = 7;
//  string fileName;
  template<class Comparable>
  void inPlaceMerge(std::vector<Comparable> &data, const int &first, const int &mid, const int &last);
  
  template<class Comparable>
  void insertionSort(std::vector<Comparable> &data, const int &first, const int &last);
  
  template<class Comparable>
  void combineArrays(std::vector<Comparable> &data, const int &first, const int &mid, const int &last);
  
  template<class Comparable>
  void swap(std::vector<Comparable> &data, const int &low, const int &hi);
  
  template <class Comparable>
  void subArrayIndexing(std::vector<Comparable> &data, std::queue<std::stack<unsigned short>> &levelQueue);
  
  std::queue<unsigned short> nRemHandling(const unsigned short &n, const unsigned short &fakeN,
                                     unsigned short &nRem,unsigned short &remK, unsigned short &two_to_RemK);
  
  void levelQueueBuilder(unsigned short &k, unsigned short &two_raisedTo_k, std::queue<std::stack<unsigned short>> &levelQueue,
                         const unsigned short &first, const unsigned short &fakeN_last);
};
#endif //MSI_ASSIG4_MERGESORTIMPROVED_H
