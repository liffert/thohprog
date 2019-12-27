#pragma once
#include <fstream>
#include <string>
#include "Iterator.h"
template <class T>
class List {

	struct ListNode {
		T data;
		ListNode* next;
		ListNode() {
			next = NULL;
		}
		ListNode(T dat) {
			data = dat;
		}
		void Print() {
			std::cout << data;
		}
	};

public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List();
	~List();

	//methods
	iterator begin();//Returns an iterator addressing the first element 
	iterator end();//Returns an iterator that addresses the location 
   //succeeding the last element


	void clear();//Erases all the elements of a list.
	bool empty();//Tests if a list is empty.

	iterator find(const node_type& val);//Returns an iterator to the 
// first element in a list that 
//match a specified value.
	iterator find_b(const node_type& val);

	void pop_front();//Deletes the element at the beginning of a list.

	void push_front(const node_type val);//Adds an element to the beginning 
  //of a list.
	void remove(const node_type val);//Erases first element in a list that 
   //match a specified value.


	int size();//Returns the number of elements in a list.

	void splice(iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
// position of the argument list.
	void	Print();//Dumps list into the screen

	void load(const std::string name);
	node_type set(const std::string line);
	void newIter();
private:
	node_type* head;
	iterator* first, * last;
	int len;
};

template<class T>
inline List<T>::List() {
	first = NULL;
	head = NULL;
	last = NULL;
	len = 0;
}

template<class T>
List<T>::~List() {//rewrite
	clear();
	delete head;
	delete first;
	delete last;
}
template<class T>
typename List<T>::iterator List<T>::begin() {
	if (first != NULL) {
		return *first;
	}
	return NULL;
}

template<class T>
typename List<T>::iterator List<T>::end() {
	return *last;
}

template<class T>
inline void List<T>::Print() {
	node_type* temp = head;
	while (temp != NULL) {
		temp->Print();
		temp = temp->next;
	}
}
template<class T>

inline void List<T>::load(const std::string name) {
	std::ifstream file(name);
	if (file.is_open()) {
		std::string line;
		while (!file.eof()) {
			std::getline(file, line);
			push_front(set(line));
		}
	}
}

template<class T>
typename List<T>::node_type List<T>::set(const std::string line) {
	T temp(line);
	return temp;
}

template<class T>
inline void List<T>::newIter() {
	delete first;
	delete last;
	first = new iterator(head);
	node_type* temp = head;
	while (temp != NULL) {
		temp = temp->next;
	}
	last = new iterator(temp);
}

template<class T>
inline void List<T>::clear() {
	while (head != NULL) {
		pop_front();
	}
}

template<class T>
bool List<T>::empty() {
	if(len == 0){
		return true;
	}
	return false;
}

template<typename T>
typename List<T>::iterator List<T>::find(const node_type& val) {
	node_type* temp = head;
	while (temp != NULL) {
		if (temp->data == val.data) {
			return temp;
		}
		temp = temp->next;
	}
	return temp;
}

template<typename T>
typename List<T>::iterator List<T>::find_b(const node_type& val) {
	node_type* temp = head;
	node_type* pointer = head;

	while (temp != NULL) {
		if (temp->data == val.data) {
			return pointer;
		}
		pointer = temp;
		temp = temp->next;
	}
	return pointer;
}

template<class T>
inline void List<T>::pop_front() {
	if (head != NULL) {
		remove(head->data);
	}
}

template<class T>
inline void List<T>::push_front(const node_type val) {
	node_type* temp = new node_type(val.data);
	if (head == NULL) {
		head = temp;
		head->next = NULL;
		len = 1;
	}
	else {
		temp->next = head;
		head = temp;
		len++;
	}
	newIter();
}

template<class T>
inline void List<T>::remove(const node_type val) {
	iterator it = find(val);
	iterator it_b = find_b(val);
	node_type* temp = &(*it);
	node_type* temp_b = &(*it_b);
	if (it == it_b) {
		head = temp->next;
		delete temp;
		len--;
	}
	else {
		temp_b->next = temp->next;
		delete temp;
		len--;
	}
	newIter();
}

template<class T>
inline int List<T>::size() {
	return len;
}

template<class T>
inline void List<T>::splice(iterator _Where, List<T>& _Right) {
	if (_Where == NULL) {
		exit(1);
	}
	node_type temp = (*_Where).data;
	this->remove((*_Where).data);
	_Right.push_front(temp);
}
