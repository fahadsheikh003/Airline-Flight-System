#pragma once
#pragma once
#include<iostream>
#include"Person.h"

using namespace std;

class Admin :public Person
{
public:
	Admin();

	Admin(string, long long, string, string, string);
};