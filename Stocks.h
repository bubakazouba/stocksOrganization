/// ctrl+F for ////
//read all comments
//what if the constructor found an error how can it return that
//Name: Abdulrahman Sahmoud

#ifndef _STOCKS_H_
#define _STOCKS_H_
#include <string>
using namespace std;
const int MAX_DAYS=30;//where to put that .cpp or .h? in private or outside
class Stocks{
	
private:	
	static string comparing;///change to static
	int Ndays;//number of days for that company(will calculate that from the line im going to get)
	string name;
	string tickerSymbol;
	unsigned long long marketCap[MAX_DAYS],volume[MAX_DAYS];
	double high[MAX_DAYS],low[MAX_DAYS],open[MAX_DAYS],close[MAX_DAYS];

    ///private member functions declarations
	string getNthField(string str,int n,string seperator);
	/*
	   bya5od generic array wel field bel colons bta3to
	   yshof homa kam field law aktar men MAX_FIELDS ydy false
	   yeloop w yeset el array law 3ada max_days yexit
	*/
	template<typename T>
	string arrToString(T data[]);

	Stocks& copy(const Stocks&);//should it be constant?

	string comparableSTR();
	long long comparableLL();
	double comparableD();

	template<typename T>
	void setArrayField(T data[],string str);
//--------------------public functions declarations--------------------//
public:
	Stocks(){}//do I really need this? its never going to get used
	Stocks(const Stocks&);///should it be constant?
	Stocks(string line);//line read from file passed to this constructor to construct an object
	static void compareBy(string str){comparing=str;}

	string toString();//convert it back to string to the Breadth First Search can use it easily to output to the file

// Comparison Operators
	bool operator ==( Stocks& rhs);
	bool operator > ( Stocks& rhs);
	bool operator < (Stocks& rhs);
	bool operator <= (Stocks& rhs);
	Stocks& operator = (const Stocks& rhs);///should it return const?
	bool operator != (Stocks& rhs);


//--------------GETTERS----------------------//
	//do i need to put const here?
	string gettickerSymbol()const {return tickerSymbol;}
	string getName()const {return name;}
	int getNdays() const {return Ndays;}
	//make sure in the function that the index is in bounds//
	bool getClose(double & ret,int ind);
	bool getHigh(double & ret,int ind);
	bool getLow(double & ret,int ind);
	bool getOpen(double & ret,int ind);
	bool getmarketCap(long long & ret,int ind);
	bool getVolume(long long & ret,int ind);


////////////////////SETTERS////////////////////////////
	void settickerSymbol(string set){tickerSymbol=set;}
	void setName(string set){name=set;}
	//make sure in the function that the index is in bounds//
	bool setClose(double set,int ind);
	bool setHigh(double set,int ind);
	bool setLow(double set,int ind);
	bool setOpen(double set,int ind);
	bool setmarketCap(long long  set,int ind);
	bool setVolume(long long  set,int ind);

};
#endif
