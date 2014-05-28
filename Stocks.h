//Name: Abdulrahman Sahmoud
#include <string>
#ifndef _STOCKS_H_
#define _STOCKS_H_

const MAX_DAYS=30;
class Stocks{
private:
	//Ndays wont have a setter
int Ndays;//number of days for that company(will calculate that from the line im going to get)
string TickerSymbol;
string name;
Double[MAX_DAYS] prices;
Double[MAX_DAYS] high;
Double[MAX_DAYS] low;
unsigned long long[MAX_DAYS] marketCap;//why is that a long long not a double?
Doube[MAX_DAYS] open;
unsigned long long[MAX_DAYS]volume;
Double[MAX_DAYS] close;


public:
Stocks();//do I really need this? its never going to get used
Stocks(Stocks&);
Stocks(string line);//line read from file passed to this constructor to construct an object
string toString();//convert it back to string to the Breadth First Search can use it easily to output to the file
operator ==(const Stocks& rhs);
operator > (const Stocks& rhs);
operator < (const Stocks& rhs);
operator = (const Stocks& rhs);
operator != (const Stocks& rhs);
///////////////////GETTERS////////////////////////////////
string getTickerSymbol()const {return TickerSymbol;}
string getName()const {return name;}
//make sure in the function that the index is in bounds//
bool getPrice(double & ret,int ind){}
bool getHigh(double & ret,int ind){}
bool getLow(double & ret,int ind){}
bool getOpen(double & ret,int ind){}
bool getClose(double & ret,int ind){}
bool getmarketCap(long long & ret,int ind){}
bool getVolume(long long & ret,int ind){}
/////////////////////////////////////////////////////////
};
#endif