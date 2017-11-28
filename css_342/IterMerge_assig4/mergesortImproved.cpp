//
// Created by R.Peters on 11/20/2017.
//

#include <iostream>
#include "mergesortImproved.h"

#define TRUNCATE_TO_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))
using namespace std;


//template<class int>
mergesortImproved::mergesortImproved(vector<int> &data) {
    /* setting control variables where:
     *  n = total number of elements in data
     *  two_k = the number of subsection in data after k divisions, expressed in math notation as (2)^k, and derived here using 1<<k
     *  k = number of divisions.
     *  seg = the length of each segment as derived from n/(2^k)
     */
    int n = data.size(), k = 0, two_k = 1<<k;
    double seg = n, segPos = 0;
    while(n>two_k ){
        cout << two_k;
        two_k = 1<<(++k);
    }
    while(k >= 0){
        double shift = n/(1<<k);
        for(double i = 0; i  <= n; i+=shift) combineArrays(data,TRUNCATE_TO_INT(i),TRUNCATE_TO_INT((i+shift-1)));
        --k;
    }
}

/**
 * The only reasonable way to perform an in place merge of two large arrays is by the quicksort method, and for any
 * sub-array that is less than 10 elements long, insertion sort.
 * @tparam int Any class type that has a natural order
 * @param first
 * @param last
 */
//template<class int>
void mergesortImproved::combineArrays(vector<int> &data,int first, int last) {
    if(first >= last) return;
    if((last - first) == 1 )return;

    // if sub-array is short, then use insertion sort.
    if(last - first < 10){
        for(int i = first; i < last; ++i){
            for(int j = i; j < last; ++j ){
                if(data[j] < data[i]){
                    int tmp = data[i];
                    data[i] = data[j];
                    data[j] = tmp;
                }
            }// end of for j
        }// end of for i
    }// end of insertion block
    int a1 = first, piv = first + (last - first)/2, b2 = last;

    if(data[piv] <= data[piv+1])return;
    if(data[piv] > data[last]){
        int len = piv - first;
        int tmp = data[piv-1];
        data[piv-1] = data[piv];
        data[piv] = tmp;
        for(int i = first; i < piv; ++i){
            tmp = data[i];
            data[i] = data[i+len];
            data[i+len] = tmp;
        }
    }

    while(a1 < b2){
        while(data[a1] <= data[piv])++a1;
        while(data[b2] > data[piv])--b2;
        if(a1 < b2){
            int tmp = data[a1];
            data[a1] = data[b2];
            data[b2] = data[tmp];
        }else if(a1 == b2){
            int tmp = data[piv];
            data[piv] = data[b2];
            data[b2] = data[tmp];
        }
    }


}



