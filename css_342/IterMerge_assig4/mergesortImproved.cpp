//
// Created by R.Peters on 11/20/2017.
//

#include <iostream>
#include <vector>

using namespace std;

#define TERMINATOR_SIGN(num) ~(num-1);

class mergesortImproved {
public:
    template<class Comparable>
    mergesortImproved( vector<Comparable> &data );

private:
    template<class Comparable>
    int combineArrays(vector<Comparable> &data, int first, int last);
    template<class Comparable>
    void swap(vector<Comparable> &data, int low, int hi);

};

/**
 *
 * @tparam Comparable Any data type that has a natural order that permits the use of equality opperators.
 * @param data
 */
template <class Comparable>
mergesortImproved::mergesortImproved(vector<Comparable> &data) {
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

        auto shift = n/((double)two_raisedTo_k),remainder = shift-(long)shift;
        int interval = (remainder > 0)? (int)(1/remainder): 0;



        // correctlySorted is used to track the number of sub-sections that return 1
        // from combineArrays method.
        int correctlySorted = 0;

        /* sorry for the jacked up looking for loop bellow... I decided to go with this
         * ugly structure in order to account for points in the iteration where subdivisions
         * of the data array would result in segments having fractional element counts. As per
         * the expression (n/(2)^k) = 'elements-per-subdivision.'
         *
         * To combat this problem, I've decided that when shift results in
         *
         *          This loop will use variable 'i' to update the low and hi bounds as
         *          we iterate through the data array.
         *
         *          Variable 'i' will grow in increments determined by the integer portion
         *          of the variable 'shift,' which is stored in the variable 'increment.'
         *
         *          The variable 'pass' is used to track how many loops we've done in this
         *          for loop. This loop count is used when we determine if it is time to
         *
         * @pre i < n
         * @pre pass must start at 0 in order to ensure that bounds fall in the right place.
         */
        for(int i = 0, increment = (long)shift, pass = 0; i < n; ++pass){
            int low = i;
            i += increment;
            if(interval > 0){
                i += (pass % interval == 0)*1;
            }
            int hi = i-1;

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

/** int mergesortImproved::combineArrays(vector<Comparable> &data,int first, int last)
 *
 * As the name implies, this function recombines our pointer-bounded subsections of the original array.
 * This function will inevitably have to create n/2 temporary holding arrays for the task of moving data points.
 *
 * @param data
 * @param first
 * @param last
 * @return
 */
template <class Comparable>
int mergesortImproved::combineArrays(vector<Comparable> &data,int first, int last) {
    if(first >= last) return 0;
    if((last - first) == 1 )return 1;

    int a1 = first, a2 = (first + (last - first)/2), b1 = a2+1, b2 = last;

    //// If this subsection of the array is longer than 10 elements, then we should use a sorting approach that is
    //// appropriate for larger data sets.
    if(last - first > 10) {
        // when the end of the left subsection is smaller than or equal to the start of the right subsection we can
        // conclude that the subsections are conveniently in order already.
        if (data[a2] <= data[b1])return 1;
        if (data[first] > data[last]) {
            int len = a2 - a1 + 1;
//            if (len > last - a2) swap(data, a2 - 1, a2);
            for (int i = a1; i < a2; ++i) {
                swap(data, i, i + len);
            }
            return 1;
        }
        int dataSize = data.size();
        int fromEnd = dataSize-a2-1;
        vector<Comparable> data2;
        data2.assign(data.begin()+a1,data.end()-(fromEnd));
        // d1 and d2 are the index pointers for data2
        int d1 = 0, d2 = data2.size(), masterIter = a1;
        Comparable dObj = data2[d1], bObj = data[b1];
        int complete = TERMINATOR_SIGN(dataSize);
        // ToDo: describe logic of this while loop
        while(masterIter <= b2){

            // if bObj == complete, then bObj is < 0, so dObj should never be <= bObj unless both are complete, in which case
            // we don't want it to succeed... hence the ^ operator (XOR)
            while(d1 <= d2 && dObj >= 0 && ((bObj == complete) ^ (dObj <= bObj))){
                data[masterIter++] = dObj;
                dObj = data2[++d1];
            }
            // if dObj == complete, then dObj is < 0, so bObj should never be <= dObj unless both are complete, in which case
            // we don't want it to succeed... hence the ^ operator (XOR)
            while( b1 <= b2 && bObj >= 0 && ((dObj == complete) ^ (bObj < dObj))){
                data[masterIter++] = bObj;
                bObj = data[++b1];
            }

            if(b1 > b2)bObj = complete;
            else if(masterIter == b1){
            	if(dObj != complete){
            		if(dObj <= bObj) {
            			Comparable tmp = data2[d1];
            			data2[d1] = data[b1];
            			data[b1] = tmp;
            		}
            	}
            }
            if(d1 > d2)dObj = complete;

        }// end of while loop
        return 1;

    }
        //// if sub-array is short, then use insertion sort.
    else {
        for (int i = first; i < last; ++i){
            auto smallest = i;
            for (int j = i+1; j <= last; ++j ){
                if (data[j] < data[smallest]){
                    smallest = j;
                }
            }// end of for j
            // if smallest is not greater than i, then we have nothing to swap
            if (smallest > i) swap(data,smallest,i);
        }// end of for i
        return 1; // this return is only accessed if we end up using insertion sort.
    }// end of insertion block





}// end of combineArrays(data,first,last) function

/**
 *
 * @param data
 * @param low
 * @param hi
 */
template <class Comparable>
void mergesortImproved::swap(vector<Comparable> &data, int low, int hi) {
    int tmp = data[low];
    data[low] = data[hi];
    data[hi] = tmp;
}



