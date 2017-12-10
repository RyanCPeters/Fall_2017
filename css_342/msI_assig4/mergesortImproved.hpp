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
	
	/** template <class Comparable> mergesortImproved(vector<Comparable> &data)
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param data          The vector<Comparable> that is to be sorted
 */
	template <class Comparable>
	mergesortImproved(vector<Comparable> &data)
	{
		beginSorting(data);
	}
	
	mergesortImproved()=default;
	
	template<class Comparable>
	void betterBeginning(vector<Comparable> &data){
		
		unsigned short n = static_cast<unsigned short>(data.size()), powOfTwo = 1;
		
		if (n < 2)return;
		if (n > INSERTION_SORT_THRESHOLD * 2) {
			unsigned int idxIter = 0, incrementer = 2,step = 0;
			while(incrementer < n) {
				
				while (idxIter < n-1) {
					unsigned int hi = (idxIter+incrementer<n)? idxIter+incrementer : n-1;
					combineArrays(data,idxIter,idxIter+step,hi-1);
					idxIter = hi;
					if(n-1 < incrementer+idxIter)idxIter = n-1;
				}
				incrementer <<= 1;
				while (idxIter >0) {
					unsigned int hi = (idxIter-incrementer>0)? idxIter-incrementer :0;
					combineArrays(data,idxIter,idxIter+step,hi+1);
					idxIter = hi;
					if( 0 > idxIter-incrementer)idxIter = 0;
				}
				incrementer <<= 1;
			}
			
			
			
		} else {
			insertionSort(data, 0, n - 1);
		}
	}
	
/** template<class Comparable> void beginSorting(vector<Comparable> &data)
 *
 * Handles preparations for iterative-in-place Mergesort. Namely, the math needed for locating and saving index pointers into
 * queues and stacks that will later be used to emulate recursively subdeviding the unsorted collection before the much
 * simpler task of recombining the imaginary subdivisions.
 *
 * @tparam Comparable   This template reference is meant for use with data types that possess natural ordering.
 *                      Although there are no assert restrictions in place to ensure you only use data types with natural
 *                      ordering, the problem should become quickly apparant if the programmer fails to respect this
 *                      requirement.
 *
 * @param data          The vector<Comparable> that is to be sorted
 */
	template<class Comparable>
	void beginSorting(vector<Comparable> &data) {
		
		/* setting control variables where:
		 *
		 *                n = total number of elements in data
		 *
		 *  powOfTwo  = the number of subsections in data after k divisions,
		 *                    expressed in math notation as (2)^k, and derived here
		 *                    using powOfTwo <<= 1;
		 * n/powOfTwo = The number of elements per subsection
		 */
		unsigned short n = static_cast<unsigned short>(data.size()), /*k = 1,*/ powOfTwo = 1;/* static_cast<unsigned short>( 1<<(k-1));*/
		queue<stack<stack<unsigned int>>> levelQueue;
		/*
			This check is against threshold*2 because anything less than that will be handled in two sequential calls to
			insertionSort. This saves a small amount of time when sorting small collections.
			
			*/
		if (n < 2)return;
		if (n > INSERTION_SORT_THRESHOLD * 2) {
			
			/* the expression while(n > powOfTwo*2) amounts to saying while n > the next iteration of powOfTwo, then grow powOfTwo*/
			while (n >= powOfTwo * 2) powOfTwo <<= 1;
		
			vector<unsigned int> powOfTwoVect;
			for (unsigned int thePowsOfTwo = powOfTwo; ; thePowsOfTwo >>= 1) {
				powOfTwoVect.push_back(thePowsOfTwo);
				if (thePowsOfTwo <= 4 && powOfTwoVect.size() >=3)break;
			}
			bool nIsPowOf2 = false;
			unsigned int upperBound = powOfTwo, lowerBound = 0;
			stack<unsigned int> recordedBounds;
			recordedBounds.push(0);
			unsigned int myLogicSucksMid = 0, myLogicSucksHi = 0;
			
			for (unsigned int pow = 0; pow < powOfTwoVect.size();++pow) {
				if((n == powOfTwo)+nIsPowOf2 > 1)break;
				nIsPowOf2 = (n == powOfTwo && n == powOfTwoVect[pow]);
				if (upperBound != powOfTwoVect[pow]){
					if(upperBound + powOfTwoVect[pow] <= n)upperBound += powOfTwoVect[pow];
					else continue;
				}
				if(upperBound > n){
					upperBound = n;
					break;
				}
				/* For the sake of keeping the code limited to a more condensed and readable format, the iterator in the following
						 for loop will be named sPo2, which is short for sub-power-of-2.
						 
					 sPo2 will iterate from 2 to pow, where pow is the current power of 2 we are using to define boundaries with.
				*/
				for (unsigned int sPo2 = 2, step = 1; sPo2 <= powOfTwoVect[pow]; sPo2 <<= 1, step <<= 1) {
					stack<stack<unsigned int>> singleLevelStack;
					
					for (unsigned int splitIdx = lowerBound; splitIdx < upperBound; splitIdx += sPo2) {
						stack<unsigned int> subLevelSections;
						subLevelSections.push(splitIdx), subLevelSections.push(splitIdx + step);
						if (step > 1) {
							if(splitIdx + sPo2 - 1 == n-2)subLevelSections.push(splitIdx + sPo2);
							else subLevelSections.push(splitIdx + sPo2 - 1);
						}else if(splitIdx + sPo2 - 1 == n-2)subLevelSections.push(splitIdx + sPo2);
						singleLevelStack.push(subLevelSections);
						myLogicSucksMid = splitIdx+step, myLogicSucksHi = splitIdx+sPo2-1;
					} // end of for splitIdx loop
					
					levelQueue.push(singleLevelStack);
				} // end of for sPo2 loop
				recordedBounds.push(lowerBound);
				lowerBound = upperBound;
				
			}
				
			
				subArrayIndexing(data,levelQueue);
			} else {
				insertionSort(data, 0, n - 1);
			}
		}
	
	
	/////////////////////////////////////////////////////
	//////////   end of public content ;)   /////////////
	/////////////////////////////////////////////////////

