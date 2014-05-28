#ifndef _STOCKS_H_
#define _STOCKS_H_

const MAX_DAYS=30;
class Stocks{
private:
int Ndays;//number of days for that company(will calculate that from the 
sring TickerSymbol;
string Name;
Double[MAX_DAYS] Prices;
Double[MAX_DAYS] High;
Double[MAX_DAYS] Low;
unsigned long long[MAX_DAYS] MarketCap;//why is that a long long not a double?
Doube[MAX_DAYS] open;
unsigned long long Volume;
Double[MAX_DAYS] Close;


public:
Stocks();//do I really need this? its never going to get used
Stocks(Stocks&);
Stocks(string line);//line read from file passed to this constructor to construct an object
string toString();//convert it back to string to the Breadth First Search can use it easily to output to the file
operator ==(const Stocks& rhs);
operator > (const Stocks& rhs);
operator < (const Stocks& rhs);
operator = (const Stocks& rhs);

};
#endif