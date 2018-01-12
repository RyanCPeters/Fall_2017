#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

#include "ListyList.hpp"

using namespace std;
void initArray(ListyList<int> *L, const unsigned int &randMax)
{
	for(int i = 0; i < randMax; ++i)L->add(i);
	
}

int main() { //ToDo: build the driver implementation.
	const int maxSize = 10000;
	ListyList<int>* vListy;
	double time;
	cout << "Empty list initialization demo:" << endl;
	auto start = chrono::high_resolution_clock::now();
	vListy = new ListyList<int>();
	auto stop = chrono::high_resolution_clock::now();
//	cout << *vListy << endl;
	time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
	cout << "operation took " << time <<  " microseconds" << endl;
	
	cout << endl << "test#1:\n\tPopulating List demo:" << endl;
	start = chrono::high_resolution_clock::now();
	initArray(vListy,maxSize);
	stop = chrono::high_resolution_clock::now();
//	cout << *vListy << endl;
	time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
	cout << "operation took " << time << " microseconds" << endl;
	
	
	cout << endl << "test#2:\n\tClearing the list demo:" << endl;
	start = chrono::high_resolution_clock::now();
	vListy->clear();
	stop = chrono::high_resolution_clock::now();
//	cout << *vListy << endl;
	time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
	cout << "operation took " << time << " microseconds" << endl;
	
	
	cout << endl << "test#3:\n\tisEmpty() demo:" << endl;
	cout << ((vListy->isEmpty())?"true":"false") << endl;
	start = chrono::high_resolution_clock::now();
	vListy->isEmpty();
	stop = chrono::high_resolution_clock::now();
	time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
	cout << "operation took " << time <<  " microseconds" << endl;
	
	
	initArray(vListy,maxSize);
	cout << endl << "Gonna repopulate List real quick..." << endl //<< *vListy << endl
       << endl << "And now we test isEmpty a second time to validate that it works"
			 << endl << ((vListy->isEmpty())?"true":"false") << endl
	     << endl << "test#4:\n\tIterative Reversal demo:" << endl;
	start = chrono::high_resolution_clock::now();
	vListy->reverseIterative();
	stop = chrono::high_resolution_clock::now();
//	cout << *vListy << endl;
	time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
	cout << "operation took " << time <<  " microseconds" << endl;
	
	
	cout << endl << "test#5:\n\tRecursive Reversal demo:" << endl;
	start = chrono::high_resolution_clock::now();
	vListy->reverseRecursive();
	stop = chrono::high_resolution_clock::now();
//	cout << *vListy << endl;
	time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
	cout << "operation took " << time <<  " microseconds" << endl;
	vListy->clear();
	initArray(vListy,maxSize);
	
	
	cout << endl << "test#6:\n\tInserting the value 99 at 0,3,5,9,and size indices"
	             << endl << "Starting out we have size = " << vListy->size() << endl;
	vListy->insert(0,99);
	vListy->insert(3,99);
//	cout << *vListy << endl;
	vListy->insert(5,99);
	vListy->insert(9,99);
//	cout << *vListy << endl;
	vListy->insert((vListy->size()),99);
//	cout << *vListy << endl;
	
	
	cout << endl << "test#7:\n\tRemove demo: we'll try to remove all of the 99's" << endl;
	cout << "remove from end position: " << vListy->remove(vListy->size()) << endl;
//	cout << *vListy << endl;
	cout << "remove from position 9: " << vListy->remove(9) << endl;
	cout << "remove from position 5: " << vListy->remove(5) << endl;
//	cout << *vListy << endl;
	cout << "remove from position 3: " <<vListy->remove(3)<< endl;
	cout << "remove from position 0: " <<vListy->remove(0)<< endl;
//	cout << *vListy << endl;
//	vListy->remove(9);
//	vListy->remove(5);
//	vListy->remove(3);
//	vListy->remove(0);
	
	int negOne = -1;
	cout << endl << "test#8\n\tReplace demo: attempt to replace the values at the first, middle and last nodes with -1:"
	             << endl;
	vListy->replace(0,negOne );
//	cout << *vListy << endl;
	vListy->replace(vListy->size()/2,negOne);
//	cout << *vListy << endl;
	vListy->replace(vListy->size(),negOne);
//	cout << *vListy << endl;
	
	cout <<endl<<endl<< "Thus concludes the linked list demonstration driver." << endl;
	
	delete vListy;
	
	return 0;
}