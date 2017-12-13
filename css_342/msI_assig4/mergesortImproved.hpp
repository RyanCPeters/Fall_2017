//
// Created by R.Peters on 12/7/2017.
//

#ifndef MSI_ASSIG4_MERGESORTIMPROVED_H
#define MSI_ASSIG4_MERGESORTIMPROVED_H

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;
class mergesortImproved
{
public:
	
	/** template <class Comparable> mergesortImproved(vector<Comparable> &a)
 *
 * @tparam Comparable   This template reference is meant for use with a types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use a types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param a          The vector<Comparable> that is to be sorted
 */
	template <class Comparable>
	mergesortImproved(vector<Comparable> &a)
	{
		beginSort(a);
	}
	
	mergesortImproved()=default;
	
	/** template<class Comparable> void beginSorting(vector<Comparable> &a)
 *
 * Handles preparations for iterative-in-place Mergesort. Namely, the math needed for locating and saving index pointers into
 * queues and stacks that will later be used to emulate recursively subdeviding the unsorted collection before the much
 * simpler task of recombining the imaginary subdivisions.
 *
 * @tparam Comparable   This template reference is meant for use with a types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use a types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param a          The vector<Comparable> that is to be sorted
 */
	template<class Comparable>
	void beginSort(vector<Comparable> &a) {
		
		/* setting control variables where:
		 *
		 *                n = total number of elements in a
		 *
		 *  powOfTwo  = the number of subsections in a after k divisions,
		 *                    expressed in math notation as (2)^k, and derived here
		 *                    using powOfTwo <<= 1;
		 * n/powOfTwo = The number of elements per subsection
		 */
		unsigned int n = static_cast<unsigned short>(a.size()),powOfTwo = 1;
		/*
			This check is against threshold*2 because anything less than that will be handled in two sequential calls to
			insertionSort. This saves a small amount of time when sorting small collections.
			
			*/
		if (n < 2)return;
		if (n > INSERTION_SORT_THRESHOLD * 2) {
			
			
			
			vector<Comparable> b(n/2+1);
			/* the expression while(n > powOfTwo*2) amounts to saying while n > the next iteration of powOfTwo, then grow powOfTwo*/
			while (n >= powOfTwo * 2) powOfTwo <<= 1;
			vector<unsigned int> po2Rem;
			po2Rem.push_back( n%powOfTwo);
			
			/* here we are generating the corresponding remainder values for each of the powers of 2 that we will use in
			 * indexing our way through the a collection.
			 */
			for(unsigned int i = powOfTwo>>1, j = 1; i >= 4; i>>=1, ++j){
				if( i <= po2Rem.at(j-1))po2Rem.push_back(po2Rem.at(j-1) - i);
				else po2Rem.push_back(po2Rem.at(j-1));
			}
			
			unsigned int lastidx = 0;
			for (unsigned int firstPassIdx = 0; firstPassIdx+1 < n-1; firstPassIdx += 2) {
					combineArrays(a, b, firstPassIdx, firstPassIdx, firstPassIdx + 1, n);
				lastidx = firstPassIdx;
			} // end of for splitIdx loop
			combineArrays(a, b, lastidx, lastidx +1, n - 1, n);
			/*
			 * Here we begin the actual process of finding the index values used in sorting the collection.
			 */
			int pow = static_cast<unsigned int>(po2Rem.size()-1);
			for (unsigned int sPo2 = 1<<2, middleStep = sPo2>>1; pow >=0 ;--pow, sPo2 <<= 1, middleStep <<= 1) {
				/* For the sake of keeping the code limited to a more condensed and readable format,
				     the iterator in the following for loop will be named sPo2, which is short for
				     stepping-power-of-2.
				 */
				for (unsigned int splitIdx = 0; splitIdx+sPo2-1 < n; splitIdx += sPo2) {
					unsigned int low = splitIdx,mid = splitIdx + middleStep,hi = splitIdx+sPo2-1;
					if(hi >= (n-1)-po2Rem.at(pow)){
						combineArrays(a, b, low, mid, hi, n);
						// we need to merge the last section with this next section
//						unsigned int nextSmallerRemIdx = sPo2;
//						while( nextSmallerRemIdx > (n-1)-splitIdx)nextSmallerRemIdx >>=1;
						mid = hi+1, hi = n-1;
					}
					combineArrays(a, b, low, mid, hi, n);
				} // end of for splitIdx loop
			} // end of for sPo2 loop
			
		} else {
			insertionSort(a, 0, n - 1);
		}
	}
	
