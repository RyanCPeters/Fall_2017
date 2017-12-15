#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "ListyList.hpp"

using namespace std;

ListyList* initArray(ListyList *L, const unsigned int &randMax)
{
	vector<int> array(randMax);
	for(unsigned int i = 0; i<randMax;++i)array.at(i) = i;
//	shuffle(array.begin(), array.end(), default_random_engine(1));
	cout << "order of elements in L will be: " << endl;
	for(auto &elem: array){
		L->add(&elem);
		cout << elem << " ";
	}
	cout << endl;
	
	return L;
	
}

int main() { //ToDo: build the driver implementation.
	auto *L = new ListyList();
	
	initArray(L,20);
	
	
	L->clear();
	delete L;
	return 0;
}