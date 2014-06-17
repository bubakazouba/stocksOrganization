//check all my functions take consts return consts and pass by reference the vectors
//change comments
// AVL ADT
// Created By: Abdulrahman Sahmoud

#ifndef _AVL
#define _AVL

#include <algorithm>
#include <iostream>
#include "BinarySearchTree.h"
#include "Queue.h"

template<class ItemType>
class AVL : public BinarySearchTree<ItemType>
{   
private:
	/*
	_getMax: a private function that gets the maximum node in the tree by recurively going to the right child of the current pointer till it doesn't see a right child, so we become at the right most node, this is the greatest node in the tree

	Paramters: a pointer to a BinaryNode, when its called initially its the rootPtr

	Return Value: it returns the vector from the right most node
	*/
	vector<ItemType> _getMax(BinaryNode<ItemType>* nodePtr) const;
	/*
	_getMin: a private function that gets the minimum node in the tree by recurively going to the left child of the current pointer till it doesn't see a left child, so we become at the left most node, this is the smallest node in the tree

	Paramters: a pointer to a BinaryNode, when its called initially its the rootPtr

	Return Value: it returns the vector from the left most node
	*/
	vector<ItemType> _getMin(BinaryNode<ItemType>* nodePtr) const;
	/*
	_greaterThanOrEq: a private function that uses a visit function on every node in the tree greater than a certain value passed to it

	Paramaters: the visit function, the nodePtr that will be using it to decide which child to use from it to go next, the variable that the function is comparing every node to , if it is greater than it output it

	Return Value: it doesn't return
	*/
	void _greaterThanOrEq(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr,const vector<ItemType> & var) const;
	/*
	_greaterThanOrEq: a private function that uses a visit function on every node in the tree samller than a certain value passed to it

	Paramaters: the visit function, the nodePtr that will be using it to decide which child to use from it to go next, the variable that the function is comparing every node to , if it is greater than it then visit it

	Return Value: none
	*/
	void _lessThanOrEq(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr,const vector<ItemType> & var) const;
	/*
	getState: a private function that calculates the state of a node

	Paramters: a BinaryNode

	Return Value: a string representing the state of the node
	*/
	string getState(BinaryNode<ItemType>* nodePtr);
	/*
	rotateRight: a private function that takes a BinaryNode pointer and rotates it right and return it again

	Paramaters: BinaryNode pointer

	Return Value: BinaryNode pointer
	*/
	BinaryNode<ItemType>* rotateRight(BinaryNode<ItemType>* nodePtr);
	/*
	rotateRight: a private function that takes a BinaryNode pointer and rotates it left and return it again

	Paramaters: BinaryNode pointer

	Return Value: BinaryNode pointer
	*/
	BinaryNode<ItemType>* rotateLeft (BinaryNode<ItemType>* nodePtr);
	/*
	analyzeInsert: a private function that takes an out of balance node and the greater of it's 2 childs, because thats the one that will be used to fix the out of balance
	the analyzeInsert function's goal is to fix the out of balance, it works only when the out of balance node is a result of inserting
	(there is more explanation how the function works inside the code)

	Parameters: an out of balance node and the greater of it's 2 childs 

	Return Value: none
	*/
	void analyzeInsert(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& childPtr);
	/*
	analyzeDelete: a private function that takes an out of balance node and the greater of it's 2 childs, because thats the one that will be used to fix the out of balance
	the analyzeDelete function's goal is to fix the out of balance, it works only when the out of balance node is a result of deleting
	(there is more explanation how the function works inside the code)

	Parameters: an out of balance node and the greater of it's 2 childs 

	Return Value: none
	*/
	void analyzeDelete(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& childPtr);
    /*
	_insert: a private function that inserts a node in the tree, it also checks if the node that is meant to be inserted exists a node like it, if this happends it inserts its value to the vector of the node already there in the tree

	Paramaters: BinaryNode pointer that's the current node, and a BinaryNode pointer to the new node meant to be inserted

	Return Value: it returns a BinaryNode pointer that is the modified child node in each recursive call in the function:
	 in the code we have: nodePtr->setLeftPtr(_insert(..)), and it returns in rootPtr to the initial call
	*/
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);      
    /*
	_replace: a private function that replaces the vector the BinaryNode(specified in the paramater) have by the one taken by the function as a paramater

	Paramaters: BinaryNode pointer (current node), a vector the function is looking for, a bool success variable to change it if it found it or not, the newvector to replace by

	Return Value: it returns a BinaryNode pointer that is the modified child node in each recursive call in the function:
	 in the code we have: nodePtr->setLeftPtr(_insert(..)), and it returns in rootPtr to the initial call

	*/
    BinaryNode<ItemType>* _replace(BinaryNode<ItemType>* nodePtr, const vector<ItemType> target, bool & success,vector<ItemType> newVector); 
	/*
	getHeight: private function that calculates the height of a node

	Paramaters: BinaryNode pointer


	*/
	int getHeight(BinaryNode<ItemType>*  nodePtr);
	bool OOB(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& maxChild);

    // search for target node 
    // returns a 0 pointer if it didn't find it 
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const vector<ItemType> & target) const; 

	void _printIndented(BinaryNode<ItemType>* node, int depth, void printing(vector<ItemType>&) ) const;

	void _serialize(Queue<ItemType>& serial, Queue<BinaryNode<ItemType>*>& tempQ) const;
