/* Inaki Gonzalo
 * 
 * Controller.cpp
 * 
 * Copyright 2014 Unknown <tom@panda>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <stdio.h>
#include "Controller.h"
#include <fstream>
#include <iomanip>
#include "Memtracker.h"
string Stocks::comparing;

/*
readFile: 	This function reads records from a file, creates objects that are dynamically 
* allocated and stores the pointers in a queue.


Parameters: It takes a string as the name of the input file and a queue to temporarily store
* the stocks pointers.

Return Value: 	Returns a int value, that represents the amount of records in the file.


*/

	int Controller::readFile(string file,Queue<Stocks*>& StockQueue){
		 string line;
		 bool done=false;
		int counter=0;
		ifstream myfile2("inputFile");
		while(!done){
			 ifstream myfile(file.c_str());
			
			 if (myfile2.is_open())
			 {
				 while ( getline (myfile2,line) )
				 {
					counter++;
					StockQueue.enqueue(new Stocks(line));
				 }
				 
				 done=true;
			 }//end of if
			 else if (myfile.is_open())
			 {
				 while ( getline (myfile,line) )
				 {
					counter++;
					StockQueue.enqueue(new Stocks(line));
				 }
				 myfile.close();
				 done=true;
			 }//end of if
			 else{ 
				 cout<<"Error reading file"<<endl;
				 cout<<"Enter new file:";
				 getline(cin,file);
				 
			 }//end of else
		}//end while
		myfile2.close();
		 return counter;
	 }//end of function readFile()
	 
	 /*
Controller::Controller:  Reads the input file and initializes the HashTable and the AVL tree.


Parameters: It takes a string as the name of the input file and field to sort the AVL by.

Return Value: Its a constructor


*/
	 
	//Constructor 
	Controller::Controller(string file,string comp){
	comparing=comp;
	Queue<Stocks*> queue;
	int numberOfRecords=readFile(file,queue);
	table=new HashTable(numberOfRecords);
	tree=new AVL<Stocks*>();
		for (int i=0;i<queue.size();i++){
			Stocks* temp;
			queue.peek(temp);
			tree->insert(temp);
			table->add(temp);
			queue.dequeue();
			queue.enqueue(temp);
		}
	}
/*
display:  Print to screen a graphical representation of the stock.


Parameters: It takes a pointer to the Stock you wnat to display

Return Value: void


*/
	
	
	void display(Stocks* temp){
		cout << fixed;
		cout << std::setprecision(2);
		cout<<"Company Name: "<<temp->getName();
		cout<<", Ticker: "<<temp->gettickerSymbol();
		double price;
		temp->getClose(price);
		cout<<", Price: $"<<price;
		double open;
		temp->getOpen(open);
		cout<<", Open: "<<open<<endl;
		unsigned long long market;
		temp->getmarketCap(market);
		cout<<"Market Cap: "<<market;
		unsigned long long volume;
		temp->getVolume(volume);
		cout<<", Volume: "<<volume;
		double high;
		temp->getHigh(high);
		cout<<", High: "<<high;
		double low;
		temp->getLow(low);
		cout<<", Low: "<<low<<endl;
		double max=0,min=12344445556677;
		//double* prices=new double[temp->getNdays()];
		vector<double> prices;
		for(int i=0;i<temp->getNdays();i++){
			temp->getClose(price,i);
			if(price!=0){
				if (max<price)
					max=price;
				if (min>price)
					min=price;
				prices.push_back(price);
			}
		}
		int heightOfGraph=13;
		int maxDigits=9;
		double distribution=(max-min)/(heightOfGraph-1);
		int* heights=new int[prices.size()];
		for(unsigned int i=0;i<prices.size();i++){
			heights[i]=((prices[i]-min)/distribution);	
		}
		for (int i=heightOfGraph;i>-1;i--){
			if(i==heightOfGraph){
				cout << setfill (' ') <<setw(maxDigits);
				cout<<max<<" \u2227";//uparrow
				
			}
			else if(i==((heightOfGraph)/2)){//print price halfway in the graph
				cout<<"    price "<<"\u2502";//vertical bar
			}		
			else{
				cout<<"          "<<"\u2502";//vertical bar
			}
			for(unsigned int a=0;a<prices.size();a++){
				cout<<"   ";
				if(heights[a]>=i){
					cout<<"\u2593";//graybox
				}
				else{
					cout<<" ";//so that the days dont phase put
				}
			}
			cout<<endl;
		}
		cout << setfill (' ') <<setw(maxDigits);
		cout<<min<<" \u2514";//corner
		for(int a=0;a<prices.size();a++){
				if(a==(prices.size()/2)-1){
					cout<<"days";
				}
				else{
					cout<<"\u2015\u2015\u2015\u2015";//full width horizontal lines
					
				}
		}
		cout<<"\u2015\u2015>"<<endl;//full width horizontal lines
		delete [] heights;
	}