private:
	static const unsigned short INSERTION_SORT_THRESHOLD = 7;
	
	/**
	 * This function was copied from https://stackoverflow.com/a/301338/7412747
	 * @tparam T
	 */
	template<class Comparable>
	struct is_pointer { static const bool value = false; };
	
	/**
	 * This function was copied from https://stackoverflow.com/a/301338/7412747
	 * @tparam T
	 */
	template<class Comparable>
	struct is_pointer<Comparable*> { static const bool value = true; };



/** template <class Comparable> int combineArrays(vector<Comparable> &data, const int &first, const int &mid, const int &last)
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
	void combineArrays(vector<Comparable> &data, const int &first, const int &mid, const int &last)
	{
		if(first > last || first < 0 || last < 0) return;
		if(last == first )return;
		/* If this subsection of the array is longer than INSERTION_SORT_THRESHOLD elements, then we should use a sorting approach that is
		 * appropriate for larger data sets, in this case that is an iterative emulation of the mergesort algo.
		 */
		if(last - first <= INSERTION_SORT_THRESHOLD){
			return insertionSort(data,first, last);
		}// end of if(last-first <=INSERTION_SORT_THRESHOLD)  -- insertion block
		else{ // the subsection to sort is greater than INSERTION_SORT_THRESHOLD, we need a more efficient algorithm than  insertion.
			return inPlaceMerge(data,first,mid,last);
		}
	} // end of combineArrays function

/** template <class Comparable> int inPlaceMerge(vector<Comparable> &data, const int &first, const int &mid, const int &last)
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
	void inPlaceMerge(vector<Comparable> &data, const unsigned short &first, const unsigned short &mid, const unsigned short &last) {
		unsigned short backIter =  mid;
		// when the end of the left subsection is smaller than or equal to the start of the right subsection we can
		// conclude that the subsections are conveniently in order already.
		if (data[backIter - 1] <= data[backIter])return;
		if (data[first] > data[last] && mid != last) {
			unsigned short len = static_cast<unsigned short>(last - backIter + 1);
			for (unsigned short i = last; i > last - backIter - 1; --i) {
				this->swap(data, i, i + len);
			}
			return;
		}
		int dataSize = static_cast<int>(data.size());
		vector<Comparable> data2;
		data2.assign(data.rbegin()+(dataSize-backIter),data.rend()-first);
		unsigned short masterIter = first;
		// ToDo: describe logic of this while loop
		while( masterIter <= last ){
			uint8_t mergeState = 0;
			
			if(!data2.empty()) mergeState += 1;
			if(backIter <= last) mergeState += 10;
			if(mergeState == 11){// if true, then we need to compare the two data points
				if(data2.back() <= data[backIter]) mergeState += 100;
			}
			switch(mergeState){
				case 10: // if cases 10 or 11 are true, then bObj has the next value
				case 11:
					data[masterIter++] = data[backIter++];
					break;
				case 1:
				case 111:
					data[masterIter++] = data2.back(), data2.pop_back();
					break;
				default:
					break;
			}
		}// end of while loop
		
	}

/** template <class Comparable> int insertionSort(vector<Comparable> &data, const int &first, const int &last)
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
	void insertionSort(vector<Comparable> &data, const int &first, const int &last)
	{
		for (unsigned short  i = first; i < last; ++i){
			unsigned short  smallest = i;
			for (unsigned short  j = i+1; j <= last; ++j ) {
				smallest = (data[j] >= 0 && data[j] < data[smallest])? j : smallest ;
			}
			if(smallest > i) {
				this->swap(data,smallest,i);
			}
		}// end of for i
	}// end of combineArrays(data,first,last) function

/** template <class Comparable> void swap(vector<Comparable> &data, const int &low, const int &hi)
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
	void swap(vector<Comparable> &data, const int &low, const int &hi)
	{
		Comparable tmp = data.at(low);
		data[low] = data.at(hi);
		data[hi] = tmp;
	}


/**
 *
 * @tparam Comparable
 * @param data
 * @param levelQueue
 */
	template <class Comparable>
	void subArrayIndexing(vector<Comparable> &data, queue<stack<stack<unsigned int>>> &levelQueue)
	{
		while (!levelQueue.empty()) {
			unsigned int low = 0, mid = 0, hi = 0;
			stack<stack<unsigned int>> level = levelQueue.front();
			levelQueue.pop();
			
			while(!level.empty()){
				stack<unsigned int> sub = level.top();
				level.pop();
				if(sub.size() > 2){
					hi = sub.top();
					sub.pop();
					mid = sub.top();
					sub.pop();
					low = sub.top();
					sub.pop();
				}else{
					hi = sub.top();
					sub.pop();
					low = sub.top();
					sub.pop();
					mid = low;
				}
				
				this->combineArrays(data, low, mid, hi);
			}
			
			
		}
	
	}

};
#endif //MSI_ASSIG4_MERGESORTIMPROVED_H
