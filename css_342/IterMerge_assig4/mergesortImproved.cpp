//
// Created by R.Peters on 11/20/2017.
//

#include <iostream>
#include "mergesortImproved.h"

using namespace std;

/**
 *
 * @tparam Comparable Any data type that has a natural order that permits the use of equality opperators.
 * @param data
 */
template <class Comparable>
mergesortImproved<Comparable>::mergesortImproved(vector<Comparable> &data) {
    /* setting control variables where:
     *
     *                n = total number of elements in data
     *
     *  two_raisedTo_k  = the number of subsections in data after k divisions,
     *                    expressed in math notation as (2)^k, and derived here
     *                    using 1<<k.
     *
     *                k = number of divisions.
     *
     * ~~~ The number of elements per subsection is derived from n/two_raisedTo_k ~~~
     */
    int n = data.size(), k = 0, two_raisedTo_k = 1<<k;

    // while the number of elements per subsection is >= 10, increment k and
    // update two_raisedTo_k
    while(n/two_raisedTo_k >= 10 ) two_raisedTo_k = 1<<(++k);


    /* k == 0 we have nearly finished combining sub-sections of the array, k == 0 is the final level of recombination*/
    while(k >= 0){

        auto shift = n/((double)two_raisedTo_k);
        // correctlySorted is used to track the number of sub-sections that return 1
        // from combineArrays method.
        int correctlySorted = 0;
        for(double i = 0; i  < n;) {
            int low = (long)i;
            i+=shift;
            int hi = (long)i;
            correctlySorted += combineArrays(data, low, hi);
        }
        // recall that 1<<k is the number of expected sub-sections for this level of k
        // so only proceed if correctlySorted == 1<<k
        if(correctlySorted == two_raisedTo_k) {
            --k;
            two_raisedTo_k = 1<<k;
        }
    }
}

/**
 *
 * @param data
 * @param first
 * @param last
 * @return
 */
template <class Comparable>
int mergesortImproved<Comparable>::combineArrays(vector<Comparable> &data,int first, int last) {
    if(first >= last) return 0;
    if((last - first) == 1 )return 1;

    int a1 = first, a2 = (first + (last - first)/2), b1 = a2+1, b2 = last;

    vector<Comparable> d2;
    if(data[a2] <= data[b1])return 1;
    if(data[first] > data[last]){
        int len = a2 - a1 +1;
        if(len > last - a2) swap(data,a2-1,a2);
        for(int i = a1; i < a2; ++i){
            swap(data,i,i+len);
        }
        return 1;
    }

    // if sub-array is short, then use insertion sort.
    if(last - first < 10){
        for(int i = first; i < last; ++i){
            int smallest = i;
            for(int j = i+1; j < last; ++j ){
                if(data[j] < data[smallest])smallest = j;
            }// end of for j
            // if smallest is not greater than i, then we have nothing to swap
            if(smallest > i) swap(data,smallest,i);
        }// end of for i
        return 1;
    }// end of insertion block


    d2.assign(data.begin()+a1,data.end()-(data.size()-a2));
    int frontD2 = 0, backD2 = a2-a1;
    while((frontD2 <= backD2 || b1 <=b2) && a1<=a2){
        if(d2[frontD2] <= data[b1]){
            if(frontD2 < backD2)data[a1++] = d2[frontD2++];
        }
        if(d2[frontD2] > data[b1]) {
            data[a1++] = data[b1++];
        }
    }// end of while loop


}// end of combineArrays(data,first,last) function

/**
 *
 * @param data
 * @param low
 * @param hi
 */
template <class Comparable>
void mergesortImproved<Comparable>::swap(vector<Comparable> &data, int low, int hi) {
    int tmp = data[low];
    data[low] = data[hi];
    data[hi] = tmp;
}



