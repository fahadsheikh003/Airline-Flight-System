#pragma once
#include<iostream>

using namespace std;

class Payment
{
	int perhour;
	int gstper;
	double totalcost;
	double totaltax;


public:
	void setinitialdata(int, int);

	void setfinaldata(double, double);

	double getseatprice();
};