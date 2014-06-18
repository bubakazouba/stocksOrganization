//Tariq Anees
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "HashTable.h"
#include <math.h>

using namespace std;

		/*
	isPrime:	This function takes the length and checks if it is prime 

	Parameters:		This takes the initial length of the array

	Returns:		true if the parameter is prime and false if parameter is false
	*/
    bool HashTable::isPrime(int arrLength){ //given an arrSize that could be prime or non prime

        int sqrtSize = (int)sqrt((double)arrLength);
        for(int j=2; j<= sqrtSize;j++){
            if ( arrLength%j == 0 )// determines if the number is not prime
                return false;
        }
        return true;
    }
		/*
	Constructor:	This function initialises all the private members 

	Parameters:		This takes the index which is the number of records

	Returns:		nothing
	*/

    HashTable::HashTable(int size){

        arrSize=(size*2); // size is the number of records, so that number is doubled to get an array that is twice the # of records
        while( !isPrime(arrSize) ){
            arrSize++;//keeps incrementing the arrsize until the array size is prime
       }
         maxProbe=0;
         numStocks=0;
         numZeroProbes=0;
         numCollisions=0;
		 parallelArray = new int[arrSize];

        hashArray=new Stocks*[arrSize]; //creating an array of pointers to objects

        for(int d=0;d<arrSize;d++){
            hashArray[d]=NULL;
			parallelArray[d] = 0;
        }

    }
	/*
	collRes:		This function uses quadratic probe to get a new index

	Parameters:		This takes the index that must be changed and the number of probes

	Returns:		 The new index
	*/
    int HashTable::collRes(int indexRes, int numProbes){

            indexRes=((indexRes +(numProbes*numProbes) )% arrSize); // this a quadratic probes
            return indexRes;
    }

		/*
		HashFunction:	This function takes a key and hashes it 

		Parameters:		This takes the string which gets hashed

		Returns:		an index
		*/

    int HashTable::indexGenerator( string& ticker){
        unsigned long int b = 13;// trial and error with prime numbers
        unsigned long int a = 11;// trial and error with prime numbers
        int num=0;
            for( int i = 0; i < ticker.length(); i++){
                a *= b;
                num = ( (num + a) * (ticker[i]) )%arrSize;
            }
            return num;
    }

	/*
		HashFunction:	

		Parameters:		

		Returns:		
		*/
	int HashTable::findNewMaxProbe(){
		int newMax = 0;

		for (int i=0;i <arrSize;i++){
			if(parallelArray[i] > newMax)
				newMax = parallelArray[i];
		}
		return newMax;
	}

	/*
		private find:	this function searches the key in the array 

		Parameters:		This takes the string which gets hashed

		Returns:		true if the key exists and false if it doesn't
	*/
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

                    if(probeCount==0){
						numZeroProbes--;
					}else{
						numCollisions--;
					} // if the record to delete did not need a collision resolution to be found than the numZeroProbes is decremented
					
					hashArray[indexToDelete]=removedStock; // now if we want to delete the same object, we will know that it has been removed
					int isitMax = parallelArray[indexToDelete]; 

					parallelArray[indexToDelete]=0; 
					//keeps track of all the indexs with the highest probe
					
					if(isitMax == maxProbe){
						maxProbe = findNewMaxProbe();
					}
					
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

	/*
		_remove:	    the public remove calls this private remove

		Parameters:		This takes the string and sends it to the private find function called myFind

		Returns:		true if the key exists and false if it does not

	*/
    bool HashTable::_remove(string key){

        if( myFind(key ) )
            return true;
        else {
            return false;
        }

    }

	/*
		remove:	    This function  decrements the number of stocks if the key is being removed

		Parameters:	This takes a pointer object by reference

		Returns:	true if the key exists
		*/
    bool HashTable::remove(Stocks*& returnTemp){

        string key=returnTemp->gettickerSymbol();
        if(_remove(key) ){
            --numStocks;
            return true;
        }
        else
        return false;

    }


	/*
		Find:	      This function looks for a key 

		Parameters:		This takes a pointer to an object with one field and takes a second object by reference which gets modified

		Returns:		true if the key exists
		*/
    bool HashTable::find(Stocks* temp, Stocks*& returnTemp){

        int probes=0;
        bool found=false;
        string key=temp->gettickerSymbol();

		int somethingNew=0;
        somethingNew = indexGenerator(key);

         while(!found){

            if(hashArray[somethingNew]==0){return false;} //checks to see if the index is empty
           // if(hashArray[somethingNew]->gettickerSymbol()=="deleted"){return false;}
            if(hashArray[somethingNew]->gettickerSymbol()==key ){
                found=true;
            }
            else{
            probes++;// collisions counter
            somethingNew=collRes(somethingNew,probes);
        }

        if(probes > maxProbe){return false;} // stop searching for the key if collision resolution has been called more than the max probe
        }
            returnTemp=hashArray[somethingNew];
            return found;
    }


	/*
		Add:	This function checks to see if space is left w/inthe array to add. Also it adds all the keys and updates 
				private members such as numStocks and numZerOProbes

		Parameters:		This takes the object with all the fields

		Returns:		boolean
	*/
    bool HashTable:: add(Stocks* temp){
        if(numStocks==arrSize)
            return false;
        string key=temp->gettickerSymbol();

        bool noSpot=true;
        int probes=0;
        int num=0;
		int index=0;

         index=indexGenerator(key);

          while(noSpot){

            if( hashArray[index]==NULL || hashArray[index]->gettickerSymbol()=="deleted" ){
                hashArray[index]=temp;
                noSpot=false;
				parallelArray[index]=probes; //keeps track of all the indexs with the highest probe
				if(probes==maxProbe){
				}
                if(probes==0){numZeroProbes++;}
                else
                    numCollisions++;
            }

            else {
                probes++;
                index=collRes(index,probes);
            }
            if(maxProbe<probes){
                maxProbe=probes;
            } // maxProbe is getting modified
          }//while
        numStocks++;
        return true;
    }


	
	/*
		List:	This function adds objects to a queue if the hashArray is pointing to an object that is not deleted

		Parameters:		This takes a pointer to a referenced Queue

		returns:		updates the queue/ but is a void function
	*/

    void HashTable::List(Queue<Stocks*>& StockQueue){

        for(int i=0; i<arrSize; i++){
            if( hashArray[i]!= NULL && hashArray[i]->gettickerSymbol()!="deleted" ){
              StockQueue.enqueue(hashArray[i]); //add the indexs with data into a queue

            }
        }//for loop
    }

	
	/*
		STATS:	ThIS FUNction prints all the stats of the program

		Parameters:		uses private data members

		Returns:		void
	*/
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
		delete [] parallelArray;

    }