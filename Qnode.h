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
/*
Default constructor:	Sets the next parameter to null
*/
	Qnode(){ next = 0; }
/*
Constructor:	This takes a const reference to an ItemType and sets it
				as the DataValue of this Qnode. Also Sets the next pointer
				to null.

Parameters:		Const Reference to a Templated ItemType

*/
	Qnode(const ItemType& newdata){ data = newdata; next = 0;}
	
/*
getNext:		This function returns the next item of the node

Parameters:		None

Returns:		A pointer to the next Qnode
*/
	Qnode* getNext(){ return next; }
/*
setNext:		This function takes a pointer to a Qnode and sets it as the next
				of the current Qnode

Parameters:		A pointer to the Qnode which you'd like to set this object's next

Return:			None (void)
Side-effect:	The next pointer is set to the pointer which was passed to the object
*/
	void setNext(Qnode* newnext){ next = newnext; }

/*
getData:		Returns a copy of the data stored in the Qnode

Parameters:		None

Return:			The Templated ItemType which is stored in the Qnode. 
*/
	ItemType getData(){ return data;}
/*
setData:		This takes a Const Reference to a templated ItemType and sets it
				as the data of this Qnode

Parameters:		A const reference to a templated ItemType

Return:			None (void)
*/
	void setData(const ItemType& newdata){ data = newdata; }

};

#endif
