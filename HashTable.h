#include <iostream>
#include <fstream>
#include "Stocks.h"
#include "Queue.h"
#include <string>

using namespace std;


class HashTable{

public:

   bool find(Stocks* temp, Stocks*& returnTemp); //return refernce to object
   void sortedList();//pointer to a queue

   void hashStats();
   void List(Queue<Stocks*>& StockQueue);

   bool add(Stocks* temp);
   bool remove(Stocks*& returnTemp);


HashTable(int size);
~HashTable();


private:

int arrSize;
int maxProbe;
int numStocks;
int numZeroProbes;
int numCollisions;

  Stocks** hashArray;

  bool myFind(string key );
  int collRes(int indexRes, int numProbes);
  int indexGenerator( string ticker);

  bool isPrime(int arrSize);
  bool  _remove(string key);

};