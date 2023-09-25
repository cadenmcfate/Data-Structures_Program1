//node.h
//defines the node class for a linked list
//Caden McFate
//Programming assignment 1
//COSC 2030

#ifndef NODE_
#define NODE_
template<class T>
class node {
public:
	T data;
	node<T>* next;
	node() { next = nullptr;  }
	node(T item) {
		data = item; 
		next = nullptr;
	}
};
#endif