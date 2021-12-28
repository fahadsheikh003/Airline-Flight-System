#pragma once
#include<iostream>

using namespace std;

class Person
{
	string name;
	long long CNIC;
	string username;
	string password;
	string pin;


public:
	Person();

	Person(string, long long, string, string, string);
	
	void setdata(string, long long, string, string, string);

	void setdata(string);

	void setname(string);

	void setCNIC(long long);

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