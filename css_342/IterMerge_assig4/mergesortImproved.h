//
// Created by R.Peters on 11/28/2017.
//

#ifndef ITERMERGE_ASSIG4_MERGESORTIMPROVED_H
#define ITERMERGE_ASSIG4_MERGESORTIMPROVED_H

#include <vector>
#include <iosfwd>
using namespace std;


class mergesortImproved {
public:
    template<class Comparable>
    mergesortImproved( vector<Comparable> &data );

private:
    void sort();
    template<class Comparable>
    int combineArrays(vector<Comparable> &data, int first, int last);
    template<class Comparable>
    void swap(vector<Comparable> &data, int low, int hi);

};
#endif //ITERMERGE_ASSIG4_MERGESORTIMPROVED_H
