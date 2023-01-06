#pragma once
#include<iostream>
#include"Constants.h"

using namespace std;

class Person
{
	string name;
	llong CNIC;
	string username;
	string password;
	string pin;


public:
	Person();

	Person(string, llong, string, string, string);
	
	void setdata(string, llong, string, string, string);

	void setdata(string);

	void setname(string);

	void setCNIC(llong);

	void setusername(string);

	void setpassword(string);

	void setpin(string);

	string getname();

	long long getCNIC();

	string getusername();

	string getpassword();

	string getpin();

	void display();

	void makeNULL();
};
