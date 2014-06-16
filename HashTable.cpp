#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "HashTable.h"
#include <math.h>

using namespace std;

bool HashTable::isPrime(int arrSize){


   int sqrtSize = sqrt ((double)arrSize);
    for(int j=2; j<sqrtSize;j++){
           if ( arrSize%j == 0 && j != arrSize)
           return false;
       }

       return true;
}

HashTable::HashTable(int size){

 arrSize=(size*2);
 while( !isPrime(arrSize) ){
           arrSize++;
   }

 maxProbe=0;
 numStocks=0;
 numZeroProbes=0;
numCollisions=0;

hashArray=new Stocks*[arrSize];

for(int d=0;d<arrSize;d++){
      hashArray[d]=NULL;
  }

}

int HashTable::collRes(int indexRes, int numProbes){

indexRes=((indexRes +(numProbes*numProbes) )% arrSize);
return indexRes;

}

int HashTable::indexGenerator( string ticker){
      unsigned int b    = 13;//378551
      unsigned int a    = 11;//63689
  int num=0;
  for( int i = 0; i < ticker.length(); i++){
      a  = a * b;
     num = ( (num + a) * (ticker[i]) )% arrSize;
  }
  return num;
}

bool HashTable::myFind(string key  ){

int indexToDelete=0;
indexToDelete=indexGenerator(key);
int probeCount=0;
bool found=false;

Stocks* removedStock=new Stocks;
removedStock->settickerSymbol("deleted");

while(!found){

if(hashArray[indexToDelete]->gettickerSymbol() == key){
               if(probeCount==0){numZeroProbes--;}else{numCollisions--;}
hashArray[indexToDelete]=removedStock;
found=true;
}
else{
indexToDelete=collRes(indexToDelete, probeCount);
probeCount++;
}
if(probeCount>maxProbe){return false;}
}

return found;
}

bool HashTable::_remove(string key){

if( myFind(key ) )
return true;

else {return false;}

}

bool HashTable::remove(Stocks*& returnTemp){


string key=returnTemp->gettickerSymbol();

if(_remove(key) ){numStocks--;return true; }

else return false;

}

bool HashTable::find(Stocks* temp, Stocks*& returnTemp){

int probes=0;
bool found=false;
 cout<<endl;

 int somethingNew;
 string key=temp->gettickerSymbol();
 somethingNew = indexGenerator(key);

     while(!found){

 if(hashArray[somethingNew]==0){return false;}
 if(hashArray[somethingNew]->gettickerSymbol()=="deleted"){return false;}
         if(hashArray[somethingNew]->gettickerSymbol()==key ){

found=true;
 }
         else{
             probes++;// collisions counter
             somethingNew=collRes(somethingNew,probes);
         }

 if(probes>maxProbe){return false;}
     }
returnTemp=hashArray[somethingNew];
return found;
}

bool HashTable:: add(Stocks* temp){
bool success=true;
string key=temp->gettickerSymbol();

bool noSpot=true;
int probes=0;
int num=0;

int index=indexGenerator(key);

  while(noSpot){

      if( hashArray[index]==NULL ){
           hashArray[index]=temp;
           noSpot=false;
    
           if(probes==0){numZeroProbes++;}
      }
          else {
              probes++;
              index=collRes(index,probes);
  numCollisions++;
          }
          if(maxProbe<probes){maxProbe=probes;}
  }//while

if(success)
numStocks++;
return success;
}

void HashTable::List(Queue<Stocks*>& StockQueue){

for(int i=0; i<arrSize; i++){
		if( hashArray[i]!= NULL && hashArray[i]->gettickerSymbol()!="DELETED" ){
 
		  StockQueue.enqueue(hashArray[i]);

		}
	}//for loop
}


void HashTable::hashStats(){
cout<<endl;
cout<<"Array Size: "<<arrSize<<endl;
cout<<"MaxProbe: "<<maxProbe<<endl;
cout<<"Number of Stocks : "<< numStocks<<endl;
cout<<"Keys with no collisions: "<<numZeroProbes<<endl;
cout<<"Percentage of data with no collisions: "<< (((double)numZeroProbes/numStocks)*100)<<"%"<<endl;
//cout<<"Number of zero probes : "<< numZeroProbes<<endl;
cout<<"Number of collisons : "<< numCollisions<<endl;
cout<<"LOAD FACTOR: "<< (((double)numStocks/arrSize)*100)<<"%"<<endl;
cout<<endl;
}

HashTable::~HashTable(){
delete [] hashArray;

}