	/////////////////////////////////////////////////////
	//////////   end of public content ;)   /////////////
	/////////////////////////////////////////////////////

private:
	static const unsigned short INSERTION_SORT_THRESHOLD = 4;

/** template <class Comparable> int combineArrays(vector<Comparable> &a, const int &first, const int &mid, const int &last)
 *
 * As the name implies, this function recombines our pointer-bounded subsections of the original array.
 * This function will inevitably have to create n/2 temporary holding arrays for the task of moving a points.
 *
 * @tparam Comparable   This template reference is meant for use with a types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use a types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param a          The vector<Comparable> that is to be sorted
 *
 * @param first         the low-bound for the subsection of vector<Comparable> a that we are going to be sorting.
 *
 * @param mid           The index value that falls in the middle of first and last, used to subdevide the section we are
 *                      about to sort.
 *
 * @param last          The high-bound for the subsection of vector<Comparable> a that we are going to be sorting.
 */
	template <class Comparable>
	void combineArrays(vector<Comparable> &a, vector<Comparable> &b, const unsigned int &first, const unsigned int &mid,
		                   const unsigned int &last, const unsigned int &aSize)
	{
		if(first > last || first < 0 || last < 0) return;
		if(last == first )return;
		/* If this subsection of the array is longer than INSERTION_SORT_THRESHOLD elements, then we should use a sorting approach that is
		 * appropriate for larger a sets, in this case that is an iterative emulation of the mergesort algo.
		 */
		if(last - first <= INSERTION_SORT_THRESHOLD){
			return insertionSort(a,first, last);
		}// end of if(last-first <=INSERTION_SORT_THRESHOLD)  -- insertion block
		else{ // the subsection to sort is greater than INSERTION_SORT_THRESHOLD, we need a more efficient algorithm than  insertion.
			return inPlaceMerge(a, b, first, mid, last, aSize);
		}
	} // end of combineArrays function

/** template <class Comparable> int inPlaceMerge(vector<Comparable> &a, const int &first, const int &mid, const int &last)
 *
 * @tparam Comparable   This template reference is meant for use with a types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use a types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param a          The vector<Comparable> that is to be sorted
 *
 * @param first         the low-bound for the subsection of vector<Comparable> a that we are going to be sorting.
 *
 * @param mid           The index value that falls in the middle of first and last, used to subdevide the section we are
 *                      about to sort.
 *
 * @param last          The high-bound for the subsection of vector<Comparable> a that we are going to be sorting.
 */
	template <class Comparable>
	void inPlaceMerge(vector<Comparable> &a, vector<Comparable> &b, const unsigned int &first, const unsigned int &mid,
		                  const unsigned int &last, const unsigned int &aSize) {
		unsigned int backIter =  (mid < last)? mid: last-1;
		// when the end of the left subsection is smaller than or equal to the start of the right subsection we can
		// conclude that the subsections are conveniently in order already.
		if (a.at(backIter-1) <= a.at(backIter))return;
		if (a.at(first) > a.at(last) && mid != last) {
			unsigned int len =last - backIter + 1;
			for (unsigned int i = last; i < last - backIter - 1; --i) {
				this->swap(a, i, i + len);
			}
			return;
		}
		
		b.assign(a.rbegin()+(aSize-mid),a.rend()-first); // a.rbegin()+(distance from a.back() to mid), a.rend()-(distance from a.front() to first)
		unsigned int masterIter = first;
		
		// using the alternate array to hold the reverse ordered elements from first to mid, we now combine the two
		// sets of elements back into a knowing that so long as nothing new gets added some now, we will never overwrite
		// the elements at backIter's position and are thus safe to do a basic merge sort.
		while( masterIter <= last ){
			uint8_t mergeState = 0;
			if(!b.empty()) mergeState += 1;
			if(backIter <= last) mergeState += 10;
			if(mergeState == 11){// if true, then we need to compare the two a points
				if(b.back() <= a.at(backIter)) mergeState += 100;
			}
			switch(mergeState){
				case 10: // if cases 10 or 11 are true, then bObj has the next value
				case 11:
					a.at(masterIter) = a.at(backIter);
					++masterIter,++backIter;
					break;
				case 1:
				case 111:
					a.at(masterIter++) = b.back();
					b.pop_back();
					break;
				default:
					break;
			}
		}// end of while loop
		
	}

/** template <class Comparable> int insertionSort(vector<Comparable> &a, const int &first, const int &last)
 *
 * if sub-array is short, then use insertion sort.
 *
 * @tparam Comparable   This template reference is meant for use with a types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use a types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param a          The vector<Comparable> that is to be sorted
 *
 * @param first         the low-bound for the subsection of vector<Comparable> a that we are going to be sorting.
 *
 *
 * @param last           The high-bound for the subsection of vector<Comparable> a that we are going to be sorting.
 */
	template <class Comparable>
	void insertionSort(vector<Comparable> &a, const int &first, const int &last)
	{
		for (unsigned short  i = first; i < last; ++i){
			unsigned short  smallest = i;
			for (unsigned short  j = i+1; j <= last; ++j ) {
				smallest = (a[j] >= 0 && a[j] < a[smallest])? j : smallest ;
			}
			if(smallest > i) {
				this->swap(a,smallest,i);
			}
		}// end of for i
	}// end of combineArrays(a,first,last) function

/** template <class Comparable> void swap(vector<Comparable> &a, const int &low, const int &hi)
 *
 * @tparam Comparable   This template reference is meant for use with a types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use a types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param a          The vector<Comparable> that is to be sorted
 *
 * @param low           The lower indexed value from the vector<Comparable> a that we are going to be swapping.
 *
 * @param hi            the higher indexed value from the vector<Comparable> a that we are going to be swapping.
 */
	template <class Comparable>
	void swap(vector<Comparable> &a, const int &low, const int &hi)
	{
		Comparable tmp = a.at(low);
		a.at(low) = a.at(hi);
		a.at(hi) = tmp;
	}
};
#endif //MSI_ASSIG4_MERGESORTIMPROVED_H
