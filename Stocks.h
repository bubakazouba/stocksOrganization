//Name: Abdulrahman Sahmoud
#include <string>
#ifndef _STOCKS_H_
#define _STOCKS_H_

const MAX_DAYS=30;
class Stocks{
private:
int Ndays;//number of days for that company(will calculate that from the line im going to get)
string TickerSymbol;
string name;
Double prices[MAX_DAYS];
Double high[MAX_DAYS];
Double low[MAX_DAYS];
unsigned long long marketCap[MAX_DAYS];//why is that a long long not a double?
Doube open[MAX_DAYS];
unsigned long long volume[MAX_DAYS];
Double close[MAX_DAYS];


public:
Stocks();//do I really need this? its never going to get used
Stocks(Stocks&);
Stocks(string line);//line read from file passed to this constructor to construct an object


string toString();//convert it back to string to the Breadth First Search can use it easily to output to the file

// Comparison Operators
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



////////////////////SETTERS////////////////////////////
};
#endif
