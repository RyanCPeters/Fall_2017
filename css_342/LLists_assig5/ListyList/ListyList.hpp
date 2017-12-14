//
// Created by R.Peters on 12/13/2017.
//

#ifndef LISTYLIST_LISTYLIST_HPP
#define LISTYLIST_LISTYLIST_HPP

#include <iosfwd>
#include <wsman.h>

class ListyList {
private:
	struct node{
		void* item;
		node* next;
		node* swapItems(node *other){
			void *tmpPtr = this->item;
			this->item = other->item;
			other->item = tmpPtr;
			return other;
		}
		
	};
	node *head, *tail, *iter;
	unsigned int size;
	bool invalidPos(const int &pos);
	void actualRecursion(node *head);
public:
	ListyList(ListyList *L);
	
	ListyList(node *head, node *tail);
	
	ListyList();
	
	~ListyList();
	int add(void *item);
	bool insert(const int &pos, void* item);
	void replace(const int & pos, void* item);
	bool remove(const int & pos);
	void clear();
	bool isEmpty();
	void* getEntry(const int & pos);
	int getLength();
	void reverseRecursive();
	void reverseIterative();
	friend std::ostream& operator<<(std::ostream &os, const ListyList *L);
	std::string makeString()const;
};


#endif //LISTYLIST_LISTYLIST_HPP
