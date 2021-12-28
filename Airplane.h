#pragma once
#pragma once
#include<iostream>

using namespace std;

class Flight_Schedule;

class Airplane
{
	int id;
	string name;
	Flight_Schedule* current;

public:
	Airplane();

	Airplane(const Airplane&);

	void setdata(int, string);

	int getid();

	string getname();

	void setflight(Flight_Schedule&);
};