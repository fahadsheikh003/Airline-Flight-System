#pragma once
#include<iostream>
#include"Payment.h"

using namespace std;

class Passenger;

class Seat :public Payment
{
	int id;
	bool status;
	Passenger* pers;

public:
	Seat();

	void setid(int id);

	void setstatus(bool s);

	void setpassenger(Passenger* per);

	int getid();

	bool getstatus();

	void makeNULL();

	Passenger* getpassenger();
};