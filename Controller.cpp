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
#include "Stocks.h"
#include <fstream>



	Queue<Stocks*>& Controller::readFile(string file){
		 string line;
		 ifstream myfile(file);
		 if (myfile.is_open())
		 {
			 while ( getline (myfile,line) )
			 {
				StockQueue.enqueue((new Stocks(line)));
			 }
			 myfile.close();
		 }//end of if
		 else{ 
			 cout<<"Error reading file"<<endl;
		 }//end of else
		 
		 return StockQueue;
	 }//end of function readFile()
	 
	//Constructor 
	Controller::Controller(string file){
	readFile(file);
		//Tree tree();
		//HashTable table();
		
	}
	void Controller::List(){
		cout<<"Listing"<<endl;
		for (int i=0;i<StockQueue.size();i++){
			Stocks* temp;
			StockQueue.peek(temp);
			cout<<temp<<endl;
			StockQueue.dequeue();
			StockQueue.enqueue(temp);
		}
		
	}
	Controller::~Controller(){
		cout<<"destructor"<<endl;
		for (int i=0;i<StockQueue.size();i++){
			Stocks* temp;
			StockQueue.peek(temp);
			StockQueue.dequeue();
			delete temp;
		}
		
	}
	


int main(){
	
	Controller controller("bigDataDay1.cleaned");	
	bool success=false;
	string response="";
	while(!success){
	cout<<endl;
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
		controller.Remove();
	}
	else if (response=="s"){
		controller.Search();
	}
	else if (response=="u"){
		controller.Update();
	}
	else if (response=="q"){
		success=true;
	}
	else{
		cout<<"l, d, u, s or q only"<<endl;
	}
		
	}
	 return 0;
 }

