#pragma once
#include<iostream>
#include"Person.h"
#include"Bank.h"

using namespace std;

class Person;
class Travel_History;
class Flight_Schedule;

class Passenger :public Person
{
	int vsize;
	Travel_History* visits;
	string* visa;
	int visasize;
	Flight_Schedule** tickets_reserved;
	int flightsize;
	Bank account;

public:
	Passenger();

	Passenger(string, long long, string, string, string);

	void setaccount();

	void makeNULL();

	bool uniquevisa(string);

	void addvisa(string);

	void displayflights();

	void addticket(Flight_Schedule*);

	int findflightindex(int);

	void cancelflight();

	void addvisit();

	string* getvisa();

	int getvisasize();

	Bank& getaccount();
};