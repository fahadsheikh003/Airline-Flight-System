#pragma once
#include<iostream>

using namespace std;

class Airplane;

class Runway
{
	int id;
	string name;
	bool status;
	Airplane* current;

public:
	Runway();

	void setdata(int, string);

	void setstatus(bool);

	bool getstatus();

	void setairplane(Airplane&);

	Airplane* getairplane();
};