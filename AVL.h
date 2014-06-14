//check all my functions take consts return consts and pass by reference the vectors
//change comments
// AVL ADT
// Created By: Abdulrahman Sahmoud

#ifndef _AVL
#define _AVL

#include <algorithm>
#include "BinarySearchTree.h"

template<class ItemType>
class AVL : public BinarySearchTree<ItemType>
{   
private:
	BinaryNode<ItemType>* rotateRight(BinaryNode<ItemType>* nodePtr);
	BinaryNode<ItemType>* rotateLeft (BinaryNode<ItemType>* nodePtr);
	void AnalyzeInsert(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& childPtr);
	void AnalyzeDelete(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& childPtr);

  
    // internal insert node: insert newNode in nodePtr subtree 
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode); 
     
    // internal replace node: locate and delete target node under nodePtr subtree 
    BinaryNode<ItemType>* _replace(BinaryNode<ItemType>* nodePtr, const vector<ItemType> target, bool & success,vector<ItemType> newVector); 

	int getHeight(BinaryNode<ItemType>*  nodePtr);
	bool OOB(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& maxChild);

    // search for target node 
    // returns a 0 pointer if it didn't find it 
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const vector<ItemType> & target) const; 
public:
    // insert a node at the correct location 
    bool insert(const ItemType & newEntry); 

	// replace a node if found 
    bool replace(const ItemType & anEntry,vector<ItemType> newVector); 
      
    // find a target node 
    bool getEntry(const ItemType & target, vector<ItemType> & returnedItem) const; 
   
};
///////////////////////// public function definitions /////////////////////////// 
  
template<class ItemType> 
bool AVL<ItemType>::insert(const ItemType & newEntry){ 
    vector<ItemType> newvector; 
    newvector.push_back(newEntry); 
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newvector); 
    rootPtr = _insert(rootPtr, newNodePtr);   
    count++; 
    return true; 
}   
  
template<class ItemType> 
bool AVL<ItemType>::replace(const ItemType & target,vector<ItemType> newVector){ 
    bool isSuccessful = false; 
    vector<ItemType> targetVector;
	targetVector.push_back(target); 
    rootPtr = _replace(rootPtr, targetVector, isSuccessful,newVector); 
	if(isSuccessful)
		count--; 
    return isSuccessful;  
}   
  
template<class ItemType> 
bool AVL<ItemType>::getEntry(const ItemType& anEntry, vector<ItemType> & returnedItem) const{ 
    vector<ItemType> targetVector; 
    targetVector.push_back(anEntry); 
    BinaryNode<ItemType>* returnPtr=findNode(rootPtr,targetVector); 
    if(returnPtr==0)//if we didn't find it 
        return false; 
	returnedItem=returnPtr->getVector();
    return true; 
}   
    
