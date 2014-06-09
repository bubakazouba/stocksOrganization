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
void readFile(string file,Queue<Stocks*>& StockQueue);



public:
//Controller(string file);
Controller(string file,HashFunction& table);
~Controller();
void List();
void Add();
void Remove(){}
void Search(string mode,string key,HashFunction& table);
void Update(){}
void Quit(){}

};
#endif
