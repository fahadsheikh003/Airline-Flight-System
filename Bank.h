#pragma once
#include<iostream>

using namespace std;

class Bank
{
	long accID;
	double balance;
	string pin;

public:
	Bank();

	Bank(long, double, string);

	void setdata(long, double, string);

	long getaccID();

	void setbalance(double);

	double getbalance();

	string getpin();
};