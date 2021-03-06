//you need that outside the main: string Stocks::comparing= "tickerSymbol";
//Name: Abdulrahman Sahmoud
#ifndef _STOCKS
#define _STOCKS
#include <sstream>
#include <iostream>
#include "Stocks.h"

using namespace std;

//string,string,double ,long long,long long,double,double,double
//Name  ,Symbol,close  ,MarketCap,Volume   ,High   ,Low  ,Open
//1     , 2    , 3     , 4       , 5       , 6     , 7   , 8  
bool Stocks::add(string line){
	if(Ndays==MAX_DAYS)
		return false;
	
	stringstream ss;
	for(int i=1;i<=6;i++)
		ss<<getNthField(line,i,",")<<" ";

	ss>>close[Ndays];
	ss>>marketCap[Ndays];
	ss>>volume[Ndays];
	ss>>high[Ndays];
	ss>>low[Ndays];
	ss>>open[Ndays];
	Ndays++;
	return true;
}

bool Stocks::add(double newclose,unsigned long long newmarketCap,unsigned long long newvolume,double newhigh,double newlow,double newopen){
	if(Ndays==MAX_DAYS)
		return false;
	cout<<"Ndays="<<Ndays<<endl;
	close[Ndays]=newclose;
	marketCap[Ndays]=newmarketCap;
	volume[Ndays]=newvolume;
	high[Ndays]=newhigh;
	low[Ndays]=newlow;
	open[Ndays]=newopen;
	Ndays++;
	return true;
}
	string Stocks::comparableSTR() const{
		if(comparing=="Company Name")
			return name;
		if(comparing=="Ticker Symbol")
			return tickerSymbol;
		return "";
	}
	unsigned long long Stocks::comparableLL() const{
		if(comparing=="Volume")
			return volume[Ndays-1];
		if(comparing=="Market Capital")
			return marketCap[Ndays-1];
		return -1;
	}
	double Stocks::comparableD() const{
		if(comparing=="Price")
			return close[Ndays-1];
		if(comparing=="Opening Price")
			return open[Ndays-1];
		if(comparing=="High")
			return high[Ndays-1];
		if(comparing=="Low")
			return low[Ndays-1];
		return -1;
	}
//----------------------------------------------------------------------//
	string Stocks::getNthField(string line,int n,string seperator){
		for(int i=0;i<n-1;i++)
			line=line.substr(line.find(seperator)+1);
		
		return line.substr(0,line.find(seperator));
	}
//----------------------------------------------------------------------//
	template<typename T>
	void Stocks::setArrayField(T data[],string str){
		int ind=0;
		for(int i=0;i<str.size();i++){
			stringstream ss;
			while(i!=str.size()&&str[i]!=':'){
				ss<<str[i++];
			}
			ss>>data[ind++];
			
		}
	}
//----------------------------------------------------------------------//
	Stocks& Stocks::copy(const Stocks & rhs){
		Ndays=rhs.Ndays;
		name=rhs.name;
		tickerSymbol=rhs.tickerSymbol;
		setArrayField(close,arrToString(rhs.close));
		setArrayField(marketCap,arrToString(rhs.marketCap));
		setArrayField(volume,arrToString(rhs.volume));
		setArrayField(high,arrToString(rhs.high));
		setArrayField(low,arrToString(rhs.low));
		setArrayField(open,arrToString(rhs.open));
		return *this;
	}
//----------------------------------------------------------------------//
	Stocks::Stocks(const Stocks& rhs){
		copy(rhs);
	}
	Stocks& Stocks::operator = (const Stocks& rhs){
		return copy(rhs);
	}
//----------------------------------------------------------------------//
	Stocks::Stocks(string line){
		//set Ndays first
		Ndays=1;
		string tmp=getNthField(line,3,",");
		for(int i=0;i<tmp.size();i++)
			if(tmp[i]==':')
				Ndays++;
		if(Ndays>MAX_DAYS)Ndays=MAX_DAYS;
		//setting the rest of the fields
		name=getNthField(line,1,",");
		tickerSymbol=getNthField(line,2,",");
		setArrayField( close, getNthField(line,3,",") );
		setArrayField( marketCap, getNthField(line,4,",") );
		setArrayField( volume, getNthField(line,5,",") );
		setArrayField( high, getNthField(line,6,",") );
		setArrayField( low, getNthField(line,7,",") );
		setArrayField( open, getNthField(line,8,",") );
	}//end of Stocks(line)
	template<typename T>
	string Stocks::arrToString(T data[]){
		string str;
		for(int i=0;i<Ndays;i++){
			stringstream ss;
			ss<<data[i];
			str+=ss.str()+":";
		}
		return str.substr(0,str.size()-1);
	}
	string Stocks::toString(){
		string str;
		str+=name+",";
		str+=tickerSymbol+",";
		str+=arrToString(close)+",";
		str+=arrToString(marketCap)+",";
		str+=arrToString(volume)+",";
		str+=arrToString(high)+",";
		str+=arrToString(low)+",";
		str+=arrToString(open);
		return str;
	}

