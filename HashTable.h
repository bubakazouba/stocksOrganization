//Tariq Anees

#include <iostream>
#include <fstream>
#include "Stocks.h"
#include "Queue.h"
#include <string>

using namespace std;


class HashTable{

public:

   bool find(Stocks* temp, Stocks*& returnTemp); //return refernce to object so that the Controller can delete the object inside array

   void hashStats(); // outputs the stats
   void List(Queue<Stocks*>& StockQueue);// a queue is implemented 

   bool add(Stocks* temp); // temp is an object with one key field
   bool remove(Stocks*& returnTemp); //return gets modified with the actual data of the object


HashTable(int size); //size is the # data records
~HashTable();


private:


int* parallelArray;
int arrSize;//these 5 variables are updatted as remove and add are called
int maxProbe;
int numStocks;
int numZeroProbes;
int numCollisions;

  Stocks** hashArray;

  bool myFind(string key ); //private find function used only by the remove, it has less error checks
  int collRes(int indexRes, int numProbes);
  int indexGenerator( string& ticker);

  int findNewMaxProbe();

  bool isPrime(int arrLength);
  bool  _remove(string key);

};