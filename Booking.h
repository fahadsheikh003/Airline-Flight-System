#pragma once
#include<iostream>

using namespace std;

class Seat;
class Passenger;

class Booking
{
protected:
	Seat* ecoseats;
	int esize;
	int eindex, bindex;
	Seat* busseats;
	int bsize;
	bool covid_status;

public:
	Booking();

	void setcovidstatus(bool);

	void addpassenger(Passenger&, int, string, string, double, Flight_Schedule&);

	Seat& getseat(int);

	Seat* getbusseats();

	Seat* getecoseats();

	bool getcovidstatus();

	~Booking();
};