/*
Controller::searchByTicker:  searches the Hash table using a ticker as key and
* displays the stock to screen. 

Parameters: It takes a string that represents a ticker symbol;
* 
Return Value: void


*/
	void Controller::searchByTicker(string key)const{
		Stocks* target=new Stocks;
		target->settickerSymbol(key);
		Stocks* returned;
		if(table->find(target,returned))
		{
			display(returned);
		}
		else{
			cout<<"Could not find Stock"<<endl;		
		}
		delete target;
	}
/*
Controller::searchByValue:  searches the AVL tree using the passed parameter as key and
* displays the stock to screen. 

Parameters: It takes a string that represents the value of the field the tree is sorted by;
* 
Return Value: void


*/
	void Controller::searchByValue(string key){
		
		vector<Stocks*> returned;
		Stocks* target=new Stocks();
		target->addFirstDayBy(comparing,key);
		if(tree->getEntry(target,returned)){
			if(returned.size()>0){
				for (int i=0;i<returned.size();i++)
					display(returned[i]);
			}
		}
		else{
			cout<<"Could not find Stock"<<endl;
		}
		delete target;
	}
	
/*
Controller::listHash():  Gets all the stocks pointers from Hashed table int array order 
* and displays them to screen. 

Parameters: It takes a string that represents the value of the field the tree is sorted by;
* 
Return Value: void


*/
	void Controller::listHash()const{
		Queue<Stocks*> queue; 
		table->List(queue);
		while(queue.size()!=0){
			Stocks* temp;
			queue.peek(temp);
			display(temp);
			queue.dequeue();
		}	
		
	}
/*
Controller::visit(): displays to screen all the stocks from a vector of stocks

Parameters: It takes a vector of type Stocks pointer
* 
Return Value: void


*/
	void visit(vector<Stocks*>& vec){
		for (int i=0;i<vec.size();i++){
			display(vec[i]);
		}
	}
/*
Controller::listTree(): displays to screen all the stocks from the 
* AVL tree in key Order

Parameters: none
* 
Return Value: void

*/
	void Controller::listTree()const{//inOrder
		tree->inOrder(visit);
	} 
/*
Controller::printTree(): displays to screen all the stocks from the 
* AVL tree in tree shape

Parameters: none
* 
Return Value: void

*/
	void Controller::printTree()const{ //breath first
		tree->printIndented();
	}

/*
Controller::printStatistics(): displays to screen the Hash table Statistics

Parameters: none
* 
Return Value: void

*/	
	void Controller::printStatistics()const{ //print hashtable statistics
		table->hashStats();
	}
	
	/*
Controller::greaterThanOrEq: displays to screen Stocks that are greater then key

Parameters: string that represents the key
* 
Return Value: void

*/	
	void Controller::greaterThanOrEq(string response)const{
		Stocks* temp=new Stocks();
		temp->addFirstDayBy(comparing,response);
		tree->greaterThanOrEq(visit,temp);
		delete temp;
	}
	
	/*
Controller::lessThanOrEq(: displays to screen  Stocks that are less then key

Parameters: string that represents the key
* 
Return Value: void

*/	
	void Controller::lessThanOrEq(string response)const{ //print hashtable statistics
		Stocks* temp=new Stocks();
		temp->addFirstDayBy(comparing,response);
		tree->lessThanOrEq(visit,temp);
		delete temp;
	}
/*
Controller::printMaxInTree(): displays to screen the list of Stocks whith the highest
* key value in the AVL tree

Parameters: none
* 
Return Value: void

*/	
	void Controller::printMaxInTree()const{
		vector<Stocks*> vec;
		tree->getMax(vec);
		for (int i=0;i<vec.size();i++)
			display(vec[i]);
	}
/*
Controller::printMinInTree(): displays to screen the list of Stocks whith the least
* key value in the AVL tree

Parameters: none
* 
Return Value: void

*/	
	void Controller::printMinInTree()const{
		vector<Stocks*> vec;
		tree->getMin(vec);
		for (int i=0;i<vec.size();i++)
			display(vec[i]);
	}
/*
getInput: appends an intput to a string

Parameters: int for number of days, string args ,string output a meesage to user
* 
Return Value: void

*/	
	void getInput(int n,string& args, string output){
		cout<<output<<"(Day "<<n+1<<"): ";
		string response="";
		getline(cin,response);
		if(n==0){
			args=response;
		}
		else{
			args+=":"+response;
		}
	}
