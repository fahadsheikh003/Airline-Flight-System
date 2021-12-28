#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"Admin.h"
#include"Passenger.h"


#pragma warning(disable:4996)

using namespace std;
class Passenger;
class Flight_Schedule;
class City;

class extnetwork
{
	string* network;
	const int networksize;
	bool* status;

public:
	extnetwork();

	~extnetwork();
};

class NPAFS :public extnetwork
{
	City* cities;
	const int citysize;
	fstream admin_file, passenger_file;
	Admin curadmin;
	Passenger curuser;
	Flight_Schedule* flights;
	int flightsize;

public:
	NPAFS();

	void menu();

	void citybasedflights();

	void displayallflights();

	void displayflights();

	void manageuserprofile();

	int findflightindex(int id);

	void addflight();

	void editflight();

	void addbooking();

	bool checkpassword(string stemp);

	void userlogin();

	bool uniquecnic(string cnic);

	bool uniqueuser(string username);

	void adduser();

	void adminlogin();

	void initialflightdata();

	~NPAFS();
};