#pragma once
#include<iostream>
#include<string>
#include"Booking.h"
#include"Time.h"

using namespace std;

class Airplane;

class Flight_Schedule : public Booking
{
	int id;
	static int base;
	string type;
	Time takingoff_time;
	Time landing_time;
	string source;
	string srcairport;
	string destairport;
	string destination;
	Airplane* plane;
	string* delay;
	int size;
	double flight_duration;//hours
	bool status;

public:
	Flight_Schedule();
	void setid();
	int getid();
	void settype(string);
	string gettype();
	void settakingoff_time(const Time);
	Time gettakingoff_time();
	void setlanding_time(const Time&);
	Time getlanding_time();
	void setsource(const string&);
	string getsource();
	void setdestination(const string&);
	string getdestination();
	void setsrcairport(const string&);
	string getsrcairport();
	void setdestairport(const string&);
	string getdestairport();
	void setplane(const Airplane);
	Airplane* getplane();
	void adddelay(const string&);
	string* getdelay();
	int getdelaysize();
	void setstatus(bool s);
	bool getstatus();
	void addbooking(Passenger&);
	void setduration();
	void addflight();
	void operator=(const Flight_Schedule&);
	
};
