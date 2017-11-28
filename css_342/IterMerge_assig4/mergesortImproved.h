//
// Created by R.Peters on 11/28/2017.
//

#ifndef ITERMERGE_ASSIG4_MERGESORTIMPROVED_H
#define ITERMERGE_ASSIG4_MERGESORTIMPROVED_H

#include <vector>
#include <iosfwd>
using namespace std;

template<class Comparable>
class mergesortImproved {
public:

    explicit mergesortImproved( vector<Comparable> &data );

private:

    int combineArrays(vector<Comparable> &data, int first, int last);

    void swap(vector<Comparable> &data, int low, int hi);
};
#endif //ITERMERGE_ASSIG4_MERGESORTIMPROVED_H
