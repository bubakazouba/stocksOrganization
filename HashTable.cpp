#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "HashTable.h"
#include <math.h>

using namespace std;

    bool HashTable::isPrime(int arrSize){ //given an arrSize that could be prime or non prime

        int sqrtSize = sqrt ((double)arrSize);
        for(int j=2; j<= sqrtSize;j++){
            if ( arrSize%j == 0 )// determines if the number is not prime
                return false;
        }

        return true;
    }

    HashTable::HashTable(int size){

        arrSize=(size*2); // size is the number of records, so that number is doubled to get an array that is twice the # of records
        while( !isPrime(arrSize) ){
            arrSize++;//keeps incrementing the arrsize until the array size is prime
       }

         maxProbe=0;
         numStocks=0;
         numZeroProbes=0;
         numCollisions=0;

        hashArray=new Stocks*[arrSize]; //creating an array of pointers to objects

        for(int d=0;d<arrSize;d++){
            hashArray[d]=NULL;
        }

    }

    int HashTable::collRes(int indexRes, int numProbes){

            indexRes=((indexRes +(numProbes*numProbes) )% arrSize); // this a quadratic probes
            return indexRes;
    }

    int HashTable::indexGenerator( string ticker){
        unsigned int b = 13;// trial and error with prime numbers
        unsigned int a = 11;// trial and error with prime numbers
        int num=0;
            for( int i = 0; i < ticker.length(); i++){
                a *= b;
                num = ( (num + a) * (ticker[i]) )%arrSize;
            }
            return num ;
    }

    bool HashTable::myFind(string key  ){

    int indexToDelete=0;
    indexToDelete=indexGenerator(key); // the string is given an index
    int probeCount=0;
    bool found=false;

    Stocks* removedStock=new Stocks;
    removedStock->settickerSymbol("deleted");

        while(!found){
                //no need to check if the the index is empty because that check has already been done in controller class
            if(hashArray[indexToDelete]->gettickerSymbol() == key){
                    if(probeCount==0){numZeroProbes--;}else{numCollisions--;} // if the record to delete did not need a collision resolution to be found than the numZeroProbes is decremented
                    hashArray[indexToDelete]=removedStock; // now if we want to delete the same object, we will know that it has been removed
                    found=true;
            }
            else{
                indexToDelete=collRes(indexToDelete, probeCount);
                probeCount++;
            }
            if(probeCount>maxProbe){
                return false;
            } //stop searching for an  object if collision res has been called more than max number of probes
        }//while

    return found;
}

    bool HashTable::_remove(string key){

        if( myFind(key ) )
            return true;

        else {
            return false;
        }

    }

    bool HashTable::remove(Stocks*& returnTemp){

        string key=returnTemp->gettickerSymbol();
        if(_remove(key) ){
            numStocks--;
            return true;
        }

        else
        return false;

    }

    bool HashTable::find(Stocks* temp, Stocks*& returnTemp){

        int probes=0;
        bool found=false;

        int somethingNew;
        string key=temp->gettickerSymbol();
        somethingNew = indexGenerator(key);

         while(!found){

            if(hashArray[somethingNew]==0){return false;} //checks to see if the index is empty
            if(hashArray[somethingNew]->gettickerSymbol()=="deleted"){return false;}
            if(hashArray[somethingNew]->gettickerSymbol()==key ){

                found=true;
            }
            else{
            probes++;// collisions counter
            somethingNew=collRes(somethingNew,probes);
        }

        if(probes>maxProbe){return false;} // stop searching for the key if collision resolution has been called more than the max probe
        }
            returnTemp=hashArray[somethingNew];
            return found;
    }

    bool HashTable:: add(Stocks* temp){
        if(numStocks==arrSize)
            return false;
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
            if(maxProbe<probes){
                maxProbe=probes;
            } // maxProbe is getting modified

          }//while
        numStocks++;
        return true;
    }

    void HashTable::List(Queue<Stocks*>& StockQueue){

        for(int i=0; i<arrSize; i++){
            if( hashArray[i]!= NULL && hashArray[i]->gettickerSymbol()!="DELETED" ){
              StockQueue.enqueue(hashArray[i]); //add the indexs with data into a queue

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