public:
	bool getMax(vector<ItemType> & ret) const;
	bool getMin(vector<ItemType> & ret) const;
	void greaterThanOrEq(void visit(vector<ItemType> &),const ItemType & val) const;
	void lessThanOrEq(void visit(vector<ItemType> &),const ItemType & val) const;
    // insert a node at the correct location 
    bool insert(const ItemType & newEntry); 

	// replace a node if found 
    bool replace(const ItemType & anEntry,vector<ItemType> newVector); 
      
    // find a target node 
    bool getEntry(const ItemType & target, vector<ItemType> & returnedItem) const; 
   
	void printIndented( void printing(vector<ItemType>&) ) const;
	void serialize(Queue<ItemType>& serial ) const;
};
///////////////////////// public function definitions /////////////////////////// 
template<class ItemType> 
void AVL<ItemType>::serialize(Queue<ItemType>& serial ) const{
    Queue<BinaryNode<ItemType>*> tempQ;
    tempQ.enqueue(this->rootPtr);
    _serialize(serial, tempQ);
}
template<class ItemType> 
void AVL<ItemType>::printIndented( void printing(vector<ItemType>&) ) const{
    int depth = 0;
    _printIndented(this->rootPtr, depth, printing);
}
template<class ItemType> 
bool AVL<ItemType>::getMax(vector<ItemType> & ret) const{
	ret=_getMax(this->rootPtr);
	if(ret.size()==0)
		return false;
	return true;
}
template<class ItemType> 
bool AVL<ItemType>::getMin(vector<ItemType> & ret) const{
	ret=_getMin(this->rootPtr);
	if(ret.size()==0)
		return false;
	return true;
}

template<class ItemType> 
void AVL<ItemType>::greaterThanOrEq(void visit(vector<ItemType> &),const ItemType & val) const		{
		vector<ItemType>vec;
		vec.push_back(val);
		_greaterThanOrEq(visit, this->rootPtr,vec);
}
template<class ItemType> 
void AVL<ItemType>::lessThanOrEq(void visit(vector<ItemType> &),const ItemType & val) const		{
		vector<ItemType>vec;
		vec.push_back(val);
		_lessThanOrEq(visit, this->rootPtr,vec);
}
  
template<class ItemType> 
bool AVL<ItemType>::insert(const ItemType & newEntry){ 
    vector<ItemType> newvector; 
    newvector.push_back(newEntry); 
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newvector); 
    this->rootPtr = _insert(this->rootPtr, newNodePtr);   
	this->rootPtr;
    this->count++; 
    return true; 
}   
  
template<class ItemType> 
bool AVL<ItemType>::replace(const ItemType & target,vector<ItemType> newVector){ 
    bool isSuccessful = false; 
    vector<ItemType> targetVector;
	targetVector.push_back(target); 
    this->rootPtr = _replace(this->rootPtr, targetVector, isSuccessful,newVector); 
	if(isSuccessful)
		this->count--; 
    return isSuccessful;  
}   
  