// Comparison Operators
	bool Stocks::operator ==(const Stocks& rhs){
		if(comparing=="Company Name" || comparing=="Ticker Symbol")
			return comparableSTR()==rhs.comparableSTR();
		if(comparing=="Opening Price"||comparing=="Price"||comparing=="High"||comparing=="Low"){
			cout<<comparableD()<<" "<<rhs.comparableD()<<endl;
			return comparableD()==rhs.comparableD();
		}
		if(comparing=="Volume"||comparing=="Market Capital")
			return comparableLL()==rhs.comparableLL();
		return false;
	}
	bool Stocks::operator > (const Stocks& rhs){
		if(comparing=="Company Name" || comparing=="Ticker Symbol")
			return comparableSTR()>rhs.comparableSTR();
		if(comparing=="Opening Price"||comparing=="Price"||comparing=="High"||comparing=="Low")
			return comparableD()>rhs.comparableD();
		if(comparing=="Volume"||comparing=="Market Capital")
			return comparableLL()>rhs.comparableLL();
		return false;	
	}
	bool Stocks::operator <= (const Stocks& rhs){
		if(comparing=="Company Name" || comparing=="Ticker Symbol")
			return comparableSTR()<=rhs.comparableSTR();
		if(comparing=="Opening Price"||comparing=="Price"||comparing=="High"||comparing=="Low")
			return comparableD()<=rhs.comparableD();
		if(comparing=="Volume"||comparing=="Market Capital")
			return comparableLL()<=rhs.comparableLL();
		return false;
	}
	bool Stocks::operator < (const Stocks& rhs){
		if(comparing=="Company Name" || comparing=="Ticker Symbol")
			return comparableSTR()<rhs.comparableSTR();
		if(comparing=="Opening Price"||comparing=="Price"||comparing=="High"||comparing=="Low")
			return comparableD()<rhs.comparableD();
		if(comparing=="Volume"||comparing=="Market Capital")
			return comparableLL()<rhs.comparableLL();
		return false;
	}
	bool Stocks::operator != (const Stocks& rhs){
		if(comparing=="Company Name" || comparing=="Ticker Symbol")
			return comparableSTR()!=rhs.comparableSTR();
		if(comparing=="Opening Price"||comparing=="Price"||comparing=="High"||comparing=="Low")
			return comparableD()!=rhs.comparableD();
		if(comparing=="Volume"||comparing=="Market Capital")
			return comparableLL()!=rhs.comparableLL();
		return false;
	}
	

//---------------------GETTERS-----------------------------//
    bool Stocks::getBy(string key,string & field){
		if(key=="Company Name"){
			field=name;
			return true;
		}
		if(key=="Ticker Symbol"){
			field=tickerSymbol;
			return true;
		}
		if(Ndays==0)return false;
		stringstream ss;
		if(key=="Market Capital"){
			ss<<marketCap[Ndays-1];
			ss>>field;
			return true;
		}
		if(key=="Volume"){
			ss<<volume[Ndays-1];
			ss>>field;
			return true;
		}
		if(key=="Price"){
			ss<<close[Ndays-1];
			ss>>field;
			return true;
		}
		if(key=="Opening Price"){
			ss<<open[Ndays-1];
			ss>>field;
			return true;
		}
		if(key=="High"){
			ss<<high[Ndays-1];
			ss>>field;
			return true;
		}
		if(key=="Low"){
			ss<<low[Ndays-1];
			ss>>field;
			return true;
		}
		return false;
	}
	bool Stocks::getClose(double & ret,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		ret=close[ind];
		return true;
	}
	bool Stocks::getHigh(double & ret,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		ret=high[ind];
		return true;
	}
	bool Stocks::getLow(double & ret,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		ret=low[ind];
		return true;
	}
	bool Stocks::getOpen(double & ret,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		ret=open[ind];
		return true;
	}
	bool Stocks::getmarketCap(unsigned long long & ret,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		ret=marketCap[ind];
		return true;
	}
	bool Stocks::getVolume(unsigned long long & ret,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		ret=volume[ind];
		return true;
	}
//-----------------SETTERS---------------------------------//
	bool Stocks::setClose(double set,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		close[ind]=set;
		return true;
	}
	bool Stocks::setHigh(double set,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		high[ind]=set;
		return true;
	}
	bool Stocks::setLow(double set,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		low[ind]=set;
		return true;
	}
	bool Stocks::setOpen(double set,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		open[ind]=set;
		return true;
	}
	bool Stocks::setmarketCap(unsigned long long  set,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		marketCap[ind]=set;
		return true;
	}
	bool Stocks::setVolume(unsigned long long  set,int ind){
		if(Ndays==0)
			return false;
		if(ind==-1)
			ind=Ndays-1;
		if(ind<0||ind>Ndays-1)
			return false;
		volume[ind]=set;
		return true;
	}
	bool Stocks::addFirstDayBy(string field,string key){
		Ndays=1;
		stringstream ss(key);
		if(field=="Company Name"){
			name=key;
			return true;
		}
		if(field=="Ticker Symbol"){
			tickerSymbol=key;
			return true;
		}
		if(field=="Volume"){
			ss>>volume[0];
			return true;
		}
		if(field=="Market Capital"){
			ss>>marketCap[0];
			return true;
		}
		if(field=="Price"){
			ss>>close[0];
			return true;
		}
		if(field=="Opening Price"){
			ss>>open[0];
			return true;
		}
		if(field=="High"){
			ss>>high[0];
			return true;
		}
		if(field=="Low"){
			ss>>low[0];
			return true;
		}
		return false;
	}

#endif