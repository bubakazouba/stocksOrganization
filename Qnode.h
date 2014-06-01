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
	Qnode(){ next = 0; }
	Qnode(const ItemType& newdata){ data = newdata; next = 0;}
	
//		

	Qnode* getNext(){ return next; }
	void setNext(Qnode* newnext){ next = newnext; }

	ItemType getData(){ return data;}
	void setData(const ItemType& newdata){ data = newdata; }

};

#endif