//////////////////////////// private functions ////////////////////////////////////////////
template<class ItemType>
int  AVL<ItemType>::getHeight(BinaryNode<ItemType>*  nodePtr){//if im rotating
		int initialHeight=nodePtr->height;
		int leftHeight=-1,rightHeight=-1;
		if(nodePtr->getLeftPtr()!=0)leftHeight=nodePtr->getLeftPtr()->height;
		if(nodePtr->getRightPtr()!=0)rightHeight=nodePtr->getRightPtr()->height;
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
void AVL<ItemType>::AnalyzeInsert(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& childPtr){
	if(nodePtr->getState()=="LLH"){
	//the state of the child(the max child, the one making the porblem) cant be EH if it was an insert
			if(childPtr->getState()=="LH"){
				nodePtr=rotateRight(nodePtr);
				nodePtr->getRightPtr()->height=getHeight(nodePtr->getRightPtr());
			}
		else {//right of left
				nodePtr->setLeftPtr(rotateLeft(nodePtr->getLeftPtr()));
				nodePtr->getLeftPtr()->getLeftPtr()->height=getHeight(nodePtr->getLeftPtr()->getLeftPtr());
	
				nodePtr=rotateRight(nodePtr);
				nodePtr->getRightPtr()->height=getHeight(nodePtr->getRightPtr());
			}
	}//end of if nodePtr->getState=="LLH"
	if(nodePtr->getState()=="RRH"){
		if(childPtr->getState()=="RH"){
			nodePtr=rotateLeft(nodePtr);
			nodePtr->getLeftPtr()->height=getHeight(nodePtr->getLeftPtr());
		}
		else {//left of right
			nodePtr->setRightPtr(rotateRight(nodePtr->getRightPtr()));
			nodePtr->getRightPtr()->getRightPtr()->height=getHeight(nodePtr->getRightPtr()->getRightPtr());
			nodePtr=rotateLeft(nodePtr);
			nodePtr->getLeftPtr()->height=getHeight(nodePtr->getLeftPtr());
		}
	}
}

template<class ItemType>
void AVL<ItemType>::AnalyzeDelete(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& childPtr){
	if(nodePtr->getState()=="LLH"){
		//if it's LLH then it's (left of left) or (right of left)
		if(childPtr->getState()=="LH"||childPtr->getState()=="EH"){
			nodePtr=rotateRight(nodePtr);
			nodePtr->getRightPtr()->height=getHeight(nodePtr->getRightPtr());
		}
		else {//right of left
			nodePtr->setLeftPtr(rotateLeft(nodePtr->getLeftPtr()));
			nodePtr->getLeftPtr()->getLeftPtr()->height=getHeight(nodePtr->getLeftPtr()->getLeftPtr());

			nodePtr=rotateRight(nodePtr);
			nodePtr->getRightPtr()->height=getHeight(nodePtr->getRightPtr());
		}
	}//end of if nodePtr->getState=="LLH"
	if(nodePtr->getState()=="RRH"){
		if(childPtr->getState()=="RH"||childPtr->getState()=="EH"){
			nodePtr=rotateLeft(nodePtr);
			nodePtr->getLeftPtr()->height=getHeight(nodePtr->getLeftPtr());
		}
		else {
			nodePtr->setRightPtr(rotateRight(nodePtr->getRightPtr()));
			nodePtr->getRightPtr()->getRightPtr()->height=getHeight(nodePtr->getRightPtr()->getRightPtr());

			nodePtr=rotateLeft(nodePtr);
			nodePtr->getLeftPtr()->height=getHeight(nodePtr->getLeftPtr());
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
		AnalyzeInsert(nodePtr,maxChild);

	nodePtr->height=getHeight(nodePtr);
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
			nodePtr = deleteNode(nodePtr); 
		}
	////////////////////////////////////////////////////////////////////
	if(nodePtr==0)//if it was a leafNode
		return nodePtr;//return it,don't go through the checking because it will give an error when trying to dereference the nodePtr 
	BinaryNode<ItemType>* maxChild;
	if(OOB(nodePtr,maxChild))
		AnalyzeDelete(nodePtr,maxChild);
	
	nodePtr->height=getHeight(nodePtr);
	return nodePtr;   
}  
template<class ItemType>
bool AVL<ItemType>::OOB(BinaryNode<ItemType>*& nodePtr,BinaryNode<ItemType>*& maxChild){

	int leftHeight=-1,rightHeight=-1;
	if(nodePtr->getLeftPtr()!=0)	leftHeight=nodePtr->getLeftPtr()->height;
	if(nodePtr->getRightPtr()!=0)	rightHeight=nodePtr->getRightPtr()->height;

	if(leftHeight>rightHeight)//if left is higher
		maxChild=nodePtr->getLeftPtr();
	else 
		maxChild=nodePtr->getRightPtr();
	
	nodePtr->height=max(leftHeight,rightHeight)+1;
	if(nodePtr->getState()=="RRH"||nodePtr->getState()=="LLH")
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
