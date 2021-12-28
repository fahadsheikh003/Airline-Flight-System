#pragma once
#include<iostream>

using namespace std;

class Airport;
class Airplane;

class City
{
	int id;
	string name;
	Airport* airports;
	Airplane* planes;

public:
	City();

	void setdata(int, string);

	Airport getairport(int);

	Airplane getplane(int);

	void displayplanes();
};