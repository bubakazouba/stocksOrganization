/*Created By: Ahmed Faraj Ahmed
Date: 5/29/2014
Queue
*/
#ifndef _QUEUE
#define _QUEUE

#include "Qnode.h"

/*
Notes on this Queue:
***************************NOTICE*************************************
****The queue does not make copies of the data, it stores a pointer to
	the data you hare giving it because it takes a reference to the data
	as a parameter. This means that if you change the data after inserting
	it into the queue you will be changing that which you inserted, since
	it is the same data!

	This also allows you to enqueues like this:
		Queue<Objects> list;
		list.enqueue( new Objects(parameters) );
	
*/

template<class ItemType>
class Queue{
private:
	Qnode<ItemType>* first;	// pointer to the front of the list
	Qnode<ItemType>* last;	// pointer to the end of the list
	int count;


public:
	Queue(){ count = 0; first = 0; last = 0;}
	~Queue(){ clear(); }
	
	int size() const{ return count;}
	bool isEmpty() const{ return (count == 0); }

	bool enqueue( const ItemType& newEntry);

	bool peek(ItemType& var) const;
	bool dequeue();
	bool clear();		
};
/*
clear:			This function deletes all the Qnodes in the Queue

Parameters:		None

Return:			A boolean value whether the function successfuly cleared the Queue
*/
template<class ItemType>
bool Queue<ItemType>::clear(){	

	Qnode<ItemType>* nodePtr = Queue::first;
	
	while( Queue::first != 0){
		Queue::first = Queue::first->getNext();
		delete nodePtr;
		nodePtr = Queue::first;
	}
	return true;
}

/*
enqueue:		This function takes a const reference to an Item and adds it to
				the end of the Queue.

Parameters:		A reference to ItemType to add to the end of the queue

Returns:		Boolean, whether the ItemType was successfuly enqueued
*/
template<class ItemType>
bool Queue<ItemType>::enqueue( const ItemType& newEntry){
	
	Qnode<ItemType>* newNodePointer = new Qnode<ItemType>(newEntry);
	
	if(Queue::count == 0){
		Queue::first = newNodePointer;
		Queue::last = newNodePointer;
	}else{
		Queue::last->setNext(newNodePointer);
	}
	Queue::last = newNodePointer;
	Queue::count++;	
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
bool Queue<ItemType>::peek(ItemType& var) const{
	
	if(count != 0){
		var = first->getData(); 
		return true;
	}else{
		return false;
	}	
}

/*
dequeue:		This function removes a node from the end of the Queue

Parameters:		None

Return:			A boolean value whether the Item was successfuly removed
				from the end of the Queue

NOTE: 		User of the Queue should delete the items that are enqueued on their own
			if they are dynamically allocated. The Queue will not delete the Item.
*/
template<class ItemType>
bool Queue<ItemType>::dequeue(){

	if(count == 0)
		return false;

	Qnode<ItemType>* toDelete = first;

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
