#include <iostream>
#include <fstream>
#include "Stocks.h"
#include "Queue.h"
#include <string>

using namespace std;


class HashFunction{


public:

    bool find(Stocks* temp, Stocks*& returnTemp); //return refernce to object
    void list();//pointer to a queue
    void sortedList();//pointer to a queue

    void hashStats();
	void List();

    bool add(Stocks* temp);
    bool remove(Stocks*& returnTemp);


	HashFunction(int size);
	~HashFunction();


private:

	int arrSize;
	int maxProbe;
	int numStocks;
	int numZeroProbes;
	int numCollisions;

   Stocks** hashArray;
   ofstream outfile;

   bool myFind(string key );
   int collRes(int indexRes, int numProbes);
   int indexGenerator( string ticker);
   bool isPrime(int arrSize);

   bool  _find(Stocks* temp );
   void  _list(); //makes sure array is not empty
   void  _sortedList(); //
   void  _hashStats();
   bool  _remove(string key);
   void _add();

};
