//
// Created by R.Peters on 11/20/2017.
//

#include <iostream>
#include "mergesortImproved.h"

using namespace std;

/**
 *
 * @param data
 */
<<<<<<< HEAD
template <class Comparable> // ToDo: implement template
mergesortImproved::mergesortImproved(vector<Comparable> &data) {
=======
//template <class Comparable> // ToDo: implement template
mergesortImproved::mergesortImproved(vector<int> &data) {
>>>>>>> 27c5e5597144fd8e102baf89faa18a91f0efe392
    /* setting control variables where:
     *  n = total number of elements in data
     *  two_k = the number of subsection in data after k divisions, expressed in math notation as (2)^k, and derived here using 1<<k
     *  k = number of divisions.
     */
    int n = data.size(), k = 0, two_k = 1<<k;
    while(n/two_k > 10 ) two_k = 1<<(++k);

    double twok = 1<<k;

    /* when k == 0, we will see that twok == 1; and when k == 0 we have finished combining sub-sections of the array*/
<<<<<<< HEAD
    while(k >= 0){
=======
    while(1 <= twok){
>>>>>>> 27c5e5597144fd8e102baf89faa18a91f0efe392

        auto shift = (n/twok);
        // correctlySorted tracks the number of sub-sections that return 1 from combineArrays method.
        int correctlySorted = 0;
        for(double i = 0; i  < n;) {
            int low = (long)i;
            i+=shift;
            int hi = (long)i;
            correctlySorted += combineArrays(data, low, hi);
        }
        // recall that 1<<k is the number of expected sub-sections for this level of k
        // so only proceed if correctlySorted == 1<<k
        if(correctlySorted == (1<<k)) {
            --k;
            twok = 1<<k;
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
<<<<<<< HEAD
template <class Comparable> // ToDo: implement template
int mergesortImproved::combineArrays(vector<Comparable> &data,int first, int last) {
    if(first >= last) return 0;
    if((last - first) == 1 )return 1;

    int a1 = first, a2 = (first + (last - first)/2), b1 = a2+1, b2 = last;

    vector<Comparable> d2; // ToDo: change to Comparable when implementing templates
=======
//template <class Comparable> // ToDo: implement template
int mergesortImproved::combineArrays(vector<int> &data,int first, int last) {
    if(first >= last) return 0;
    if((last - first) == 1 )return 1;

    int a1 = first, a2 = (first + (last - first)/2), b1 = a2+1, b2 = last,d2Pos = 0;

    vector<int> d2; // ToDo: change to Comparable when implementing templates
>>>>>>> 27c5e5597144fd8e102baf89faa18a91f0efe392

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
<<<<<<< HEAD
            // if smallest is not greater than i, then we have nothing to swap
=======
>>>>>>> 27c5e5597144fd8e102baf89faa18a91f0efe392
            if(smallest > i) swap(data,smallest,i);
        }// end of for i
        return 1;
    }// end of insertion block

<<<<<<< HEAD
=======


>>>>>>> 27c5e5597144fd8e102baf89faa18a91f0efe392
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
<<<<<<< HEAD
template <class Comparable> // ToDo: implement template
void mergesortImproved::swap(vector<Comparable> &data, int low, int hi) {
=======
//template <class Comparable> // ToDo: implement template
void mergesortImproved::swap(vector<int> &data, int low, int hi) {
>>>>>>> 27c5e5597144fd8e102baf89faa18a91f0efe392
    int tmp = data[low];
    data[low] = data[hi];
    data[hi] = tmp;
}



