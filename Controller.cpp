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

string Stocks::comparing;

	void Controller::readFile(string file,Queue<Stocks*>& StockQueue){
		 string line;
		 ifstream myfile(file.c_str());
		 if (myfile.is_open())
		 {
			
			 while ( getline (myfile,line) )
			 {
				StockQueue.enqueue(new Stocks(line));
			 }
			 myfile.close();
		 }//end of if
		 else{ 
			 cout<<"Error reading file"<<endl;
		 }//end of else
		 
	 }//end of function readFile()
	 
	//Constructor 
	Controller::Controller(string file,HashFunction& table){
	//Controller::Controller(string file,Tree& tree, HashTable& table){
	//readFile(file);
	Queue<Stocks*> queue;
	readFile(file,queue);
		//for (int i=0;i<StockQueue.size();i++){
			//Stocks* temp;
			//queue.peek(temp);
			//tree.insert(temp);
			//table.add(temp);
			//queue.dequeue();
			//queue.enqueue(temp);
		//}
		
		
	}
	void Controller::List(){
		cout<<"Listing"<<endl;
		
	}
	void Controller::SearchByTicker(string key,HashFunction& table){
		Stocks temp;
		temp.settickerSymbol(key);
		if(table.find(temp))
		{
			cout<<"Found Stock"<<endl;
			cout<<temp.toString()<<endl;
		}
		else{
			cout<<"Could not find Stock"<<endl;
		}
	}
	void Controller::SearchByValue(string key,HashFunction& table){
		
		Stocks* temp;
		
		//if(tree.getEntry(new Stocks(key),temp)){
			//cout<<"Found Stock"<<endl;
			//cout<<temp->toString()<<endl;
		//}
		//else{
			//cout<<"Could not find Stock"<<endl;
		//}
		
	}
	
	
	
	
	void Controller::Add(string key,HashFunction& table){
		cout<<"Adding"<<endl;
		Stocks temp;
		temp.settickerSymbol(key);
		if(!table.find(temp))
		{
			//table.addObj(&temp); //insert the addreass right?
			//tree.insert(&temp);	//insert the addreass right?
		}
		else{
			cout<<"Ups, the stock you are inserting already exists"<<endl;
		}
		
		
	}	
	void Controller::Remove(string key,HashFunction& table){
		cout<<"Removing"<<endl;
		Stocks temp;
		temp.settickerSymbol(key);
		if(table.find(temp))
		{
			//table.deleteRecord(&temp); //insert the addreass right?
			//tree.remove(&temp);	//insert the addreass right?
		}
		else{
			cout<<"Ups,the Stock you are trying to delete doesnt exist"<<endl;
		}
		
		
	}
		
	
	Controller::~Controller(){
		cout<<"destructor"<<endl;
		//for (int i=0;i<StockQueue.size();i++){
			//Stocks* temp;
			//StockQueue.peek(temp);
			//StockQueue.dequeue();
			//delete temp;
		//}
		
	}
	


int main(){
	//BinarySearchTree tree;  //Should i mke the tree and table private to the controller?
	HashFunction table;
	//Controller controller("bigDataDay1.cleaned");
	//Controller controller("bigDataDay1.cleaned",tree,table);	
	Controller controller("bigDataDay1.cleaned",table);	
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
			controller.Remove(response,table);
		}
		else if (response=="a"){
			cout<<"Enter Ticker Symbol: ";
			getline(cin,response);
			controller.Add(response,table);
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
					controller.SearchByTicker(response,table);
				}
				else if (response=="p"){
					valid=true;
					cout<<"l. least in value"<<endl;
					cout<<"g. greater in value"<<endl;
					cout<<"Choice: ";
					getline(cin,response);
					controller.SearchByValue(response,table);
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
				}
				else if (response=="n"){
					sure=true;
					success=false;
				}
			}
			
			
		}
		else{
			cout<<"l, d, u, s or q only"<<endl;
		}
		
	}
	 return 0;
 }

