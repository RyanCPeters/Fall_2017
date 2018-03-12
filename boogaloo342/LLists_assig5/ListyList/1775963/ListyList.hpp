//
// Created by R.Peters on 12/13/2017.
//

#ifndef LISTYLIST_LISTYLIST_HPP
#define LISTYLIST_LISTYLIST_HPP

#include <iostream>
#include <sstream>
#include <memory>
#include <iomanip>

// bit of a faux pa to use the std namespace in header files... but I'm too tired to care;
using std::cout; using std::endl;

template <typename O>
class node{

public:
	O* item ;
	node<O> *next;
	
	/**
	 *
	 * @tparam O
	 */
	node():next(nullptr),item(nullptr){};
	

	
	/**
	 *
	 * @tparam O
	 * @param nd
	 * @param itm
	 */
	explicit node(node<O> &nd,O &itm):next(&nd),item(itm){};
	
	/**
	 *
	 * @tparam O
	 * @param itm
	 */
	explicit node(O* &itm):next(nullptr),item(itm){};
	
	/**
	 *
	 * @param rhsNode
	 * @return
	 */
	node<O>& operator=(const node<O> &rhsNode){
		item = rhsNode.item;
		next = rhsNode.next;
		return *this;
	}
	
	node<O>& operator=(const node<O> *rhsNode){
		item = rhsNode->item;
		next = rhsNode->next;
		return *this;
	}
	
//	node<O>& operator=(const void* shit){
//		item = shit;
//		*next = shit;
//		return *this;
//	}
	
	/**
	 *
	 * @tparam O
	 * @param rhs
	 * @return
	 */
	bool operator==(const node<O> &rhs)const{return this == &rhs;}
	

	
	/**
	 *
	 * @tparam O
	 * @param other
	 */
	void swapItems(node<O>* &other){
		O* tmp = (other->item);
		other->item = item;
		item = tmp;
	}
};



template <typename O>
class ListyList {
private:
	
	
	node<O> iter, tail, head;
	long int len;
	
	/**
	 *
	 * @param pos
	 * @return
	 */
	bool isInvalidPos(const int &pos){
		return pos < 0 || pos > len;
	}
	
	/**
	 *
	 * @tparam O
	 * @param nd
	 */
	void actualRecursion(node<O> &nd){
		if(nd.next != tail.next)actualRecursion(*(nd.next));
		nd.next->next = &nd;
	}




public:
	
	/**
	 *
	 * @tparam O
	 * @param L
	 */
	ListyList(ListyList &L) {
		head = (L.head);
		iter = (L.iter);
		tail = (L.tail);
		len = L.len;
		if(head.next == nullptr){
			tail.next = &head;
		}
	}

	
	/**
	 *
	 */
	ListyList():
					len(0),
					iter(),
					head(),
					tail(){
		
		tail.next = &head;
		
		cout << "ListyList initialized as an empty singly-linked List" << endl;
	}
	
	/**
	 *
	 */
	~ListyList() {
		clear();
		delete(&iter);
		delete(&head);
		delete(&tail);
		cout << "ListyList is cleared and all node pointers deleted " << endl;
	}
	
	/**
	 *
	 * @param item
	 */
	void add(O &item) {
		++len;
		O* oPtr = new int(item);
		// implicit in this exchange of pointers is that tail controls all aspects of appending to the end of the list.
		tail.next->next = new node<O>();
		tail.next = tail.next->next;
		tail.next->item = oPtr;
		oPtr = nullptr;
		delete[]oPtr;
	}
	
	void add(O* &itm){
		add(*itm);
	}
	
	void add(const O &itm){
		O* oPtr = new O(itm);
		add(*itm);
	}
	/**
	 *
	 * @param pos
	 * @param item
	 * @return
	 */
	bool insert(const int &pos, O &item){
		if(isInvalidPos(pos))return false;
		if(pos > 0 && pos < len) {
			int seekPos = 1;
			iter.next = head.next;
			while (seekPos < pos && iter.next != nullptr) {
				iter.next = iter.next->next;
				++seekPos;
			}
			if (seekPos == pos) {
				node<O> *tmp = new node<O>();
				tmp->next = iter.next->next;
				tmp->item = &item;
				iter.next->next = tmp;
				iter.next = nullptr;
				++len;
				tmp = nullptr;
				delete[]tmp;
				return true;
			}
		}else if(pos == len){
			iter.next = tail.next;
			node<O> *tmp = new node<O>();
			tmp->next = iter.next->next;
			tmp->item = &item;
			iter.next->next = tmp;
			tail.next = iter.next->next;
			iter.next = nullptr;
			++len;
			tmp = nullptr;
			delete[]tmp;
			return true;
			
		} else{
			node<O> *tmp = new node<O>();
			iter.next = &head;
			tmp->next = iter.next->next;
			tmp->item = &item;
			iter.next->next = tmp;
			iter.next = nullptr;
			++len;
			tmp = nullptr;
			delete[]tmp;
			return true;
		}
		iter.next = nullptr;
		return false;
	
	}
	/**
	 *
	 * @param pos
	 * @param itm
	 * @return
	 */
	bool insert(const int &pos, O* &itm){
		insert(pos,*itm);
	}
	
