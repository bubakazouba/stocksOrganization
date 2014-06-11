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
	int size=numberOfRecords*1.5+17;
	cout<<"size= "<<size<<endl;
	table=new HashFunction(size);
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
	void Controller::List(){
		cout<<"Listing"<<endl;
	}
	void Controller::SearchByTicker(string key){
		Stocks* target=new Stocks;
		target->settickerSymbol(key);
		Stocks* returned;
		if(table->find(target,returned))
		{
			cout<<"Found Stock"<<endl;
			cout<<returned->toString()<<endl;// may throw seg error if find doesnt modify key properly
		}
		else{
			cout<<"Could not find Stock"<<endl;
		}
		delete target;
	}
	void Controller::SearchByValue(string price){
		
		Stocks* returned;
		Stocks* target=new Stocks();// needs some work , because of the staks
		//if(tree->getEntry(target,returned)){
			//cout<<"Found Stock"<<endl;
			//cout<<returned->toString()<<endl;
		//}
		//else{
			//cout<<"Could not find Stock"<<endl;
		//}
		delete target;
		
	}
	
	void Controller::Add(string key){
		cout<<"Adding"<<endl;
		Stocks* newStock=new Stocks;
		newStock->settickerSymbol(key);
		Stocks* returned;
		if(!table->find(newStock,returned))
		{
			cout<<"Enter Company Name:";
			string response="";
			getline(cin,response);
			table->add(newStock); 
			tree->insert(newStock);	
		}
		else{
			cout<<"Ups, the stock you are inserting already exists"<<endl;
			delete newStock;
		}
		
		
	}	
	void Controller::Remove(string key){
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
			controller.List();
		}
		else if (response=="d"){
			cout<<"Enter Ticker Symbol: ";
			getline(cin,response);
			controller.Remove(response);
		}
		else if (response=="a"){
			cout<<"Enter Ticker Symbol: ";
			getline(cin,response);
			controller.Add(response);
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
					controller.SearchByTicker(response);
				}
				else if (response=="p"){
					valid=true;
					cout<<"l. least in value"<<endl;
					cout<<"g. greater in value"<<endl;
					cout<<"Choice: ";
					getline(cin,response);
					controller.SearchByValue(response);
				}
			}
		}
		else if (response=="u"){
			controller.Update();
		}
		else if (response=="q"){
			bool sure=false;
			while(!sure){//while not sure
				cout<<"Are you sure? (y/n): ";
				getline(cin,response);
				if (response=="y"){
					sure=true;
					success=true;
					controller.Quit();
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

