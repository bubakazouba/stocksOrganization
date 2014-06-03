/*
these comments are for me
put that in the copy constructor:Ndays=rhs.Ndays;
remove the const comments
Ndays++; in the add function that should be after the setting not before
add ind=-1 for all the setters and getters
change the operator overloaders to const and change comparableStrs to consts too
in the testing driver test the add(string)
*/
#include<iostream>
using namespace std;
#include "stocks.h"
string Stocks::comparing;
int main(){
	Stocks::compareBy("tickerSymbol");
	Stocks test1("1347 Property Insurance Holdings Inc,PIH,8.9,30998700,11500,9.19,8.5,8.91");
	Stocks test2("1347 Property Insurance Holdings Inc,PIH,9.0,20998700,11501,8.19,8.6,8.91");
	//Stocks test[100];
	
	string str;
	int n;
	double tmp;
	unsigned long long tmpll;
	int ind=0;
	for(;;){
		cout<<"enter your option:(input ? for options available)";
		cin>>str;
		if(str=="?"){
			cout<<"getnth  setnth  tostring add < <= > != == comp = exit"<<endl;
		}
		if(str=="exit")return 0;
		if(str=="getnth"){
			cout<<"field:";cin>>str;
			if(str=="tickerSymbol")
				cout<<test1.gettickerSymbol()<<endl;
			if(str=="name")
				cout<<test1.getName()<<endl;
			if(str=="close"){
				cout<<"n:";cin>>n;
				cout<<test1.getClose(tmp,n)<<endl;
				cout<<tmp<<endl;
			}
			if(str=="open"){
				cout<<"n:";cin>>n;
				cout<<test1.getOpen(tmp,n)<<endl;
				cout<<tmp<<endl;
			}
			if(str=="high"){
				cout<<"n:";cin>>n;
				cout<<test1.getHigh(tmp,n)<<endl;
				cout<<tmp<<endl;
			}
			if(str=="low"){
				cout<<"n:";cin>>n;
				cout<<test1.getLow(tmp,n)<<endl;
				cout<<tmp<<endl;
			}
			if(str=="volume"){
				cout<<"n:";cin>>n;
				cout<<test1.getVolume(tmpll,n)<<endl;
				cout<<tmpll<<endl;
			}
			if(str=="marketCapital"){
				cout<<"n:";cin>>n;
				cout<<test1.getmarketCap(tmpll,n)<<endl;
				cout<<tmpll<<endl;
			}
		}//end of get Nth
		if(str=="setnth"){
			cout<<"field:";cin>>str;
			if(str=="tickerSymbol"){
				cout<<"new value:";cin>>str;
				test1.settickerSymbol(str);
			}
			if(str=="tickerSymbol"){
				cout<<"new value:";cin>>str;
				test1.setName(str);
			}
			if(str=="close"){
				cout<<"new value:";cin>>tmp;
				cout<<"n:";cin>>n;
				test1.setClose(tmp,n);
			}
			if(str=="open"){
				cout<<"new value:";cin>>tmp;
				cout<<"n:";cin>>n;
				test1.setOpen(tmp,n);
			}
			if(str=="high"){
				cout<<"new value:";cin>>tmp;
				cout<<"n:";cin>>n;
				test1.setHigh(tmp,n);
			}
			if(str=="low"){
				cout<<"new value:";cin>>tmp;
				cout<<"n:";cin>>n;
				test1.setLow(tmp,n);
			}
			if(str=="marketCapital"){
				cout<<"new value:";cin>>tmp;
				cout<<"n:";cin>>n;
				test1.setmarketCap(tmpll,n);
			}
			if(str=="volume"){
				cout<<"new value:";cin>>tmp;
				cout<<"n:";cin>>n;
				test1.setVolume(tmpll,n);
			}
		}//end of setNth
		if(str=="tostring"){
			cout<<test1.toString()<<endl;
		}
		if(str=="add"){
			double close,high,low,open;
			unsigned long long mar,vol;
			cin>>close>>mar>>vol>>high>>low>>open;
			test1.add(close,mar,vol,high,low,open);
		}
		if(str=="<"){
			cout<<(test1<test2)<<endl;
		}
		if(str=="=="){
			cout<<(test1==test2)<<endl;
		}
		if(str==">"){
			cout<<(test1>test2)<<endl;
		}
		if(str=="<="){
			cout<<(test1<=test2)<<endl;
		}
		if(str=="!="){
			cout<<(test1!=test2)<<endl;
		}
		if(str.find("comp")!=-1){
			cout<<"field:";cin>>str;
			test1.compareBy(str);
		}
		if(str=="="){
			test1=test2;
			cout<<"done"<<endl;
		}


	}
	return 0;
}