#pragma once
#include<iostream>

using namespace std;

class Travel_History
{
	int day;
	int month;
	int year;
	int ndays;
	string location;

public:
	Travel_History();

	Travel_History(int d, int m, int y, int n, string loc);
};