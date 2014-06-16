/// ctrl+F for ////
//read all comments
//what if the constructor found an error how can it return that
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

    ///private member functions declarations
	string getNthField(string str,int n,string seperator);
	/*
	   takes a generic array and the field with its colons
	   loop through array and set it
	*/
	template<typename T>
	string arrToString(T data[]);
	
	Stocks& copy(const Stocks&);//should it be constant?

	string comparableSTR() const;
	unsigned long long comparableLL() const;
	double comparableD() const;

	template<typename T>
	void setArrayField(T data[],string str);
//--------------------public functions declarations--------------------//
public:
	Stocks(){Ndays=0;}//do I really need this? its never going to get used
	Stocks(const Stocks&);///should it be constant?
	Stocks& operator = (const Stocks& rhs);///should it return const?
	Stocks(string line);//line read from file passed to this constructor to construct an object
	static void compareBy(string str){comparing=str;}

	string toString();//convert it back to string to the Breadth First Search can use it easily to output to the file
	bool add(double setclose,unsigned long long setmarketCap,unsigned long long setvolume,double high,double low,double open);
	bool add(string line);
// Comparison Operators
	bool operator == (const Stocks& rhs);
	bool operator >  (const Stocks& rhs);
	bool operator <  (const Stocks& rhs);
	bool operator <= (const Stocks& rhs);
	bool operator != (const Stocks& rhs);


//--------------GETTERS----------------------//
	///do i need to put const here?
	string gettickerSymbol()const {return tickerSymbol;}
	string getName()const {return name;}
	int getNdays() const {return Ndays;}
	//make sure in the function that the index is in bounds//
	bool getClose(double & ret,int ind=-1);
	bool getHigh(double & ret,int ind=-1);
	bool getLow(double & ret,int ind=-1);
	bool getOpen(double & ret,int ind=-1);
	bool getmarketCap(unsigned long long & ret,int ind=-1);
	bool getVolume(unsigned long long & ret,int ind=-1);


////////////////////SETTERS////////////////////////////
	void settickerSymbol(string set){tickerSymbol=set;}
	void setName(string set){name=set;}
	//make sure in the function that the index is in bounds//
	bool setClose(double set,int ind=-1);
	bool setHigh(double set,int ind=-1);
	bool setLow(double set,int ind=-1);
	bool setOpen(double set,int ind=-1);
	bool setmarketCap(unsigned long long  set,int ind=-1);
	bool setVolume(unsigned long long  set,int ind=-1);
	bool setBy(string field,string key);
};
#endif
