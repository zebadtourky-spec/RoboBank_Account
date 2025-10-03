#ifndef CAL_H
#define CAL_H
#include <string>
#include <map>
using namespace std;
//=========== Function for Rounding ===========//
int Round (double value, bool Rounding );
//===========1-Balance Operations=============//
int apply_deposit(int balance, int amount );
int apply_withdrawal(int balance,int amount );
int apply_fee(int balance,unsigned int fee );
//===========2-Interest=============//
int simple_interest(int base, double apr, int days, int day_count_basis,bool Rounding);
int compound_amount(int principal, double apr, int years, int compounds_per_year,bool Rounding);
//===========3-Currency Conversion===========//
int fx_convert(int amount, string from_currency, string to_currency,map<string,double>fx_table,bool Rounding);
//===========4-Utilities===========//
int percent_of(int amount, double rate,bool Rounding);
bool validate_rate(double rate);
bool validate_non_negative(int amount);
#endif
