//
// Created by R.Peters on 11/28/2017.
//

#ifndef ITERMERGE_ASSIG4_MERGESORTIMPROVED_H
#define ITERMERGE_ASSIG4_MERGESORTIMPROVED_H

#include <vector>
#include <iosfwd>
using namespace std;

//template<class int>
class mergesortImproved {
public:
//    template <class int>
    explicit mergesortImproved( vector<int> &data );

private:
    int combineArrays(vector<int> &data,int first, int last);
    void swap(vector<int> &data,int low, int hi);
};
#endif //ITERMERGE_ASSIG4_MERGESORTIMPROVED_H