/*
Controller::add: wait for user to input , create a Stocks object whith dynamic memory 
* and a pass a pointer of it to the AVL tree and the hash table

Parameters: a string that represents a ticker symbol
* 
Return Value: void

*/		
	void Controller::add(string key){
		string args="";
		Stocks* target=new Stocks;
		target->settickerSymbol(key);
		Stocks* returned;
		if(!table->find(target,returned))
		{
			cout<<"Enter Company Name:";
			string response="";
			getline(cin,response);
			args+=response;
			args+=","+key;
			cout<<"Enter how many days of data:";
			int days=0;
			bool ok = false;
			while (!ok)
			{ 
				cin >> days;
				if(!cin.fail() && (cin.peek()==EOF || cin.peek()=='\n'))
				{
					ok = true;
				}
				else
				{
					cout<<"Enter how many days of data:";
				}
				cin.clear();
				cin.ignore(256,'\n');
			}
			string prices="";
			string marketCap="";
			string volumes="";
			string highs="";
			string lows="";
			string opens="";
			for (int n=0;n<days;n++){
				getInput(n,prices, "Enter Closing Price");
				getInput(n,marketCap, "Enter Market Capital");
				getInput(n,volumes, "Enter Volume");
				getInput(n,highs, "Enter High");
				getInput(n,lows, "Enter Low");
				getInput(n,opens, "Enter Open");
			}
			args+=","+prices;
			args+=","+marketCap;
			args+=","+volumes;
			args+=","+highs;
			args+=","+lows;
			args+=","+opens;
			Stocks* newStock=new Stocks(args);
			table->add(newStock); 
			tree->insert(newStock);	
		}
		else{
			cout<<"Ups, the stock you are inserting already exists"<<endl;
		}
		delete target;
	}	
/*
Controller::remove: remove an an item from the tree and the hashed table
* and deleting the dynamic memory of the object.

Parameters: a string that represents a ticker symbol
* 
Return Value: void

*/	
	void Controller::remove(string key){
		Stocks* target=new Stocks;
		Stocks* returned;
		target->settickerSymbol(key);
		if(table->find(target,returned))
		{
			table->remove(returned); 
			vector<Stocks*> vec;
			 tree->getEntry(returned,vec); 
			 for (int i=0;i<vec.size();i++){
				 if(vec[i]->gettickerSymbol()==returned->gettickerSymbol()){
					 vec.erase(vec.begin()+i);
				 }
			 }
			 tree->replace(returned,vec); 
			cout<<key<<" was removed"<<endl;
			delete returned;
		}
		else{
			cout<<"Ups,the Stock you are trying to delete doesnt exist"<<endl;
		}
		delete target;
	}
/*
Controller::quit: serializes the tree, prints it to a file and deletes the dynamic memory of every 
* Stocks object

Parameters: none
* 
Return Value: void

*/	
	void Controller::quit(){
		Queue<Stocks*> queue;
		tree->serialize(queue);
		//table->List(queue);
		ofstream outfile("inputFile");
		while(queue.size()!=0){
			Stocks* temp;
			queue.peek(temp);
			if (outfile)
			{
				outfile<<temp->toString()<<endl;
			}
			delete temp;
			queue.dequeue();
		}	
		outfile.close();
	}
	/*
Controller::~Controller:delete table and tree 

Parameters: none
* 
Return Value: void

*/	
	Controller::~Controller(){
		delete table;
		delete tree;
	}
     bool operator<( vector<Stocks*> v1,vector<Stocks*> v2){
            return *v1[0]<*v2[0];
    }
    bool operator==( vector<Stocks*> v1,vector<Stocks*> v2){
            return *v1[0]==*v2[0];
    }
    bool operator>( vector<Stocks*> v1,vector<Stocks*> v2){
            return *v1[0]>*v2[0];
    }
    bool operator<=( vector<Stocks*> v1,vector<Stocks*> v2){
            return *v1[0]<=*v2[0];
    }
    bool operator!=( vector<Stocks*> v1,vector<Stocks*> v2){
            return *v1[0]!=*v2[0];
    }