template<class ItemType> 
bool AVL<ItemType>::getEntry(const ItemType& anEntry, vector<ItemType> & returnedItem) const{ 
    vector<ItemType> targetVector; 
    targetVector.push_back(anEntry); 
    BinaryNode<ItemType>* returnPtr=findNode(this->rootPtr,targetVector); 
    if(returnPtr==0)//if we didn't find it 
        return false; 
	returnedItem=returnPtr->getVector();
    return true; 
}   
    
//////////////////////////// private functions ////////////////////////////////////////////
template<class ItemType> 
void AVL<ItemType>::_serialize(Queue<ItemType>& serial, Queue<BinaryNode<ItemType>*>& tempQ) const{
    
    BinaryNode<ItemType>* temp;
    
    while( ! tempQ.isEmpty() ){
        tempQ.peek(temp);
        if(temp->getLeftPtr() != 0)
            tempQ.enqueue(temp->getLeftPtr() );
        if( temp->getRightPtr() != 0)
            tempQ.enqueue(temp->getRightPtr() );
		tempQ.dequeue();
        int size = temp->getVector().size();
        for( int i = 0; i< size ; i++){
                serial.enqueue( temp->getVector()[i] );
        }
    }
}

template<class ItemType> 
void AVL<ItemType>::_printIndented(BinaryNode<ItemType>* node, int depth, void printing(vector<ItemType>&) ) const{
    if (node == 0)
        return;

    _printIndented(node->getRightPtr() , depth+1,printing);
    
    for(int i =0; i< depth; i++)
        cout<< "\t";
    vector<ItemType> temp = node->getVector();
    printing(temp);
    cout << endl;

    _printIndented(node->getLeftPtr(), depth+1,printing);

    return;

}
template<class ItemType> 
vector<ItemType> AVL<ItemType>::_getMax(BinaryNode<ItemType>* nodePtr) const{
	if(nodePtr==0){
		vector<ItemType> emptyvector;
		return emptyvector;
	}
	if(nodePtr->getRightPtr()==0)
		return nodePtr->getVector();
	return _getMax(nodePtr->getRightPtr());
}
template<class ItemType> 
vector<ItemType> AVL<ItemType>::_getMin(BinaryNode<ItemType>* nodePtr) const{
	if(nodePtr==0){
		vector<ItemType> emptyvector;
		return emptyvector;
	}
	if(nodePtr->getLeftPtr()==0)
		return nodePtr->getVector();
	return _getMin(nodePtr->getLeftPtr());
}

template<class ItemType> 
void AVL<ItemType>::_greaterThanOrEq(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr,const vector<ItemType> & var) const{
		if(nodePtr==0)
			return;
		vector<ItemType> tmpVec=nodePtr->getVector();
		if(nodePtr->getVector()==var){
			visit(tmpVec);
			_greaterThanOrEq(visit,nodePtr->getRightPtr(),var);
		}
		else if(nodePtr->getVector()>var){
			visit(tmpVec);
			_greaterThanOrEq(visit,nodePtr->getRightPtr(),var);
			_greaterThanOrEq(visit,nodePtr->getLeftPtr(),var);
		}
		else {
			_greaterThanOrEq(visit,nodePtr->getRightPtr(),var);
		}
	}
template<class ItemType> 
void AVL<ItemType>::_lessThanOrEq(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr,const vector<ItemType> & var) const{
		if(nodePtr==0)
			return;
		vector<ItemType> tmpVec=nodePtr->getVector();
		if(nodePtr->getVector()==var){
			visit(tmpVec);
			_lessThanOrEq(visit,nodePtr->getRightPtr(),var);
		}
		else if(nodePtr->getVector()<var){
			visit(tmpVec);
			_lessThanOrEq(visit,nodePtr->getRightPtr(),var);
			_lessThanOrEq(visit,nodePtr->getLeftPtr(),var);
		}
		else {
			_lessThanOrEq(visit,nodePtr->getLeftPtr(),var);
		}
	}

template<class ItemType> 
string AVL<ItemType>::getState(BinaryNode<ItemType>* nodePtr){ 
        int leftHeight,rightHeight; 
        leftHeight=rightHeight=-1; 
		if(nodePtr->getLeftPtr()!=0) 
			leftHeight=nodePtr->getLeftPtr()->getHeight(); 
		if(nodePtr->getRightPtr()!=0) 
			rightHeight=nodePtr->getRightPtr()->getHeight();
        if(leftHeight-rightHeight==0) 
            return "EH"; 
        if(leftHeight-rightHeight==1) 
            return "LH"; 
        if(rightHeight-leftHeight==1) 
            return "RH"; 
        if(leftHeight-rightHeight==2) 
            return "LLH"; 
        if(rightHeight-leftHeight==2) 
            return "RRH"; 
        return "ERROR"; 
    } 
