// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Abdulrahman Sahmoud
 
#ifndef _BINARY_TREE
#define _BINARY_TREE
#include <vector>
#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{

protected:
///return the variables here
public:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

	// "admin" functions
 	BinaryTree()						{rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree)	{
		clear();
		rootPtr=copyTree(tree.rootPtr),
		count=tree.count;
	}
	virtual ~BinaryTree()				{ destroyTree(rootPtr);}		
	BinaryTree & operator=(const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const				{return count == 0;}
	int size() const					{return count;}
	void clear()						{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(vector<ItemType> &)) const		{_preorder(visit, rootPtr);}
	void inOrder(void visit(vector<ItemType> &)) const		{_inorder(visit, rootPtr);}
	void postOrder(void visit(vector<ItemType> &)) const	    {_postorder(visit, rootPtr);}	
	void reverseOrder(void visit(vector<ItemType> &)) const	{_reverseOrder(visit, rootPtr);}	

	void preOrder(void visit(ItemType &)) const		{_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const		{_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const	    {_postorder(visit, rootPtr);}	
	void reverseOrder(void visit(ItemType &)) const	{_reverseOrder(visit, rootPtr);}	

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   

	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _reverseOrder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	// vector traverses
	void _preorder(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(vecotr<ItemType> &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr) const;
    void _reverseOrder(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr) const;

}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) {
	if(nodePtr==0)
		return 0;
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());
	newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
	newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr){
	if(nodePtr==0)
		return;

	destroyTree(nodePtr->getRightPtr());
	destroyTree(nodePtr->getLeftPtr());
	delete nodePtr;
}  
///////////////////////////vector traverses/////////////////////////////////////////////////////////
template<class ItemType>
void BinaryTree<ItemType>::_reverseOrder(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr) const{
	if (nodePtr == 0)
		return;

	ItemType item = nodePtr->getItem();
	_reverseOrder(visit, nodePtr->getRightPtr()); 
	visit(item);
	_reverseOrder(visit, nodePtr->getLeftPtr());
	
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr) const{
	if (nodePtr == 0)
		return;

	visit(nodePtr->getItem());
	_preorder(visit, nodePtr->getLeftPtr());
	_preorder(visit, nodePtr->getRightPtr()); 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr) const{
	if(nodePtr==0)
		return;
	
	_inorder(visit, nodePtr->getLeftPtr());
	visit(nodePtr->getItem());
	_inorder(visit, nodePtr->getRightPtr());
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(vector<ItemType> &), BinaryNode<ItemType>* nodePtr) const{
	if(nodePtr==0)
		return;

	_postorder(visit, nodePtr->getLeftPtr());
	_postorder(visit, nodePtr->getRightPtr());
	visit(nodePtr->getItem());
}  

///////////////////////////////////////////////////////////////////////////////////////
template<class ItemType>
void BinaryTree<ItemType>::_reverseOrder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const{
	if (nodePtr == 0)
		return;

	ItemType item = nodePtr->getItem();
	_reverseOrder(visit, nodePtr->getRightPtr()); 
	visit(item);
	_reverseOrder(visit, nodePtr->getLeftPtr());
	
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const{
	if (nodePtr == 0)
		return;

	visit(nodePtr->getItem());
	_preorder(visit, nodePtr->getLeftPtr());
	_preorder(visit, nodePtr->getRightPtr()); 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const{
	if(nodePtr==0)
		return;
	
	_inorder(visit, nodePtr->getLeftPtr());
	visit(nodePtr->getItem());
	_inorder(visit, nodePtr->getRightPtr());
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const{
	if(nodePtr==0)
		return;

	_postorder(visit, nodePtr->getLeftPtr());
	_postorder(visit, nodePtr->getRightPtr());
	visit(nodePtr->getItem());
}  

template<class ItemType>
BinaryTree<ItemType> & 	BinaryTree<ItemType>::	operator=(const BinaryTree<ItemType> & sourceTree){
	rootPtr=copyTree(sourceTree.rootPtr);
	count=sourceTree.count;
	return *this;
}  


#endif
