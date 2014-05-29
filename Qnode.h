/*Created By: Ahmed Faraj Ahmed
Date: 5/29/2014
Qnode
*/

#ifndef _QNODE
#define _QNODE

template<class ItemType>
class Qnode{
private:
	ItemType data;
	Qnode* next;

public:
	Qnode(){ next = 0; prev = 0;}
	Qnode(ItemType newdata){ data = newdata; prev = 0; next = 0;}
	
//		

	getNext(){ return next; }
	setNext(Qnode* newnext){ next = newnext; }

	getData(){ return data;}
	setData(ItemType newdata){ data = newdata; }

}

#endif
