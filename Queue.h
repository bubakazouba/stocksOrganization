/*Created By: Ahmed Faraj Ahmed
Date: 5/29/2014
Queue
*/
#ifndef _QUEUE
#define _QUEUE

#include "Qnode.h"


template<class ItemType>
class Queue{
private:
	Qnode<ItemType>* first;	// pointer to the front of the list
	Qnode<ItemType>* last;	// pointer to the end of the list
	int count;



public:
	Queue(){ count = 0; first = 0; last = 0;}
	~Queue();
	
	int size() const{ return count;}
	bool isEmpty() const{ return (count == 0); }

	bool enqueue( const ItemType& newEntry);
	
	bool peek(ItemType& var) const;
	bool dequeue();
		
};




template<class ItemType>
~Queue(){

	Qnode<ItemType>* nodePtr = first;
	
	while( first != 0){
		first = first->getNext();
		delete nodePtr;
		nodePtr = first;
	}	

}


template<class ItemType>
bool enqueue( const ItemType& newEntry){
	
	Qnode<ItemType>* newNodePointer = new Qnode<ItemType>(newEntry);
	
	if(count == 0){
		first = newNodePointer;
		last = newNodePointer;
	}else{
		last->setNext(newNodePointer);
	}
	last = newNodePointer;
	count++;	
	return true;

}


/*
peek: 	This function takes a reference to the Templated type of the queue
	  	and stores the item that is in the front of the queue in the 
		referenced parameter.


Parameters: A reference to a variable of the Templated Type to store the
			item in the front of the queue in.

Return Value: 	Returns a boolean value, false if the Queue is empty
				and true otherwise.


Dependencies: requires the Templated type to have an overloaded equal.

*/
template<class ItemType>
bool peek(ItemType& var) const{
	
	if(count != 0){
		var = first->getData();
		return true;
	}else{
		return false;
	}	
}


/*
dequeue:	
*/
template<class ItemType>
bool dequeue(){

	if(count == 0)
		return false;

	Node<ItemType>* toDelete = first;

	if(first == last){	//last item in the queue
		first = 0;
		last = 0;
	} else {
		first = first->getNext();
	}

	delete toDelete;
	count--;
	return true;
}


#endif
