// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by CNguyen///should I put my name here? I added the height variable
#ifndef _BINARY_NODE
#define _BINARY_NODE
#include<string>
using namespace std;

template<class ItemType>
class BinaryNode
{   
private:
	ItemType              item;         // Data portion
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
	int height;//will turn that to a private with setters and getters later
	string getState(){
		int leftHeight,rightHeight;
		leftHeight=rightHeight=-1;
		if(leftPtr!=0)
			leftHeight=leftPtr->height;
		if(rightPtr!=0)
			rightHeight=rightPtr->height;
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
	//will ask claire if this function should be here or in the BinaryTree.h
	// constructors
	BinaryNode(const ItemType & anItem)			   {item = anItem; leftPtr = 0; rightPtr = 0;height=0;}
	BinaryNode(const ItemType & anItem, 
		       BinaryNode<ItemType>* left, 
			   BinaryNode<ItemType>* right)		   {item = anItem; leftPtr = left; rightPtr = right;}///have to set the height ere
	// accessors
	void setItem(const ItemType & anItem)		   {item = anItem;}
	void setLeftPtr(BinaryNode<ItemType>* left)	   {leftPtr = left;}
	void setRightPtr(BinaryNode<ItemType>* right)  {rightPtr = right;}
	// mutators
	ItemType getItem() const					   {return item;}
	BinaryNode<ItemType>* getLeftPtr() const	   {return leftPtr;}
	BinaryNode<ItemType>* getRightPtr() const	   {return rightPtr;}

	bool isLeaf() const							   {return (leftPtr == 0 && rightPtr == 0);}
}; 

#endif 
