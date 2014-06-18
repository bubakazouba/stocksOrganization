//Header file for Stocks class
//Name: Abdulrahman Sahmoud

#ifndef _STOCKS_H_
#define _STOCKS_H_
#include <string>
#include <sstream>
using namespace std;
const int MAX_DAYS=30;//where to put that .cpp or .h? in private or outside
class Stocks{
	
private:	
	static string comparing;
	int Ndays;//number of days for that company(will calculate that from the line im going to get)
	string name;
	string tickerSymbol;
	unsigned long long marketCap[MAX_DAYS],volume[MAX_DAYS];
	double high[MAX_DAYS],low[MAX_DAYS],open[MAX_DAYS],close[MAX_DAYS];

    /*
    private function thats used by other functions for easier accessibility for arrays
    it returns a string containing the nth field of a big string passed to the function, it also takes the seperator as a parameter since there are fields seperated by commas
    and inner fields seperated by colons
    */
	string getNthField(string str,int n,string seperator);
	/*
	   takes a generic array and the field with its colons
	   loop through array and set it
	*/
	template<typename T>
	string arrToString(T data[]);
	
	/*
	copy constructor
	*/
	Stocks& copy(const Stocks&);

	/*
	returns the value of the comparing field, there are three function because there are 3 data types for the private fields the class contains
	*/
	string comparableSTR() const;
	unsigned long long comparableLL() const;
	double comparableD() const;

	/*
	the function takes an array and modify it, it takes a string containing the inner fields delimited by colons, it seperates them and insert to the array
	*/
	template<typename T>
	void setArrayField(T data[],string str);
//--------------------public functions declarations--------------------//
public:
	Stocks(){Ndays=0;}
	Stocks(const Stocks&);
	/*
	equal operator overloader
	*/
	Stocks& operator = (const Stocks& rhs);
	/*
	constructor for the class, takes a line from the file and seperates the fields and assign them to the member variables
	*/
	Stocks(string line);
	/*
	setters and getters for the compare by value
	*/
	static void compareBy(string str){comparing=str;}
	static string getCompareBy(){return comparing;}
	/*
	convert it back to string to the Breadth First Search can use it easily to output to the file
	*/
	string toString();
	/*
	add function that adds one day to the stocks with all the array fields as paramaters
	*/
	bool add(double setclose,unsigned long long setmarketCap,unsigned long long setvolume,double high,double low,double open);
	/*
	add function works like the one above but takes a string instead
	*/
	bool add(string line);
// Comparison Operators
	bool operator == (const Stocks& rhs);
	bool operator >  (const Stocks& rhs);
	bool operator <  (const Stocks& rhs);
	bool operator <= (const Stocks& rhs);
	bool operator != (const Stocks& rhs);


////////////////////GETTERS////////////////////////////
	bool getBy(string key,string & field);
	string gettickerSymbol()const {return tickerSymbol;}
	string getName()const {return name;}
	int getNdays() const {return Ndays;}
	bool getClose(double & ret,int ind=-1);
	bool getHigh(double & ret,int ind=-1);
	bool getLow(double & ret,int ind=-1);
	bool getOpen(double & ret,int ind=-1);
	bool getmarketCap(unsigned long long & ret,int ind=-1);
	bool getVolume(unsigned long long & ret,int ind=-1);
////////////////////SETTERS////////////////////////////
	void settickerSymbol(string set){tickerSymbol=set;}
	void setName(string set){name=set;}
	bool setClose(double set,int ind=-1);
	bool setHigh(double set,int ind=-1);
	bool setLow(double set,int ind=-1);
	bool setOpen(double set,int ind=-1);
	bool setmarketCap(unsigned long long  set,int ind=-1);
	bool setVolume(unsigned long long  set,int ind=-1);
	bool addFirstDayBy(string field,string key);
};
#endif