	/**
	 *
	 * @param pos
	 * @param itm
	 * @return
	 */
	bool insert(const int &pos, const O &itm){
		O* oPtr = new O(itm);
		insert(pos,*oPtr);
	}
	
	/**
	 *
	 * @param pos
	 * @param item
	 */
	void replace(const int &pos, O* &item){
		if(isInvalidPos(pos))return;
		if(pos == 0){
			head.next->item = item;
			return;
		}
		if(pos == len){
			tail.next->item = item;
			return;
		}
		int myPos = 0;
		iter.next = head.next;
		while(myPos < pos && iter.next != tail.next){
			iter.next = iter.next->next;
			++myPos;
		}
		if(myPos == pos)iter.next->item = item;
		iter.next= nullptr;
	}
	void replace(const int &pos, const O &itm){
		O* oPtr = new int(itm);
		replace(pos,oPtr);
		delete[]oPtr;
	}
	
	void replace(const int &pos, const O* itm){
		O* oPtr = new int(*itm);
		replace(pos,oPtr);
		delete[]oPtr;
	}
	/**
	 *
	 * @param pos
	 * @return
	 */
	bool remove(const int &pos){
		if(isInvalidPos(pos))return false;
		if(pos == len){
			iter.next = head.next;
			while(iter.next->next!=tail.next)iter.next = iter.next->next;
			tail.next = iter.next;
			delete[]iter.next->next;
			iter.next = nullptr;
			--len;
			return true;
		}
		int seekPos = 0;
		iter.next = &head;
		while(seekPos < pos && iter.next->next != tail.next) {
			iter.next = iter.next->next;
			++seekPos;
		}
		if(seekPos == pos){
			node<O>* del = iter.next->next;
			iter.next->next = iter.next->next->next;
			iter.next = nullptr;
			del->next = nullptr;
			delete[]del->item;
			delete(del->next);
			delete(del);
			--len;
			return true;
		}
		return false;
	}
	
	
	/**
	 *
	 */
	void clear() {
		while(head.next != tail.next){
			iter.next = head.next;
			head.next = head.next->next;
			delete(iter.next);
		}
		delete(tail.next);
		tail.next = &head;
		iter.next = head.next = nullptr;
		len = 0;
	}
	
	/**
	 *
	 * @return
	 */
	bool isEmpty() {
		return len == 0;
	}
	
	/**
	 *
	 * @param pos
	 * @return
	 */
	O* getEntry(const int &pos){
		if(isInvalidPos(pos))return nullptr;
		int seekPos = 0;
		iter.next = head.next;
		while(seekPos < pos && iter.next != tail.next){
			++seekPos;
			iter.next = iter.next->next;
		}
		if(seekPos == pos){
			O* ret = (iter.next)->item;
			iter.next = nullptr;
			return ret;
		}
		iter.next = nullptr;
		return nullptr;
	}
	
	/**
	 *
	 * @return
	 */
	long int size()const {
		return len;
	}
	
	/**
	 *
	 */
	void reverseRecursive(){
		if(len <2)return;
		if(head.next != tail.next)actualRecursion(*(head.next));
		iter.next = head.next;
		head.next = tail.next;
		tail.next = iter.next;
		iter.next = nullptr;
	}
	/**
	 *
	 */
	void reverseIterative() {
		if(len < 2) return;
		if(len == 3){ // at only 3 elements, ->next->next calls can reach center of list to flip pointers around.
			tail.next->next = head.next->next;
			head.next->next = head.next;
			head.next = tail.next;
			iter.next = head.next;
			head.next = tail.next;
			tail.next = iter.next;
			iter.next = nullptr;
			return;
		}
		node<O> iter2 = node<O>();
		tail.next->next = &tail;
		tail.next = iter2.next = iter.next = head.next;
		head.next = head.next->next;
		iter.next = iter.next->next->next;
		while(iter.next->next != &tail){
			head.next->next = iter2.next;
			iter2.next = head.next;
			head.next = iter.next;
			iter.next = iter.next->next;
		}
		head.next->next = iter2.next;
		iter2.next = head.next;
		head.next = iter.next;
		head.next->next = iter2.next;
		tail.next->next = nullptr;
		iter.next = nullptr;
	}
	
	/**
	 *
	 * @return
	 */
	int getLength() const {
		return len;
	}
	
	/**
	 *
	 * @return
	 */
	std::string makeString()const {
		if(head.next == nullptr)return "len: 0;\n[ ]";
		std::stringstream ss;
		ss << "len: " << size() << "\n[ ";
		node<O> tmp = iter;
		tmp.next = head.next;
		int pos = 1;
		while(tmp.next != tail.next){
			ss << std::setw(2) << *(tmp.next->item) <<  ", ";
			if(++pos%11 == 0)ss << "\n  " ;
			tmp.next = tmp.next->next;
		}
		
		ss << std::setw(2) << *tmp.next->item << " ]";
		return ss.str();
	}
	
};

/**
	 *
	 * @param os
	 * @param L
	 * @return
	 */
template <typename O>
std::ostream& operator<<(std::ostream &os, const ListyList<O> &L){
	os << L.makeString();
	return os;
}

#endif //LISTYLIST_LISTYLIST_HPP