template<class ItemType>
int  AVL<ItemType>::getHeight(BinaryNode<ItemType>*  nodePtr){//if im rotating
		int initialHeight=nodePtr->getHeight();
		int leftHeight=-1,rightHeight=-1;
		if(nodePtr->getLeftPtr()!=0)
			leftHeight=nodePtr->getLeftPtr()->getHeight();
		if(nodePtr->getRightPtr()!=0)
			rightHeight=nodePtr->getRightPtr()->getHeight();
		return max(leftHeight,rightHeight)+1;
   }

template<class ItemType>
BinaryNode<ItemType>* AVL<ItemType>::rotateRight(BinaryNode<ItemType>*  nodePtr){
	BinaryNode<ItemType>* tempPtr;
	tempPtr=nodePtr->getLeftPtr();
	nodePtr->setLeftPtr(tempPtr->getRightPtr());
	tempPtr->setRightPtr(nodePtr);
	return tempPtr;
}

template<class ItemType>
BinaryNode<ItemType>* AVL<ItemType>::rotateLeft (BinaryNode<ItemType>* nodePtr){
	BinaryNode<ItemType>* tempPtr=nodePtr->getRightPtr();
	nodePtr->setRightPtr(tempPtr->getLeftPtr());
	tempPtr->setLeftPtr(nodePtr);
	nodePtr=tempPtr;
	return tempPtr;
}

template<class ItemType>
void AVL<ItemType>::analyzeInsert(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& childPtr){
	if(getState(nodePtr)=="LLH"){
	//the state of the child(the max child, the one making the porblem) cant be EH if it was an insert
			if(getState(childPtr)=="LH"){
				nodePtr=rotateRight(nodePtr);
				nodePtr->getRightPtr()->setHeight(getHeight(nodePtr->getRightPtr()));
			}
		else {//right of left
				nodePtr->setLeftPtr(rotateLeft(nodePtr->getLeftPtr()));
				nodePtr->getLeftPtr()->getLeftPtr()->setHeight(getHeight(nodePtr->getLeftPtr()->getLeftPtr()));
	
				nodePtr=rotateRight(nodePtr);
				nodePtr->getRightPtr()->setHeight(getHeight(nodePtr->getRightPtr()));
			}
	}//end of if nodePtr->getState=="LLH"
	if(getState(nodePtr)=="RRH"){
		if(getState(childPtr)=="RH"){
			nodePtr=rotateLeft(nodePtr);
			nodePtr->getLeftPtr()->setHeight(getHeight(nodePtr->getLeftPtr()));
		}
		else {//left of right
			nodePtr->setRightPtr(rotateRight(nodePtr->getRightPtr()));
			nodePtr->getRightPtr()->getRightPtr()->setHeight(getHeight(nodePtr->getRightPtr()->getRightPtr()));
			nodePtr=rotateLeft(nodePtr);
			nodePtr->getLeftPtr()->setHeight(getHeight(nodePtr->getLeftPtr()));
		}
	}
}

template<class ItemType>
void AVL<ItemType>::analyzeDelete(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& childPtr){
	if(getState(nodePtr)=="LLH"){
		//if it's LLH then it's (left of left) or (right of left)
		if(getState(childPtr)=="LH"||getState(childPtr)=="EH"){
			nodePtr=rotateRight(nodePtr);
			nodePtr->getRightPtr()->setHeight(getHeight(nodePtr->getRightPtr()));
		}
		else {//right of left
			nodePtr->setLeftPtr(rotateLeft(nodePtr->getLeftPtr()));
			nodePtr->getLeftPtr()->getLeftPtr()->setHeight(getHeight(nodePtr->getLeftPtr()->getLeftPtr()));

			nodePtr=rotateRight(nodePtr);
			nodePtr->getRightPtr()->setHeight(getHeight(nodePtr->getRightPtr()));
		}
	}//end of if nodePtr->getState=="LLH"
	if(getState(nodePtr)=="RRH"){
		if(getState(childPtr)=="RH"||getState(childPtr)=="EH"){
			nodePtr=rotateLeft(nodePtr);
			nodePtr->getLeftPtr()->setHeight(getHeight(nodePtr->getLeftPtr()));
		}
		else {
			nodePtr->setRightPtr(rotateRight(nodePtr->getRightPtr()));
			nodePtr->getRightPtr()->getRightPtr()->setHeight(getHeight(nodePtr->getRightPtr()->getRightPtr()));

			nodePtr=rotateLeft(nodePtr);
			nodePtr->getLeftPtr()->setHeight(getHeight(nodePtr->getLeftPtr()));
		}
	}
}

