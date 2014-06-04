//Name: Inaki Gonzalo

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <string>
#include "Stocks.h"
#include "Queue.h"
  
using namespace std;
class Controller{
private:
Queue<Stocks*>& readFile(string file);
Queue<Stocks*> StockQueue;


public:
Controller(string file);
~Controller();
void List();
void Remove(){}
void Search(){}
void Update(){}
void Quit(){}

};
#endif
