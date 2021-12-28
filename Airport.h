#pragma once
#pragma once
#include<iostream>

using namespace std;

class Runway;
class Flight_Schedule;

class Airport
{
	int id;
	string name;
	Runway* runways;
	const int runsize;
	Flight_Schedule** flights;
	int flightsize;

public:
	Airport();

	void setdata(int, string);

	void addflight(Flight_Schedule&);
	
	void displayboard();
	
	~Airport();
};