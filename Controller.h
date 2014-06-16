//Name: Inaki Gonzalo

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <string>
#include "Stocks.h"
#include "Queue.h"
#include "HashTable.h"
#include "AVL.h"
#include <vector>

  
using namespace std;
class Controller{
private:

int readFile(string file,Queue<Stocks*>& StockQueue);
HashTable* table;
AVL<Stocks*>* tree;
string comparing;


public:
Controller(string file,string comp);
~Controller();
void listHash()const;
void listTree()const;
void printTree()const;
void add(string key);
void remove(string key);
void searchByTicker(string key)const;
void searchByValue(string key);
void printStatistics()const;
void quit();
void printMaxInTree()const;
void printMinInTree()const;



};
#endif
