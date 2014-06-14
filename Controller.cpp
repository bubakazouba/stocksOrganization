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
//#include "Memtracker.h"
//it leaks because the serialize function is not implemented yet.

string Stocks::comparing;

	int Controller::readFile(string file,Queue<Stocks*>& StockQueue){
		 string line;
		int counter=0;
		 ifstream myfile(file.c_str());
		 if (myfile.is_open())
		 {
			 while ( getline (myfile,line) )
			 {
				counter++;
				StockQueue.enqueue(new Stocks(line));
			 }
			 myfile.close();
		 }//end of if
		 else{ 
			 cout<<"Error reading file"<<endl;
		 }//end of else
		 return counter;
	 }//end of function readFile()
	 
	//Constructor 
	Controller::Controller(string file){
	Queue<Stocks*> queue;
	int numberOfRecords=readFile(file,queue);
	table=new HashFunction(numberOfRecords);
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
	void Controller::display(Stocks* temp){
		cout << fixed;
		cout << std::setprecision(2);
		cout<<"Company Name: "<<temp->getName();
		cout<<", Ticker: "<<temp->gettickerSymbol();
		double price;
		temp->getClose(price);
		cout<<", Price: $"<<price<<endl;
		unsigned long long market;
		temp->getmarketCap(market);
		cout<<"Market Cap: "<<market;
		unsigned long long volume;
		temp->getVolume(volume);
		cout<<", Volume: "<<volume;
		double open;
		temp->getOpen(open);
		cout<<", Open: "<<open;
		double close;
		temp->getClose(close);
		cout<<", Close: "<<close<<endl;
		double max=0,min=12344445556677;
		double prices[temp->getNdays()];
		for(int i=0;i<temp->getNdays();i++){
			temp->getClose(price,i);
			if (max<price)
				max=price;
			if (min>price)
				min=price;
			prices[i]=price;
		}
		int heightOfGraph=13;
		int maxDigits=9;
		double distribution=(max-min)/(heightOfGraph-1);
		int heights[temp->getNdays()];
		for(int i=0;i<temp->getNdays();i++){
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
			for(int a=0;a<temp->getNdays();a++){
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
		for(int a=0;a<temp->getNdays();a++){
				if(a==(temp->getNdays()/2)-1){
					cout<<"days";
				}
				else{
					cout<<"\u2015\u2015\u2015\u2015";//full width horizontal lines
					
				}
		}
		cout<<"\u2015\u2015>"<<endl;
		
		
	}
	void Controller::searchByTicker(string key){
		Stocks* target=new Stocks;
		target->settickerSymbol(key);
		Stocks* returned;
		if(table->find(target,returned))
		{
			cout<<"Found Stock"<<endl;
			//cout<<returned->toString()<<endl;// may throw seg error if find doesnt modify key properly
			display(returned);
		}
		else{
			cout<<"Could not find Stock"<<endl;
			
		}
		delete target;
	}
	void Controller::searchByValue(string price){
		
		Stocks* returned;
		Stocks* target=new Stocks();// needs some work , because of the staks
		//if(tree->getEntry(target,returned)){
			//cout<<"Found Stock"<<endl;
			//cout<<returned->toString()<<endl;
			//display(returned);
		//}
		//else{
			//cout<<"Could not find Stock"<<endl;
		//}
		delete target;
		
	}
	void Controller::listHash(){
		cout<<"Listing Hash"<<endl;
	}
	void Controller::listTree(){//inOrder
		cout<<"Listing tree"<<endl;
		
		} 
	void Controller::printTree(){ //breath first
		cout<<"printing tree"<<endl;
		
	}
	
	void Controller::add(string key){
		cout<<"Adding"<<endl;
		string args="";
		Stocks* target=new Stocks;
		target->settickerSymbol(key);
		Stocks* returned;
		if(!table->find(target,returned))
		{
			/////////////////////////////////////needs work
			
			cout<<"Enter Company Name:";
			string response="";
			getline(cin,response);
			args+=response;
			args+=":"+key;
			cout<<"Enter how many days of data:";
			int days=0;
			cin>>days;
			getline(cin,response);//gets garbage
			for (int n=0;n<days;n++){
				cout<<"Enter Closing Price:";
				getline(cin,response);
				args+=":"+response;
			}
			cout<<"Enter Market Capital:";
			getline(cin,response);
			args+=":"+response;
			
			cout<<"Enter Volume:";
			getline(cin,response);
			args+=":"+response;
			
			cout<<"Enter High:";
			getline(cin,response);
			args+=":"+response;
			
			cout<<"Enter Low:";
			getline(cin,response);
			args+=":"+response;
			
			cout<<"Enter Open:";
			getline(cin,response);
			args+=":"+response;
			
			cout<<args<<endl;
			Stocks* newStock=new Stocks(args);
			table->add(newStock); 
			tree->insert(newStock);	
		}
		else{
			cout<<"Ups, the stock you are inserting already exists"<<endl;
		}
		delete target;
	}	
	void Controller::remove(string key){
		cout<<"Removing"<<endl;
		Stocks* target=new Stocks;
		Stocks* returned;
		target->settickerSymbol(key);
		if(table->find(target,returned))
		{
			table->remove(returned); 
			tree->remove(returned);	
			delete returned;
		}
		else{
			cout<<"Ups,the Stock you are trying to delete doesnt exist"<<endl;
		}
		delete target;
		
		
	}
	
	void Controller::update(string key){
		cout<<"Updating"<<endl;
		Stocks* target=new Stocks;
		Stocks* returned;
		target->settickerSymbol(key);
		if(table->find(target,returned))
		{
			cout<<"Enter Company Name:";
			string response="";
			getline(cin,response);
			/////////////////////////////////////needs work
			table->remove(returned); 
			tree->remove(returned);	
			delete returned;
		}
		else{
			cout<<"Ups,the Stock you are trying to delete doesnt exist"<<endl;
		}
		delete target;
		
		
	}
	
		
	
	Controller::~Controller(){
		cout<<"destructor"<<endl;
		delete table;
		delete tree;
		
	}
	


int main(){
	Controller controller("bigDataDay1.cleaned");	
	bool success=false;
	string response="";
	while(!success){
		cout<<"a. add stocks"<<endl;
		cout<<"l. list stocks"<<endl;
		cout<<"d. delete stocks"<<endl;
		cout<<"s. search stocks"<<endl;
		cout<<"u. update stocks"<<endl;
		cout<<"q. quit"<<endl;
		cout<<"Choice: ";
		getline(cin,response);
		if(response=="l"){
			bool valid=false;
			while(!valid){//while not sure
				cout<<"List by:"<<endl;
				cout<<"t. Ticker Symbol"<<endl;
				cout<<"p. Current Price"<<endl;
				cout<<"Choice: ";
				getline(cin,response);
				if (response=="t"){
					valid=true;
					controller.listHash();
				}
				else if (response=="p"){
					valid=true;
					controller.listTree();
				}
			}
		}
		else if (response=="d"){
			cout<<"Enter Ticker Symbol: ";
			getline(cin,response);
			controller.remove(response);
		}
		else if (response=="a"){
			cout<<"Enter Ticker Symbol: ";
			getline(cin,response);
			controller.add(response);
		}
		else if (response=="s"){
			bool valid=false;
			while(!valid){//while not sure
				cout<<"Search by:"<<endl;
				cout<<"t. Ticker Symbol"<<endl;
				cout<<"p. Current Price"<<endl;
				cout<<"Choice: ";
				getline(cin,response);
				if (response=="t"){
					valid=true;
					cout<<"Enter Ticker Symbol:";
					getline(cin,response);
					controller.searchByTicker(response);
				}
				else if (response=="p"){
					valid=true;
					cout<<"l. least in value"<<endl;
					cout<<"g. greater in value"<<endl;
					cout<<"Choice: ";
					getline(cin,response);
					controller.searchByValue(response);
				}
			}
		}
		else if (response=="u"){
			cout<<"Enter Ticker Symbol: ";
			getline(cin,response);
			
			controller.update(response);
		}
		else if (response=="q"){
			bool sure=false;
			while(!sure){//while not sure
				cout<<"Are you sure? (y/n): ";
				getline(cin,response);
				if (response=="y"){
					sure=true;
					success=true;
					controller.quit();
				}//end of if
				else if (response=="n"){
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

