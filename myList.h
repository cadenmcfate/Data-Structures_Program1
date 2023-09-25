//myList.h
//defines the linked list template class for program 1
//Caden McFate
//Programming assignment 1
//COSC 2030
#ifndef MYLIST_
#define MYLIST_
#include "node.h"
#include <iostream>
using std::cout;
using std::endl;
template <class T>
class myList {
private:
	node<T>* head;
	int size;
public:
	myList() { head = nullptr; size = 0; } //constructor
	~myList(); //destructor
	void insert(T item); //insert front
	T front();
	int find(T item); //returns the amount of string.compare(string) operations it took to find 'item'. Positive if found, negative if not found.
	void sort(int max); //sorts the list by increasing length.
	void display(); //prints the list
	void remove(); //remove front
	bool isEmpty() { return size == 0;  }
	int getSize() { return size; }
};

//destructor
template <class T>
myList<T>:: ~myList() {
	while (!isEmpty()) {
		remove();
	}
}


//insert front
template <class T>
void myList<T>::insert(T item) {
	node<T>* tmp = new node<T>(item);
	tmp->next = head;
	head = tmp;
	size++;
}

//remove first
template <class T>
void myList<T>::remove() {
	node<T>* tmp;
	if (head != nullptr) {
		tmp = head;
		head = tmp->next;
		delete tmp;
		size--;
	}
}

//return first item
template <class T>
T myList<T>::front() {
	if (head != nullptr) {
		return head->data;
	}
	else return "empty";
}	

template <class T>
int myList<T>::find(T item) {
	node<T>* tmp = head;
	int compares = 0;
	while (tmp != nullptr) { 
		if (tmp->data.length() != item.length()) { tmp = tmp->next; continue; } //move on if the words aren't the same length
		if (int(tmp->data[0]) != int(item[0])) { tmp = tmp->next; continue; } //move on if the words don't start with the same letter
		compares++;
		if (item.compare(tmp->data) == 0) { 
			return compares; //word is found, compares is returned as a positive value.
		} 
		tmp = tmp->next;
	}
	return compares * -1; //compares is returned as a negative value to distinguigh regular compares from the 'word-not-found' compares.
}


template <class T>
void myList<T>::display() {
	node<T>* tmp = head;
	while (tmp != nullptr) {
		cout << tmp->data << endl;
		tmp = tmp->next;
	}
}

template <class T>
void myList<T>::sort(int max) {
	node<T>* tmp = head;
	myList<T> sorted;
	int checkLength = max;
	while (checkLength >= 1) {	//sorting the dictionary in increasing word length to the sorted linked list.
		tmp = head;
		while (tmp != nullptr) {
			if (tmp->data.length() == checkLength) {
				sorted.insert(tmp->data);
			}
			tmp = tmp->next;
		}
		checkLength--;
	}
	node<T>* sorttmp = sorted.head;		//copying the sorted list back into the original dictionary
	tmp = head;
	while (sorttmp != nullptr && tmp != nullptr) {
		tmp->data = sorttmp->data;
		sorttmp = sorttmp->next;
		tmp = tmp->next;
	}
}
#endif