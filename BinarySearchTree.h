// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Abdulrahman Sahmoud
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryNode.h"
#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
protected:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	// returns a 0 pointer if it didn't find it
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
   
public:  
	// insert a node at the correct location
    virtual bool insert(const ItemType & newEntry);
	// remove a node if found
	virtual bool remove(const ItemType & anEntry);
	// find a target node
	virtual bool getEntry(const ItemType & target, ItemType & returnedItem) const;
 
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry){
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);  
	count++;
	return true;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target){
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	if(isSuccessful)
		count--;
	return isSuccessful; 
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const{
	BinaryNode<ItemType>* returnPtr=findNode(rootPtr,anEntry);
	if(returnPtr==0)//if we didn't find it
		return false;

	returnedItem=returnPtr->getItem();
	return true;
}  


//////////////////////////// end of public functions///////////////////////////////////////

//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr){
	if(nodePtr==0)
		return newNodePtr;
	if(newNodePtr->getItem()<nodePtr->getItem()){//if item we are going to insert is < current item
		if(nodePtr->getLeftPtr()==0)
			nodePtr->setLeftPtr(newNodePtr);
		else
			_insert(nodePtr->getLeftPtr(),newNodePtr);
	}//end if we are going left
	else {// if(newNodePtr->getItem()>=nodePtr->getItem()) //if item we are going to insert is >= current item
		if(nodePtr->getRightPtr()==0)
			nodePtr->setRightPtr(newNodePtr);
		else
			_insert(nodePtr->getRightPtr(),newNodePtr);
	}//end if we are going right
	return nodePtr;
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success){
	if (nodePtr == 0) {
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  {
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0){
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else {
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor){
	if (nodePtr->getLeftPtr() == 0){
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else {
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr, const ItemType & target) const {
	if(nodePtr==0)
		return 0;
	if(nodePtr->getItem()==target)
		return nodePtr;
	
	if(nodePtr->getItem()>target){
		return findNode(nodePtr->getLeftPtr(),target);
	}
	else {// if (nodePtr->getItem()<=target)
		return findNode(nodePtr->getRightPtr(),target);
	}
}  
////////////////////////////////////////end of private functions///////////////////////

#endif
