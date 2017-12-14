//
// Created by R.Peters on 12/13/2017.
//

#include <iostream>
#include <sstream>
#include "ListyList.hpp"


using namespace std;
/**
 *
 */
ListyList::ListyList():head(nullptr),tail(nullptr), iter(nullptr),size(0) {
	head = tail;
}

/**
 *
 * @param head
 * @param tail
 */
ListyList::ListyList(ListyList::node *head = nullptr, ListyList::node *tail = nullptr) : head(head), tail(tail) {}

/**
 *
 * @param L
 */
ListyList::ListyList(ListyList *L) {
	this->iter = nullptr;
	this->head = L->head;
	this->tail = L->tail;
	this->size = L->size;
}

/**
 *
 */
ListyList::~ListyList() {
	this->clear();
	delete this->head;
	delete this->tail;
	delete this;
}
/**
 *
 */
void ListyList::clear() {
	while(head->next != tail){
		tail->next = head->next;
		head->next = head->next->next;
		delete tail->next;
		tail->next = nullptr;
	}
	tail->next = nullptr;
	head->next = nullptr;
	iter->next = nullptr;
	size = 0;
}

/**
 *
 * @param item
 * @return
 */
int ListyList::add(void *item) {
	// implicit in this exchange of pointers is that tail controls all aspects of appending to the end of the list.
	auto *tmp = new node();
	tmp->item = item;
	tmp->next = tail->next;
	tail->next = tail->next->next = tmp;
	++size;
	return 0;
}

/**
 *
 * @param pos
 * @param item
 * @return
 */
bool ListyList::insert(const int & pos, void *item) {
	if(invalidPos(pos))return false;
	int seekPos = 1;
	iter->next = head;
	while(seekPos < pos && iter->next->next != tail){
		iter->next = iter->next->next;
		++seekPos;
	}
	if(seekPos == pos){
		auto *tmp = new node();
		tmp->item = item;
		tmp->next = iter->next->next;
		iter->next->next = tmp;
		iter->next = nullptr;
	}else{
		iter->next = nullptr;
		return false;
	}
	return true;
}

/**
 *
 * @param pos
 * @param item
 */
void ListyList::replace(const int & pos, void *item) {
	if(invalidPos(pos))return;
	iter->item = item;
	for(int myPos = 0; myPos <= pos; ++myPos){
		if(iter->next == tail)break;
		iter->next = iter->next->next;
	}
	iter->swapItems(iter->next);
	delete iter->item;
	iter->item = nullptr;
}

/**
 *
 * @param pos
 * @return
 */
bool ListyList::remove(const int & pos) {
	if(invalidPos(pos))return false;
	int seekPos = 1;
	iter->next = head;
	while(seekPos < size && iter->next != tail) {
		iter->next = iter->next->next;
		++seekPos;
	}
	if(seekPos == pos){
		node *tmp = iter->next->next;
		iter->next->next = iter->next->next->next;
		delete tmp;
		iter->next = nullptr;
	}
	return false;
}

/**
 *
 * @return
 */
bool ListyList::isEmpty() {
	return size == 0;
}

/**
 *
 * @param pos
 * @return
 */
void *ListyList::getEntry(const int & pos) {
	if(invalidPos(pos))return nullptr;
	int seekPos = 0;
	iter->next = head;
	while(seekPos < pos && iter->next != tail){
		++seekPos;
		iter->next = iter->next->next;
	}
	if(seekPos == pos){
		void *ret = iter->next->item;
		iter->next = nullptr;
		return ret;
	}
	return nullptr;
}

/**
 *
 * @return
 */
int ListyList::getLength() {
	return size;
}

void ListyList::actualRecursion(ListyList::node *recurser) {
	if(recurser->next != tail)actualRecursion(recurser->next);
	recurser->next->next = recurser;
}

/**
 *
 * @return
 */
void ListyList::reverseRecursive() {
	if(size <2)return;
	if(head->next != tail)actualRecursion(head->next);
	iter->next = head->next;
	head->next = tail->next;
	tail->next = iter->next;
	iter->next = nullptr;
}

/**
 *
 * @return
 */
void ListyList::reverseIterative() {
	if(size < 2) return;
	if(size == 3){ // at only 3 elements, ->next->next calls can reach center of list to flip pointers around.
		tail->next->next = head->next->next;
		head->next->next = head->next;
		head->next = tail;
		iter->next = head->next;
		head->next = tail->next;
		tail->next = iter->next;
		iter->next = nullptr;
		return;
	}
	auto* iter2 = new node();
	tail->next = iter2->next = iter->next = head->next;
	head->next = head->next->next;
	iter->next = iter->next->next->next;
	while(iter->next != tail){
		head->next->next = iter2->next;
		iter2->next = head->next;
		head->next = iter->next;
		iter->next = iter->next->next;
	}
	head->next->next = iter2->next;
	tail->next->next = tail;
	iter->next = nullptr;
	iter2->next = nullptr;
	delete iter2;
}

bool ListyList::invalidPos(const int &pos) {
	return pos < 1 || pos > size;
}

/**
 *
 * @param os
 * @param L
 * @return
 */
std::ostream &operator<<(std::ostream &os, const ListyList *L) {
	os << L->makeString();
	return os;
}

/**
 *
 * @return
 */
string ListyList::makeString()const {
	if(size == 0)return "";
	stringstream ss;
	ss << "[ ";
	iter->next = head->next;
	if(head->next != tail) {
		ss << *static_cast<int*>(iter->next->item);
		iter->next = iter->next->next;
	}
	int pos = 0;
	while(iter->next != tail){
		if(++pos%10)ss << endl;
		ss << ", " << *static_cast<int*>(iter->next->item);
	}
	ss << "]";
	return ss.str();
}
