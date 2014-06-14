//Name: Inaki Gonzalo

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <string>
#include "Stocks.h"
#include "Queue.h"
#include "hashHeader.h"
#include "AVL.h"

  
using namespace std;
class Controller{
private:

int readFile(string file,Queue<Stocks*>& StockQueue);
HashFunction* table;
AVL<Stocks*>* tree;


public:
Controller(string file);
~Controller();
void listHash();
void listTree();
void printTree();
void display(Stocks* temp);
void add(string key);
void remove(string key);
void searchByTicker(string key);
void searchByValue(string key);
void printStatistics();
void update(string key);
void quit();

};
#endif