template<class ItemType>
BinaryNode<ItemType>* AVL<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,BinaryNode<ItemType>* newNodePtr){
	if (nodePtr == 0)
		return newNodePtr; 

	if (newNodePtr->getVector() < nodePtr->getVector()) //if item less than the current node 
		nodePtr->setLeftPtr(_insert (nodePtr->getLeftPtr(), newNodePtr));
	else if(newNodePtr->getVector() >nodePtr->getVector())
		nodePtr->setRightPtr(_insert (nodePtr->getRightPtr(), newNodePtr));
	else 
		nodePtr->pushback(newNodePtr->getVector()[0]); 
	////////////////////////////////////////////////////////////////////
	BinaryNode<ItemType>* maxChild;
	if(OOB(nodePtr,maxChild))
		analyzeInsert(nodePtr,maxChild);

	nodePtr->setHeight(getHeight(nodePtr));
	return nodePtr;  //return original root
}  

template<class ItemType>
BinaryNode<ItemType>* AVL<ItemType>::_replace(BinaryNode<ItemType>* nodePtr, const vector<ItemType> target, bool & success,vector<ItemType> newVector){ 
	if (nodePtr == 0) {
		success = false;
		return 0;
	}
	if (nodePtr->getVector() > target)		 
		nodePtr->setLeftPtr(_replace(nodePtr->getLeftPtr(), target, success,newVector));
	else if (nodePtr->getVector() < target)	 
		nodePtr->setRightPtr(_replace(nodePtr->getRightPtr(), target, success,newVector));
	else{
		nodePtr->setVector(newVector);
		if(nodePtr->getVector().size()==0)
			nodePtr = this->deleteNode(nodePtr); 
		}
	////////////////////////////////////////////////////////////////////
	if(nodePtr==0)//if it was a leafNode
		return nodePtr;//return it,don't go through the checking because it will give an error when trying to dereference the nodePtr 
	BinaryNode<ItemType>* maxChild;
	if(OOB(nodePtr,maxChild))
		analyzeDelete(nodePtr,maxChild);
	
	nodePtr->setHeight(getHeight(nodePtr));
	return nodePtr;   
}  
template<class ItemType>
bool AVL<ItemType>::OOB(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& maxChild){

	int leftHeight=-1,rightHeight=-1;
	if(nodePtr->getLeftPtr()!=0)	leftHeight=nodePtr->getLeftPtr()->getHeight();
	if(nodePtr->getRightPtr()!=0)	rightHeight=nodePtr->getRightPtr()->getHeight();

	if(leftHeight>rightHeight)//if left is higher
		maxChild=nodePtr->getLeftPtr();
	else 
		maxChild=nodePtr->getRightPtr();
	
	nodePtr->setHeight(max(leftHeight,rightHeight)+1);
	if(getState(nodePtr)=="RRH"||getState(nodePtr)=="LLH")
		return true;
	
	return false;
}
template<class ItemType> 
BinaryNode<ItemType>* AVL<ItemType>::findNode(BinaryNode<ItemType>* nodePtr, const vector<ItemType> & target) const { 
    if(nodePtr==0) 
        return 0; 
    if(nodePtr->getVector()==target) 
        return nodePtr; 
      
    if(nodePtr->getVector()>target){ 
        return findNode(nodePtr->getLeftPtr(),target); 
    } 
    else {// if (nodePtr->getVector()<=target) 
        return findNode(nodePtr->getRightPtr(),target); 
    } 
}  
///////////////////////end of private functions ///////////////////////////////////////////

#endif
