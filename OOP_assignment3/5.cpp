/*Write a function that will have income and tax rate as arguments and will return tax amount. In case tax rate is not provided it will be automatically taken as 10%. Call it with and without tax rate.*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

inline double tax(int income, double rate = 10.0){
  return income*rate/100;
}

int main()
{
 int income;double rate;
 cout<<"input income and rate(in percent): ";
 cin>>income>>rate;
 double tax_returns = tax(income,rate);
 cout<<fixed<<tax_returns<<endl;
 tax_returns = tax(income);
 cout<<fixed<<tax_returns<<endl;
 return 0;
}

