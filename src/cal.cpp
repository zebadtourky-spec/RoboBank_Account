#include "cal.h"
#include <cmath>
#include <string>
#include <map>
using namespace std;
//=========== Function for Rounding ===========//
int Round (double value, bool Rounding){
  return Rounding ?round(value):nearbyint(value);
   }
//===========1-Balance Operations=============//
int apply_deposit(int balance,int amount ){
 return balance+amount;
}

int apply_withdrawal(int balance,int amount ){
 return balance-amount;
}
int apply_fee (int balance,unsigned int fee ){
 return balance-fee;
}
//===========2-Interest=============//
int simple_interest(int base, double apr, int days, int day_count_basis, bool Rounding){
 double interest=base*(apr)*((double)days/day_count_basis);

 return Round(interest,Rounding);}
int compound_amount(int principal, double apr, int years, int compounds_per_year,bool Rounding)
{
 double amount = principal * pow(1.0 + (apr) / compounds_per_year, compounds_per_year * years);

return Round(amount, Rounding);}

//===========3-Currency Conversion===========//

int fx_convert(int amount, string from_currency, string to_currency,map<string,double>fx_table,bool Rounding)
{  if(fx_table.find(from_currency) == fx_table.end() || fx_table.find(to_currency) == fx_table.end())
   return 0;

    double converted = amount * (fx_table[to_currency]/fx_table[from_currency]);
     return Round(converted,Rounding);
}
//===========4-Utilities===========//
int percent_of(int amount, double rate,bool Rounding){
double portion = amount * rate;
 return Round(portion,Rounding);
}
bool validate_rate(double rate){
     return (rate >= 0.0 && rate <= 1.0);

}
bool validate_non_negative(int amount){
 return (amount >= 0);

}