/*
main:Interfece with the user.
Parameters: none

*/	
int main(){
	bool success=false;
	string response="";
	string comparing;
	cout<<"Welcome to this awesome program..."<<endl;
	
	while(!success){
			
		cout<<"Enter a field to sort the tree"<<endl;
		cout<<"n. Company Name"<<endl;
		cout<<"s. Ticker Symbol"<<endl;
		cout<<"p. Price"<<endl;
		cout<<"v. Volume"<<endl;
		cout<<"c. Market Capital"<<endl;
		cout<<"o. Opening Price"<<endl;
		cout<<"h. High"<<endl;
		cout<<"l. Low"<<endl;
		cout<<"Choice: ";
		getline(cin,response);
		
		if(response=="n"||response=="N"){
			Stocks temp;
			comparing="Company Name";
			temp.compareBy(comparing);
			success=true;
		}
		else if (response=="s"||response=="S"){
			Stocks temp;
			comparing="Ticker Symbol";
			temp.compareBy(comparing);
			success=true;
		}
		else if (response=="p"||response=="P"){
			Stocks temp;
			comparing="Price";
			temp.compareBy(comparing);
			success=true;
		}
		else if (response=="v"||response=="V"){
			Stocks temp;
			comparing="Volume";
			temp.compareBy(comparing);
			success=true;
		}
		else if (response=="c"||response=="C"){
			Stocks temp;
			comparing="Market Capital";
			temp.compareBy(comparing);
			success=true;	
		}
		else if (response=="o"||response=="O"){
			Stocks temp;
			comparing="Opening Price";
			temp.compareBy(comparing);
			success=true;
		}
		else if (response=="h"||response=="H"){
			Stocks temp;
			comparing="High";
			temp.compareBy(comparing);
			success=true;
		}
		else if (response=="l"||response=="L"){
			Stocks temp;
			comparing="Low";
			temp.compareBy(comparing);
			success=true;
		}
	}
	success=false;
	//Controller controller("inputfile.txt",comparing);
	Controller controller("miniInputFile",comparing);
	while(!success){
		cout<<"a. add stock"<<endl;
		cout<<"d. delete stock"<<endl;
		cout<<"l. list stocks"<<endl;
		cout<<"s. search stock"<<endl;
		cout<<"h. print hash statistics"<<endl;
		cout<<"q. quit"<<endl;
		cout<<"Choice: ";
		getline(cin,response);
		if(response=="l"){
			bool valid=false;
			while(!valid){//while not sure
				cout<<"List by:"<<endl;
				cout<<"t. Ticker Symbol(Hash order)"<<endl;
				cout<<"p. "<<comparing<<"(Tree in order)"<<endl;
				cout<<"s. Tree shape"<<endl;
				cout<<"g. Greater than or esqual to input("<<comparing<<")"<<endl;
				cout<<"l. Less than or equal to input("<<comparing<<")"<<endl;
				cout<<"Choice: ";
				getline(cin,response);
				if (response=="t"||response=="T"){
					valid=true;
					controller.listHash();
				}
				else if (response=="p"||response=="P"){
					valid=true;
					controller.listTree();
				}
				else if (response=="s"||response=="S"){
					valid=true;
					controller.printTree();
				}
				else if (response=="g"||response=="G"){
					cout<<"Value: ";
					getline(cin,response);
					controller.greaterThanOrEq(response);
					
					valid=true;
					controller.printTree();
				}
				else if (response=="l"||response=="L"){
					cout<<"Value: ";
					getline(cin,response);
					controller.lessThanOrEq(response);
					
					valid=true;
					controller.printTree();
				}
			}
		}
		else if (response=="d"||response=="D"){
			cout<<"Enter Ticker Symbol: ";
			getline(cin,response);
			controller.remove(response);
		}
		else if (response=="a"||response=="A"){
			cout<<"Enter Ticker Symbol: ";
			getline(cin,response);
			controller.add(response);
		}
		else if (response=="s"||response=="S"){
			bool valid=false;
			while(!valid){//while not sure
				cout<<"Search by:"<<endl;
				cout<<"t. Ticker Symbol"<<endl;
				cout<<"p. "<<comparing<<endl;
				cout<<"Choice: ";
				getline(cin,response);
				if (response=="t"){
					valid=true;
					cout<<"Enter Ticker Symbol:";
					getline(cin,response);
					controller.searchByTicker(response);
				}
				else if (response=="p"||response=="P"){
					
					while(!valid){//while not sure
						cout<<"l. least in value"<<endl;
						cout<<"g. greater in value"<<endl;
						cout<<"c. custom value"<<endl;
						cout<<"Choice: ";
						getline(cin,response);
						if(response=="c"||response=="C"){
							cout<<"Enter custom value: ";
							getline(cin,response);
							controller.searchByValue(response);
							valid=true;
						}
						else if(response=="l"||response=="L"){
							controller.printMinInTree();
							valid=true;
							
						}
						else if(response=="g"||response=="G"){
							controller.printMaxInTree();
							valid=true;
							
						}
					}//end of while	
				}//end of else if (response=="p")
			}//end of while valid
		}
		
		else if (response=="h"||response=="H"){
			controller.printStatistics();
		}
		else if (response=="q"||response=="Q"){
			bool sure=false;
			while(!sure){//while not sure
				cout<<"Are you sure? (y/n): ";
				getline(cin,response);
				if (response=="y"||response=="Y"){
					sure=true;
					success=true;
					controller.quit();
				}//end of if
				else if (response=="n"||response=="N"){
					sure=true;
					success=false;
				}//end of else if
			}	//end of while
		}//end of else if
		else{
			cout<<"l, d, u, s or q only"<<endl;
		}
	}
	 return 0;
 }
