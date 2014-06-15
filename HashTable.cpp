#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "HashFunction.h"
#include "math.h"

using namespace std;

bool HashFunction::isPrime(int arrSize){

    int sqrtSize = sqrt (arrSize);
     for(int j=2; j<sqrtSize;j++){
            if ( arrSize%j == 0 && j != arrSize)
            return false;
        }

        return true;
}

HashFunction::HashFunction(int size){

	  arrSize=(size*2);
	  while( !isPrime(arrSize) ){
            arrSize++;
    }

	  maxProbe=0;
	  numStocks=0;
	  numZeroProbes=0;
	 numCollisions=0;

	hashArray=new Stocks*[arrSize];

	outfile.open("outTest1.txt");
	cout<<"Hash Constructor"<<endl;
	 for(int d=0;d<arrSize;d++){
       hashArray[d]=NULL;
   }

}

int HashFunction::collRes(int indexRes, int numProbes){

 indexRes=((indexRes +(numProbes*numProbes) )% arrSize);
 return indexRes;

}

int HashFunction::indexGenerator( string ticker){
       unsigned int b    = 13;//378551
       unsigned int a    = 11;//63689
	   int num=0;
   for( int i = 0; i < ticker.length(); i++){
       a  = a * b;
      num = ( (num + a) * (ticker[i]) )% arrSize;
   }
   return num;
}

bool HashFunction::myFind(string key  ){

	int indexToDelete=0;
	indexToDelete=indexGenerator(key);
	int probeCount=0;
	bool found=false;

	Stocks* removedStock=new Stocks;
	removedStock->settickerSymbol("deleted");

	while(!found){

	    //if(hashArray[indexToDelete]==NULL){return false;}
		//if(hashArray[indexToDelete]->gettickerSymbol()=="deleted"){return false;}
		if(hashArray[indexToDelete]->gettickerSymbol() == key){
                if(probeCount==0){numZeroProbes--;}else{numCollisions--;}
			hashArray[indexToDelete]=removedStock;
			cout<<"The index "<<indexToDelete<<" has been deleted"<<endl;
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

bool HashFunction::_remove(string key){

	if( myFind(key ) )
	return true;

	else {return false;}

}

bool HashFunction::remove(Stocks*& returnTemp){


	string key=returnTemp->gettickerSymbol();

	if(_remove(key) ){numStocks--;return true; }

	else return false;

}

bool HashFunction::find(Stocks* temp, Stocks*& returnTemp){

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

bool HashFunction:: add(Stocks* temp){
	bool success=true;
	string key=temp->gettickerSymbol();

	bool noSpot=true;
	int probes=0;
	int num=0;

	int index=indexGenerator(key);

	outfile<<key<<"  ";
    outfile<<"probes: ";

   while(noSpot){

       if( hashArray[index]==NULL ){
            hashArray[index]=temp;
            noSpot=false;
            outfile<<probes;

            if(probes==0){numZeroProbes++;}
       }
           else {
               probes++;
               index=collRes(index,probes);
			   numCollisions++;
           }
           if(maxProbe<probes){maxProbe=probes;}
   }//while

   outfile<<"   hashIndex:"<<index<<endl;

	if(success)
		numStocks++;
	return success;
}

void HashFunction::List(){
	_list();
}

void HashFunction::_list(){

	for(int i=0; i<arrSize; i++){
			if( hashArray[i]!= NULL && hashArray[i]->gettickerSymbol()!="DELETED" ){
			    cout<<hashArray[i]->toString()<<endl;
			}
	}//for loop


}//private list

void HashFunction::hashStats(){
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

HashFunction::~HashFunction(){
	delete hashArray;
	outfile.close();
}
