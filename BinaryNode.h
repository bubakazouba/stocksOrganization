//ZABAT FEL BINARY NODE CONSTRUCTOR tany ya5od itemtype w y3ml vector w kda
//why is the _remove function not taking target by reference
//zabat overloaders el vectors
//change getVector to return const
//can this class have inline long functions 

// Node for a binary tree 
// Created by Frank M. Carrano and Tim Henry. 
// Modified by CNguyen 
#ifndef _BINARY_NODE 
#define _BINARY_NODE 
#include<string> 
#include<vector> 
using namespace std; 
  
template<class ItemType> 
class BinaryNode 
{    
private: 
    vector<ItemType>          vec;         // Vector portion 
	ItemType                 item;         // Data portion 
    BinaryNode<ItemType>* leftPtr;        // Pointer to left child 
    BinaryNode<ItemType>* rightPtr;       // Pointer to right child 
	int height; 
public: 
	void setHeight(int H){height=H;}
	int getHeight()const{return height;}
	BinaryNode(){leftPtr=0;rightPtr=0;}
	void pushback(ItemType & obj){vec.push_back(obj);} 
    // constructors 
    BinaryNode(const vector<ItemType> & aVec)        {vec = aVec; leftPtr = 0; rightPtr = 0;height=0;} 
	BinaryNode(const ItemType & anItem)               {item = anItem; leftPtr = 0; rightPtr = 0;height=0;} 
    
	BinaryNode(const ItemType & anItem,  
               BinaryNode<ItemType>* left,  
               BinaryNode<ItemType>* right)          {item = anItem;  leftPtr = left; rightPtr = right;}///have to set the height ere 

    BinaryNode(const vector<ItemType> & aVec,  
               BinaryNode<ItemType>* left,  
               BinaryNode<ItemType>* right)          {vec=aVec; leftPtr = left; rightPtr = right;}///have to set the height ere 

    // accessors 
    void setVector(const vector<ItemType> & aVec) {vec = aVec;} 
	void setItem(const ItemType & anItem)         {item = anItem;} 
    void setLeftPtr(BinaryNode<ItemType>* left)      {leftPtr = left;} 
    void setRightPtr(BinaryNode<ItemType>* right)  {rightPtr = right;} 
    // mutators 
    ItemType getItem() const                              {return item;} 
	vector<ItemType> getVector() const                      {return vec;} 
    BinaryNode<ItemType>* getLeftPtr() const     {return leftPtr;} 
    BinaryNode<ItemType>* getRightPtr() const    {return rightPtr;} 
  
    bool isLeaf() const                            {return (leftPtr == 0 && rightPtr == 0);} 
};  
  
#endif  