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
double prices[MAX_DAYS];
double high[MAX_DAYS];
double low[MAX_DAYS];
unsigned long long marketCap[MAX_DAYS];//why is that a long long not a double?
doube open[MAX_DAYS];
unsigned long long volume[MAX_DAYS];
double close[MAX_DAYS];


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
bool getPrice(double & ret,int ind);
bool getHigh(double & ret,int ind);
bool getLow(double & ret,int ind);
bool getOpen(double & ret,int ind);
bool getClose(double & ret,int ind);
bool getmarketCap(long long & ret,int ind);
bool getVolume(long long & ret,int ind);



////////////////////SETTERS////////////////////////////
void setTickerSymbol(string set){TickerSymbol=set;}
void setName(string set){name=set;}
//make sure in the function that the index is in bounds//
bool setPrice(double set,int ind);
bool setHigh(double set,int ind);
bool setLow(double set,int ind);
bool setOpen(double set,int ind);
bool setClose(double set,int ind);
bool setmarketCap(long long  set,int ind);
bool setVolume(long long  set,int ind);

};
#endif
