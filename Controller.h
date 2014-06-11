//Name: Inaki Gonzalo

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <string>
#include "Stocks.h"
#include "Queue.h"
#include "hashHeader.h"

  
using namespace std;
class Controller{
private:

int readFile(string file,Queue<Stocks*>& StockQueue);
HashFunction* table;


public:
//Controller(string file);
Controller(string file);
~Controller();
void List();
void Add(string key);
void Remove(string key);
void SearchByTicker(string key);
void SearchByValue(string key);
void Update(){}
void Quit(){}

};
#endif
