#include<iostream>
#include<iomanip>
#include<string>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include"Person.h"
#include"Admin.h"
#include"Airplane.h"
#include"Airport.h"
#include"Bank.h"
#include"Booking.h"
#include"City.h"
#include"Flight_Schedule.h"
#include"Passenger.h"
#include"Payment.h"
#include"Runway.h"
#include"Seat.h"
#include"Travel_History.h"
#include"NPAFS.h"

using namespace std;

//Person class
Person::Person()
{
	name = "NULL";
	CNIC = NULL;
	username = "NULL";
	password = "NULL";
	pin = "NULL";
};

Person::Person(string n, long long CNIC, string un, string pass, string pin)
{
	name = n;
	this->CNIC = CNIC;
	username = un;
	password = pass;
	this->pin = pin;
}

void Person::setdata(string n, long long CNIC, string un, string pass, string pin)
{
	name = n;
	this->CNIC = CNIC;
	username = un;
	password = pass;
	this->pin = pin;
}

void Person::setdata(string temp)
{
	string* ptr = new string[5];

	int pos = temp.find("\t");
	ptr[0] = temp.substr(0, pos);

	for (int i = 1; i < 4; i++)
	{
		temp = temp.substr(pos + 1);
		pos = temp.find("\t");
		ptr[i] = temp.substr(0, pos);
	}

	temp = temp.substr(pos + 1);
	pos = temp.find("\n");
	ptr[4] = temp.substr(0, pos);

	long long cnic = 0;
	int i = 0;
	while (1)
	{
		if (int(ptr[4][i]) >= 48 && int(ptr[4][i]) <= 57)
		{
			cnic = cnic * 10 + (long long(ptr[4][i]) - long long(48));
		}
		else
			break;
		i++;
	}

	this->setname(ptr[3]);
	this->setCNIC(cnic);
	this->setusername(ptr[0]);
	this->setpassword(ptr[1]);
	this->setpin(ptr[2]);

	delete[] ptr;
}

void Person::setname(string n)
{
	name = n;
}

void Person::setCNIC(long long CNIC)
{
	this->CNIC = CNIC;
}

void Person::setusername(string us)
{
	username = us;
}

void Person::setpassword(string pass)
{
	password = pass;
}

void Person::setpin(string pin)
{
	this->pin = pin;
}

string Person::getname()
{
	return name;
}

long long Person::getCNIC()
{
	return CNIC;
}

string Person::getusername()
{
	return username;
}

string Person::getpassword()
{
	return password;
}

string Person::getpin()
{
	return pin;
}

void Person::display()
{
	cout << "Name: " << name << endl;
	cout << "CNIC: " << CNIC << endl;
	cout << "Username: " << username << endl;
	cout << "Password: " << password << endl;
	cout << "PIN: " << pin << endl;
}

void Person::makeNULL()
{
	this->setname("NULL");
	this->setCNIC(long long(0));
	this->setusername("NULL");
	this->setpassword("NULL");
	this->setpin("-1");
}

//Admin class
Admin::Admin() {};

Admin::Admin(string n, long long CNIC, string un, string pass, string pin)
{
	this->setname(n);
	this->setCNIC(CNIC);
	this->setusername(un);
	this->setpassword(pass);
	this->setpin(pin);
};

//Airplane class
Airplane::Airplane() :id(-1), name("NULL"), current{} {};

Airplane::Airplane(const Airplane& P)
{
	this->id = P.id;
	this->name = P.name;
	this->current = P.current;
}

void Airplane::setdata(int id, string name)
{
	this->id = id;
	this->name = name;
}

int Airplane::getid()
{
	return id;
}

string Airplane::getname()
{
	return name;
}

void Airplane::setflight(Flight_Schedule& flight)
{
	current = &flight;
}

//Airport class
Airport::Airport() : id(-1), name("NULL"), runsize(5), flights{}, flightsize(0)
{
	runways = new Runway[runsize];
};

void Airport::setdata(int id, string name)
{
	this->id = id;
	this->name = name;
	for (int i = 0; i < 5; i++)
	{
		runways[i].setdata(i + 1, "Runway " + to_string(i + 1));
	}
}

void Airport::addflight(Flight_Schedule & flight)
{
	Flight_Schedule** tempflights = new Flight_Schedule * [flightsize + 1];

	for (int i = 0; i < flightsize; i++)
	{
		tempflights[i] = flights[i];
	}

	tempflights[flightsize] = &flight;

	if (flightsize != 0)
		delete[] flights;

	flights = tempflights;
	tempflights = nullptr;
	flightsize++;
}

void Airport::displayboard()
{
	cout << "Scheduled Flights are\n\n";

	for (int i = 0; i < flightsize; i++)
	{
		if (flights[i]->getstatus() == true)
		{
			cout << i + 1 << ". " << flights[i]->getid() << ", " << flights[i]->gettype() << ", From " << flights[i]->getsource() << " ("
				<< flights[i]->getsrcairport() << ") to " << flights[i]->getdestination() << " (" << flights[i]->getdestairport() << ") "
				<< "Taking off at " << flights[i]->gettakingoff_time().hour << ":" << flights[i]->gettakingoff_time().mins << " on "
				<< flights[i]->gettakingoff_time().day << "/" << flights[i]->gettakingoff_time().month << "/" << flights[i]->gettakingoff_time().year << "." << endl << endl;
		}
	}
}

Airport::~Airport()
{
	delete[] runways;
}

//Bank class
Bank::Bank() :accID(-1), balance(0), pin("NULL") {};

Bank::Bank(long id, double b, string pin)
{
	accID = id;
	balance = b;
	pin = pin;
}

void Bank::setdata(long id, double b, string pin)
{
	accID = id;
	balance = b;
	pin = pin;
}

long Bank::getaccID()
{
	return accID;
}

void Bank::setbalance(double b)
{
	balance = b;
}

double Bank::getbalance()
{
	return balance;
}

string Bank::getpin()
{
	return pin;
}

//Booking class
Booking::Booking() :esize(50), bsize(10), covid_status(false), eindex(0), bindex(0)
{
	ecoseats = new Seat[esize];
	busseats = new Seat[bsize];
	for (int i = 0; i < esize; i++)
	{
		ecoseats[i].setid(i + 1);
	}

	for (int i = 0; i < bsize; i++)
	{
		busseats[i].setid(101 + i);
	}
}

void Booking::setcovidstatus(bool s)
{
	covid_status = s;
}

void Booking::addpassenger(Passenger & P, int x, string type, string destination, double duration, Flight_Schedule& flight)
{
	if (type == "Local" || type == "local")
	{
		if (x == 1)
		{
			if (eindex < esize)
			{
				ecoseats[eindex].setinitialdata(10000, 5);
				ecoseats[eindex].setfinaldata(10000 * duration, 10000 * duration * 0.05);
				cout << "Ticket price: " << ecoseats[eindex].getseatprice() << endl;
				int choice;
				do
				{
					cout << "Enter 1 if you want to purchace it.\n"
						<< "Enter 2 to go back.\n"
						<< "Enter your choice: ";
					cin >> choice;
				} while (choice < 1 || choice>2);
				cin.ignore();
				switch (choice)
				{
				case 1:
				{
					do
					{
						cout << "Enter 1 if you want to pay cash at the time of departure.\n"
							<< "Enter 2 to pay from bank.\n"
							<< "Enter your choice: ";
						cin >> choice;
					} while (choice < 1 || choice>2);
					cin.ignore();
					if (choice == 1)
					{
						ecoseats[eindex].setpassenger(&P);
						ecoseats[eindex].setstatus(false);
						P.addticket(&flight);
						cout << "Seat no " << ecoseats[eindex].getid() << " has been booked for u.\n";
					}
					else if (choice == 2 && P.getaccount().getaccID() == -1)
					{
						cout << "Please login to your bank account.\n";
						P.setaccount();
						if (P.getaccount().getbalance() >= ecoseats[eindex].getseatprice())
						{
							ecoseats[eindex].setpassenger(&P);
							ecoseats[eindex].setstatus(false);
							P.addticket(&flight);
							cout << "Seat no " << ecoseats[eindex].getid() << " has been booked for u.\n";

							P.getaccount().setbalance(P.getaccount().getbalance() - ecoseats[eindex].getseatprice());
						}
						else
						{
							cout << "Sorry! you didn't have sufficient balance.\n";
							return;
						}
					}
					else if (choice == 2 && P.getaccount().getaccID() != -1)
					{
						if (P.getaccount().getbalance() >= ecoseats[eindex].getseatprice())
						{
							ecoseats[eindex].setpassenger(&P);
							ecoseats[eindex].setstatus(false);
							P.addticket(&flight);
							cout << "Seat no " << ecoseats[eindex].getid() << " has been booked for u.\n";

							P.getaccount().setbalance(P.getaccount().getbalance() - ecoseats[eindex].getseatprice());
						}
						else
						{
							cout << "Sorry! you didn't have sufficient balance.\n";
							return;
						}
					}
					break;
				}
				case 2:
					return;
				}

				if (covid_status)
					eindex++;
				eindex++;

			}
			else
			{
				cout << "\nSorry! no seat available..\n";
			}
		}
		else if (x == 2)
		{
			if (bindex < bsize)
			{
				busseats[bindex].setinitialdata(15000, 5);
				busseats[bindex].setfinaldata(15000 * duration, 15000 * duration * 0.05);
				cout << "Ticket price: " << busseats[bindex].getseatprice() << endl;
				int choice;
				do
				{
					cout << "Enter 1 if you want to purchace it.\n"
						<< "Enter 2 to go back.\n"
						<< "Enter your choice: ";
					cin >> choice;
				} while (choice < 1 || choice>2);
				cin.ignore();
				switch (choice)
				{
				case 1:
				{
					do
					{
						cout << "Enter 1 if you want to pay cash at the time of departure.\n"
							<< "Enter 2 to pay from bank.\n"
							<< "Enter your choice: ";
						cin >> choice;
					} while (choice < 1 || choice>2);
					cin.ignore();
					if (choice == 1)
					{
						busseats[bindex].setpassenger(&P);
						busseats[bindex].setstatus(false);
						P.addticket(&flight);
						cout << "Seat no " << busseats[bindex].getid() << " has been booked for u.\n";
					}
					else if (choice == 2 && P.getaccount().getaccID() == -1)
					{
						cout << "Please login to your bank account.\n";
						P.setaccount();
						if (P.getaccount().getbalance() >= busseats[bindex].getseatprice())
						{
							busseats[bindex].setpassenger(&P);
							busseats[bindex].setstatus(false);

							cout << "Seat no " << busseats[bindex].getid() << " has been booked for u.\n";
							P.addticket(&flight);
							P.getaccount().setbalance(P.getaccount().getbalance() - busseats[bindex].getseatprice());
						}
						else
						{
							cout << "Sorry! you didn't have sufficient balance.\n";
							return;
						}
					}
					else if (choice == 2 && P.getaccount().getaccID() != -1)
					{
						if (P.getaccount().getbalance() >= busseats[bindex].getseatprice())
						{
							busseats[bindex].setpassenger(&P);
							busseats[bindex].setstatus(false);

							cout << "Seat no " << busseats[bindex].getid() << " has been booked for u.\n";
							P.addticket(&flight);
							P.getaccount().setbalance(P.getaccount().getbalance() - busseats[bindex].getseatprice());
						}
						else
						{
							cout << "Sorry! you didn't have sufficient balance.\n";
							return;
						}
					}
					break;
				}
				case 2:
					return;
				}

				if (covid_status)
					bindex++;
				bindex++;

			}
			else
			{
				cout << "\nSorry! no seat available..\n";
			}
		}
	}
	else if (type == "International" || type == "international")
	{
		int size = P.getvisasize();
		bool visacheck = false;
		for (int i = 0; i < size; i++)
		{
			if (P.getvisa()[i] == destination)
				visacheck = true;
		}

		if (visacheck == false)
		{
			cout << "Sorry! you didn't have visa for " << destination << endl;
			return;
		}

		if (x == 1)
		{
			if (eindex < esize)
			{
				ecoseats[eindex].setinitialdata(20000, 10);
				ecoseats[eindex].setfinaldata(20000 * duration, 20000 * duration * 0.1);
				cout << "Ticket price: " << ecoseats[eindex].getseatprice() << endl;
				int choice;
				do
				{
					cout << "Enter 1 if you want to purchace it.\n"
						<< "Enter 2 to go back.\n"
						<< "Enter your choice: ";
					cin >> choice;
				} while (choice < 1 || choice>2);
				cin.ignore();
				switch (choice)
				{
				case 1:
				{
					do
					{
						cout << "Enter 1 if you want to pay cash at the time of departure.\n"
							<< "Enter 2 to pay from bank.\n"
							<< "Enter your choice: ";
						cin >> choice;
					} while (choice < 1 || choice>2);
					cin.ignore();
					if (choice == 1)
					{
						ecoseats[eindex].setpassenger(&P);
						ecoseats[eindex].setstatus(false);
						P.addticket(&flight);
						cout << "Seat no " << ecoseats[eindex].getid() << " has been booked for u.\n";
					}
					else if (choice == 2 && P.getaccount().getaccID() == -1)
					{
						cout << "Please login to your bank account.\n";
						P.setaccount();
						if (P.getaccount().getbalance() >= ecoseats[eindex].getseatprice())
						{
							ecoseats[eindex].setpassenger(&P);
							ecoseats[eindex].setstatus(false);
							P.addticket(&flight);
							cout << "Seat no " << ecoseats[eindex].getid() << " has been booked for u.\n";

							P.getaccount().setbalance(P.getaccount().getbalance() - ecoseats[eindex].getseatprice());
						}
						else
						{
							cout << "Sorry! you didn't have sufficient balance.\n";
							return;
						}
					}
					else if (choice == 2 && P.getaccount().getaccID() != -1)
					{
						if (P.getaccount().getbalance() >= ecoseats[eindex].getseatprice())
						{
							ecoseats[eindex].setpassenger(&P);
							ecoseats[eindex].setstatus(false);
							P.addticket(&flight);
							cout << "Seat no " << ecoseats[eindex].getid() << " has been booked for u.\n";

							P.getaccount().setbalance(P.getaccount().getbalance() - ecoseats[eindex].getseatprice());
						}
						else
						{
							cout << "Sorry! you didn't have sufficient balance.\n";
							return;
						}
					}
					break;
				}
				case 2:
					return;
				}

				if (covid_status)
					eindex++;
				eindex++;

			}
			else
			{
				cout << "\nSorry! no seat available..\n";
			}
		}
		else if (x == 2)
		{
			if (bindex < bsize)
			{
				busseats[bindex].setinitialdata(25000, 10);
				busseats[bindex].setfinaldata(25000 * duration, 25000 * duration * 0.1);
				cout << "Ticket price: " << busseats[bindex].getseatprice() << endl;
				int choice;
				do
				{
					cout << "Enter 1 if you want to purchace it.\n"
						<< "Enter 2 to go back.\n"
						<< "Enter your choice: ";
					cin >> choice;
				} while (choice < 1 || choice>2);
				cin.ignore();
				switch (choice)
				{
				case 1:
				{
					do
					{
						cout << "Enter 1 if you want to pay cash at the time of departure.\n"
							<< "Enter 2 to pay from bank.\n"
							<< "Enter your choice: ";
						cin >> choice;
					} while (choice < 1 || choice>2);
					cin.ignore();
					if (choice == 1)
					{
						busseats[bindex].setpassenger(&P);
						busseats[bindex].setstatus(false);
						P.addticket(&flight);
						cout << "Seat no " << busseats[bindex].getid() << " has been booked for u.\n";
					}
					else if (choice == 2 && P.getaccount().getaccID() == -1)
					{
						cout << "Please login to your bank account.\n";
						P.setaccount();
						if (P.getaccount().getbalance() >= busseats[bindex].getseatprice())
						{
							busseats[bindex].setpassenger(&P);
							busseats[bindex].setstatus(false);
							P.addticket(&flight);
							cout << "Seat no " << busseats[bindex].getid() << " has been booked for u.\n";

							P.getaccount().setbalance(P.getaccount().getbalance() - busseats[bindex].getseatprice());
						}
						else
						{
							cout << "Sorry! you didn't have sufficient balance.\n";
							return;
						}
					}
					else if (choice == 2 && P.getaccount().getaccID() != -1)
					{
						if (P.getaccount().getbalance() >= busseats[bindex].getseatprice())
						{
							busseats[bindex].setpassenger(&P);
							busseats[bindex].setstatus(false);
							P.addticket(&flight);
							cout << "Seat no " << busseats[bindex].getid() << " has been booked for u.\n";

							P.getaccount().setbalance(P.getaccount().getbalance() - busseats[bindex].getseatprice());
						}
						else
						{
							cout << "Sorry! you didn't have sufficient balance.\n";
							return;
						}
					}
					break;
				}
				case 2:
					return;
				}

				if (covid_status)
					bindex++;
				bindex++;

			}
			else
			{
				cout << "\nSorry! no seat available..\n";
			}
		}
	}
}

Seat& Booking::getseat(int id)
{
	if (id > 100)
		return busseats[id - 101];
	else
		return ecoseats[id - 1];
}

Seat* Booking::getbusseats()
{
	return busseats;
}

Seat* Booking::getecoseats()
{
	return ecoseats;
}

bool Booking::getcovidstatus()
{
	return covid_status;
}

Booking::~Booking()
{
	delete[] ecoseats, busseats;
}

//City class
City::City() :id(0), name("NULL")
{
	airports = new Airport[2];
	planes = new Airplane[20];
};

void City::setdata(int id, string name)
{
	this->id = id;
	this->name = name;
	airports[0].setdata(10, "North");
	airports[1].setdata(20, "South");
	for (int i = 0; i < 20; i++)
	{
		planes[i].setdata(this->id * (i + 1), this->name + " Plane " + to_string(i + 1));
	}
}

Airport City::getairport(int i)
{
	return airports[i];
}

Airplane City::getplane(int x)
{
	for (int i = 0; i < 20; i++)
	{
		if (planes[i].getid() == x)
			return planes[i];

	}

	Airplane xd;
	xd.setdata(-1, "NULL");

	return xd;
}

void City::displayplanes()
{
	cout << "Airplanes of " << name << endl;
	for (int i = 0; i < 20; i++)
	{
		cout << i + 1 << ". " << planes[i].getname() << " ("
			<< planes[i].getid() << ")." << endl;
	}
}

//Flight_Schedule class
Flight_Schedule::Flight_Schedule() :delay{}, plane{}, takingoff_time{}, landing_time{}
{
	id = ++base;
	type = "NULL";
	source = destairport = destination = srcairport = "NULL";
	size = 0;
	flight_duration = 0;
	status = true;
}

void Flight_Schedule::setid()
{
	this->id = ++base;
}

int Flight_Schedule::getid()
{
	return id;
}

void Flight_Schedule::settype(string type)
{
	this->type = type;
}

string Flight_Schedule::gettype()
{
	return type;
}

void Flight_Schedule::settakingoff_time(const Time T)
{
	takingoff_time = T;
}

Time Flight_Schedule::gettakingoff_time()
{
	return takingoff_time;
}

void Flight_Schedule::setlanding_time(const Time& T)
{
	landing_time = T;
}

Time Flight_Schedule::getlanding_time()
{
	return landing_time;
}

void Flight_Schedule::setsource(const string& n)
{
	source = n;
}

string Flight_Schedule::getsource()
{
	return source;
}

void Flight_Schedule::setdestination(const string& n)
{
	destination = n;
}

string Flight_Schedule::getdestination()
{
	return destination;
}

void Flight_Schedule::setsrcairport(const string& n)
{
	srcairport = n;
}

string Flight_Schedule::getsrcairport()
{
	return srcairport;
}

void Flight_Schedule::setdestairport(const string& n)
{
	destairport = n;
}

string Flight_Schedule::getdestairport()
{
	return destairport;
}

void Flight_Schedule::setplane(const Airplane* plane)
{
	this->plane = new Airplane(*plane);
}

Airplane* Flight_Schedule::getplane()
{
	return plane;
}

void Flight_Schedule::adddelay(const string& n)
{
	string* temp = new string[size + 1];

	for (int i = 0; i < size; i++)
	{
		temp[i] = delay[i];
	}

	temp[size] = n;

	if (size != 0)
		delete[] delay;

	delay = temp;
	temp = nullptr;
	size++;
}

string* Flight_Schedule::getdelay()
{
	return delay;
}

int Flight_Schedule::getdelaysize()
{
	return size;
}

void Flight_Schedule::setstatus(bool s)
{
	status = s;
}

bool Flight_Schedule::getstatus()
{
	return status;
}

void Flight_Schedule::addbooking(Passenger & P)
{
	int choice;

	cout << "Enter 1 if you want to travel in economy class.\n"
		<< "Enter 2 if you want to travel in business class.\n"
		<< "Enter your choice: ";
	cin >> choice;

	addpassenger(P, choice, type, destination, flight_duration, *this);
}

void Flight_Schedule::setduration()
{
	if (type == "Local" || type == "local")
		flight_duration = 1;
	else if (type == "International" || type == "international")
	{
		flight_duration = 3;
		if (size > 0)
			flight_duration += double(size) * 2;
	}

	landing_time.mins = takingoff_time.mins;
	landing_time.hour = takingoff_time.hour + flight_duration;
	if (landing_time.hour > 23)
	{
		landing_time.day = 1;
		landing_time.hour %= 24;
	}
	landing_time.day += takingoff_time.day;
	if (landing_time.day > 30)
	{
		landing_time.month = 1;
		landing_time.day %= 30;
	}
	landing_time.month += takingoff_time.month;
	if (landing_time.month > 12)
	{
		landing_time.year = 1;
		landing_time.month %= 12;
	}
	landing_time.year += takingoff_time.year;
}

void Flight_Schedule::addflight()
{
	do
	{
		cout << "Enter flight type (local or international): ";
		getline(cin, type);
	} while (!(type == "Local" || type == "local" || type == "International" || type == "international"));

	do
	{
		cout << "Enter departure city: ";
		getline(cin, source);
	} while (!(source == "Karachi" || source == "Peshawar" || source == "Quetta"
		|| source == "Islamabad" || source == "Lahore"));

	do
	{
		cout << "Enter airport for departure (North or South): ";
		getline(cin, srcairport);
	} while (!(srcairport == "North" || srcairport == "South"));

	if (type == "Local" || type == "local")
	{
		do
		{
			cout << "Enter Destination city: ";
			getline(cin, destination);
		} while (!((destination != source) && (destination == "Karachi" || destination == "Peshawar" || destination == "Quetta"
			|| destination == "Islamabad" || destination == "Lahore")));

		do
		{
			cout << "Enter airport for destination (North or South): ";
			getline(cin, destairport);
		} while (!(destairport == "North" || destairport == "South"));
	}

	else if (type == "International" || type == "international")
	{
		do
		{
			cout << "Enter Destination country: ";
			getline(cin, destination);
		} while (!(destination == "United States" || destination == "Canada" || destination == "France"
			|| destination == "Japan" || destination == "South Africa" || destination == "United Kingdom"
			|| destination == "Iran" || destination == "Iraq" || destination == "Turkey"
			|| destination == "China" || destination == "Russia" || destination == "Spain"
			|| destination == "Dubai" || destination == "Kingdom of South Arabia" || destination == "New Zealand"
			|| destination == "Sweden" || destination == "Denmark" || destination == "Bahrain"
			|| destination == "Kuwait" || destination == "Austria" || destination == "Australia"
			|| destination == "Bangladesh" || destination == "Panama" || destination == "Afghanistan"
			|| destination == "Vietnam"));

		cout << "Enter number of delay's in flight (enter 0 if none): ";
		cin >> size;
		delay = new string[size];
		for (int i = 0; i < size; i++)
		{
			do
			{
				cout << "Enter delay " << i + 1 << " : ";
				getline(cin, delay[i]);
			} while (destination == delay[i]);
		}

		destairport = destination + " International Airport";

	}

	cout << "Enter Time of departure:\n";

	do
	{
		cout << "Enter year: ";
		cin >> takingoff_time.year;
	} while (!(takingoff_time.year >= 2021 && takingoff_time.year <= 2030));

	do
	{
		cout << "Enter month: ";
		cin >> takingoff_time.month;
	} while (!(takingoff_time.month > 0 && takingoff_time.month <= 12));

	do
	{
		cout << "Enter day: ";
		cin >> takingoff_time.day;
	} while (!(takingoff_time.day > 0 && takingoff_time.day <= 30));

	do
	{
		cout << "Enter hour(24h format): ";
		cin >> takingoff_time.hour;
	} while (!(takingoff_time.hour >= 0 && takingoff_time.hour <= 23));

	do
	{
		cout << "Enter minutes(0-59): ";
		cin >> takingoff_time.mins;
	} while (!(takingoff_time.mins >= 0 && takingoff_time.mins <= 59));


}

void Flight_Schedule::operator=(const Flight_Schedule & F)
{
	this->id = F.id;
	this->type = F.type;
	this->takingoff_time = F.takingoff_time;
	this->landing_time = F.landing_time;
	this->source = F.source;
	this->destination = F.destination;
	this->srcairport = F.srcairport;
	this->destairport = F.destairport;
	this->plane = new Airplane;
	this->plane = F.plane;
	this->flight_duration = F.flight_duration;
	this->size = F.size;
	this->status = F.status;
	this->delay = new string[this->size];
	for (int i = 0; i < this->size; i++)
	{
		delay[i] = F.delay[i];
	}
	this->bsize = F.bsize;
	this->esize = F.esize;
	this->bindex = F.bindex;
	this->eindex = F.eindex;

	this->ecoseats = new Seat[this->esize];
	for (int i = 0; i < this->esize; i++)
	{
		this->ecoseats[i] = F.ecoseats[i];
	}

	this->busseats = new Seat[this->bsize];
	for (int i = 0; i < this->bsize; i++)
	{
		this->busseats[i] = F.busseats[i];
	}
}

int Flight_Schedule::base = 0;

//Passenger class
Passenger::Passenger() : vsize(0), visits{}, visasize(0), visa{}, flightsize(0), tickets_reserved{} {};

Passenger::Passenger(string n, long long CNIC, string un, string pass, string pin) : vsize(0), visits{}, visasize(0), visa{}, flightsize(0), tickets_reserved{}
{
	this->setname(n);
	this->setCNIC(CNIC);
	this->setusername(un);
	this->setpassword(pass);
	this->setpin(pin);
};

void Passenger::setaccount()
{
	if (account.getaccID() == -1)
	{
		long xd; string pin; double b;

		cout << "Enter account ID: ";
		cin >> xd;
		cin.ignore();
		cout << "Enter Balance: ";
		cin >> b;
		cin.ignore();
		cout << "Enter your pin: ";
		//getline(cin, pin);

		char F[32];
		char a;
		int i = 0;
		while (1)
		{
			a = getch();

			if (a >= 32 && a <= 126)
			{
				F[i] = a;
				i++;
				cout << "*";
			}

			if (a == '\b' && i >= 1)
			{
				cout << "\b \b";
				i--;
			}

			if (a == '\r')
			{
				F[i] = '\0';
				break;
			}
		}

		pin = F;

		account.setdata(xd, b, pin);
	}
	else
	{
		cout << "\nYour bank account is already linked.\n";
	}
}

void Passenger::makeNULL()
{
	Person::makeNULL();
	vsize = visasize = flightsize = NULL;
	visits = nullptr;
	tickets_reserved = nullptr;
	visa = nullptr;
}

bool Passenger::uniquevisa(string v)
{
	for (int i = 0; i < visasize; i++)
	{
		if (visa[i] == v)
			return false;
	}
	return true;
}

void Passenger::addvisa(string v)
{
	string* tempvisa = new string[visasize + 1];

	for (int i = 0; i < visasize; i++)
	{
		tempvisa[i] = visa[i];
	}

	tempvisa[visasize] = v;

	if (visasize != 0)
	{
		delete[] visa;
	}

	visa = tempvisa;
	tempvisa = nullptr;

	visasize++;
}

void Passenger::displayflights()
{
	cout << "You have tickets for following Flights\n\n";

	for (int i = 0; i < flightsize; i++)
	{
		if (tickets_reserved[i]->getstatus() == true)
		{
			cout << i + 1 << ". " << tickets_reserved[i]->getid() << ", " << tickets_reserved[i]->gettype() << ", From " << tickets_reserved[i]->getsource() << " ("
				<< tickets_reserved[i]->getsrcairport() << ") to " << tickets_reserved[i]->getdestination() << " (" << tickets_reserved[i]->getdestairport() << ") "
				<< "Taking off at " << tickets_reserved[i]->gettakingoff_time().hour << ":" << tickets_reserved[i]->gettakingoff_time().mins << " on "
				<< tickets_reserved[i]->gettakingoff_time().day << "/" << tickets_reserved[i]->gettakingoff_time().month << "/" << tickets_reserved[i]->gettakingoff_time().year << "." << endl << endl;
		}
	}
}

void Passenger::addticket(Flight_Schedule * Flight)
{
	Flight_Schedule** tempflights = new Flight_Schedule * [flightsize + 1];

	for (int i = 0; i < flightsize; i++)
	{
		tempflights[i] = tickets_reserved[i];
	}

	tempflights[flightsize] = Flight;

	if (flightsize != 0)
	{
		delete[] tickets_reserved;
	}

	tickets_reserved = tempflights;
	tempflights = nullptr;

	flightsize++;
}

int Passenger::findflightindex(int id)
{
	for (int i = 0; i < flightsize; i++)
	{
		if (tickets_reserved[i]->getid() == id)
			return i;
	}
	return -1;
}

void Passenger::cancelflight()
{
	int xd;
	cout << "Enter Id of the flight that you want to cancel: ";
	cin >> xd;

	int index = findflightindex(xd);

	if (index == -1)
	{
		cout << "Sorry! no flight found.\n";
		return;
	}

	int seatindex = -1;
	string seattype;
	cout << "Error!";
	for (int i = 1; i <= 110; i++)
	{
		if ((i <= 50) && (tickets_reserved[index]->getseat(i).getpassenger()->getusername() == this->getusername()))
		{
			seatindex = i - 1;
			seattype = "Economy";
			break;
		}
		else if ((i <= 110) && (tickets_reserved[index]->getseat(i).getpassenger()->getusername() == this->getusername()))
		{
			seatindex = i - 101;
			seattype = "Business";
			break;
		}
		if (i == 51)
			i = 100;
	}
	
	double payment=0;
	if (seattype == "Economy")
	{
		tickets_reserved[index]->getecoseats()[seatindex].makeNULL();
		payment = tickets_reserved[index]->getecoseats()[seatindex].getseatprice() * 0.75;
	}
	else if (seattype == "Business")
	{
		tickets_reserved[index]->getbusseats()[seatindex].makeNULL();
		payment = tickets_reserved[index]->getbusseats()[seatindex].getseatprice() * 0.75;
	}

	if (account.getaccID() == -1)
	{
		cout << "Please login to your bank to receive your payment.\n";
		setaccount();
	}

	account.setbalance(account.getbalance() + payment);
	cout << "\nYou have received " << payment << " PKR.\n";
	cout << "Your new Balance is " << account.getbalance() << endl;
}

//void Passenger::addvisit();

string* Passenger::getvisa()
{
	return visa;
}

int Passenger::getvisasize()
{
	return visasize;
}

Bank& Passenger::getaccount()
{
	return account;
}

//Payment class
void Payment::setinitialdata(int ph, int gstp)
{
	perhour = ph;
	gstper = gstp;
}

void Payment::setfinaldata(double tcost, double ttax)
{
	totalcost = tcost;
	totaltax = ttax;
}

double Payment::getseatprice()
{
	return totalcost + totaltax;
}

//Runway class
Runway::Runway() : id(-1), name("NULL"), status(true), current{} {};

void Runway::setdata(int id, string name)
{
	this->id = id;
	this->name = name;
	status = true;
}

void Runway::setstatus(bool status)
{
	this->status = status;
}

bool Runway::getstatus()
{
	return status;
}

void Runway::setairplane(Airplane& airplane)
{
	current = &airplane;
}

Airplane* Runway::getairplane()
{
	return current;
}

//Seat class
Seat::Seat() : id(0), status(true), pers{} {};

void Seat::setid(int id)
{
	this->id = id;
}

void Seat::setstatus(bool s)
{
	status = s;
}

void Seat::setpassenger(Passenger* per)
{
	pers = new Passenger(*per);
}

int Seat::getid()
{
	return id;
}

bool Seat::getstatus()
{
	return status;
}

void Seat::makeNULL()
{
	status = true;
	pers = nullptr;
}

Passenger* Seat::getpassenger()
{
	return pers;
}

//Travel_History class
Travel_History::Travel_History() : day(0), month(0), year(0), ndays(0), location("NULL") {};

Travel_History::Travel_History(int d, int m, int y, int n, string loc)
{
	day = d;
	month = m;
	year = y;
	ndays = n;
	location = loc;
}

//extnetwork class
extnetwork::extnetwork() : networksize(25)
{
	network = new string[networksize];
	status = new bool[networksize];

	for (int i = 0; i < networksize; i++)
	{
		status[i] = false;
	}

	network[0] = "United States";
	network[1] = "Canada";
	network[2] = "France";
	network[3] = "Japan";
	network[4] = "South Africa";
	network[5] = "United Kingdom";
	network[6] = "Iran";
	network[7] = "Iraq";
	network[8] = "Turkey";
	network[9] = "China";
	network[10] = "Russia";
	network[11] = "Spain";
	network[12] = "Dubai";
	network[13] = "Kingdom of Saudi Arabia";
	network[14] = "New Zealand";
	network[15] = "Sweden";
	network[16] = "Denmark";
	network[17] = "Bahrain";
	network[18] = "Kuwait";
	network[19] = "Austria";
	network[20] = "Australia";
	network[21] = "Bangladesh";
	network[22] = "Panama";
	network[23] = "Afghanistan";
	network[24] = "Vietnam";
}

extnetwork::~extnetwork()
{
	delete[] network, status;
}

//NPAFS class
NPAFS::NPAFS() : citysize(5), curadmin{}, curuser{}, flights{}, flightsize(0)
{
	cities = new City[citysize];

	cities[0].setdata(21, "Karachi");
	cities[1].setdata(91, "Peshawar");
	cities[2].setdata(81, "Quetta");
	cities[3].setdata(42, "Lahore");
	cities[4].setdata(51, "Islamabad");

	initialflightdata();
}

void NPAFS::initialflightdata()
{
	flightsize = 15;
	flights = new Flight_Schedule[flightsize];

	srand(time(nullptr));
	Time temp;

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	//Peshawar Flights
	flights[0].settype("Local");
	flights[0].setsource("Peshawar");
	flights[0].setsrcairport("North");
	flights[0].setdestination("Islamabad");
	flights[0].setdestairport("South");
	flights[0].settakingoff_time(temp);
	flights[0].setduration();
	flights[0].setplane(&cities[1].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[1].settype("Local");
	flights[1].setsource("Peshawar");
	flights[1].setsrcairport("South");
	flights[1].setdestination("Karachi");
	flights[1].setdestairport("South");
	flights[1].settakingoff_time(temp);
	flights[1].setduration();
	flights[1].setplane(&cities[1].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[2].settype("International");
	flights[2].setsource("Peshawar");
	flights[2].setsrcairport("South");
	flights[2].setdestination("Japan");
	flights[2].setdestairport("Japan's International Airport");
	flights[2].settakingoff_time(temp);
	flights[2].setduration();
	flights[2].setplane(&cities[1].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	//Islamabad Flights
	flights[3].settype("Local");
	flights[3].setsource("Islamabad");
	flights[3].setsrcairport("South");
	flights[3].setdestination("Peshawar");
	flights[3].setdestairport("South");
	flights[3].settakingoff_time(temp);
	flights[3].setduration();
	flights[3].setplane(&cities[4].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[4].settype("Local");
	flights[4].setsource("Islamabad");
	flights[4].setsrcairport("South");
	flights[4].setdestination("Lahore");
	flights[4].setdestairport("South");
	flights[4].settakingoff_time(temp);
	flights[4].setduration();
	flights[4].setplane(&cities[4].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[5].settype("International");
	flights[5].setsource("Islamabad");
	flights[5].setsrcairport("South");
	flights[5].setdestination("Turkey");
	flights[5].setdestairport("Turkey's International Airport");
	flights[5].settakingoff_time(temp);
	flights[5].setduration();
	flights[5].setplane(&cities[4].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	// Lahore FLights
	flights[6].settype("Local");
	flights[6].setsource("Lahore");
	flights[6].setsrcairport("South");
	flights[6].setdestination("Peshawar");
	flights[6].setdestairport("South");
	flights[6].settakingoff_time(temp);
	flights[6].setduration();
	flights[6].setplane(&cities[3].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[7].settype("Local");
	flights[7].setsource("Lahore");
	flights[7].setsrcairport("South");
	flights[7].setdestination("Islamabad");
	flights[7].setdestairport("South");
	flights[7].settakingoff_time(temp);
	flights[7].setduration();
	flights[7].setplane(&cities[3].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[8].settype("International");
	flights[8].setsource("Lahore");
	flights[8].setsrcairport("South");
	flights[8].setdestination("Iran");
	flights[8].setdestairport("Iran's International Airport");
	flights[8].settakingoff_time(temp);
	flights[8].setduration();
	flights[8].setplane(&cities[3].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	//Karachi Flights
	flights[9].settype("Local");
	flights[9].setsource("Karachi");
	flights[9].setsrcairport("South");
	flights[9].setdestination("Peshawar");
	flights[9].setdestairport("South");
	flights[9].settakingoff_time(temp);
	flights[9].setduration();
	flights[9].setplane(&cities[0].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[10].settype("Local");
	flights[10].setsource("Karachi");
	flights[10].setsrcairport("South");
	flights[10].setdestination("Islamabad");
	flights[10].setdestairport("South");
	flights[10].settakingoff_time(temp);
	flights[10].setduration();
	flights[10].setplane(&cities[0].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[11].settype("International");
	flights[11].setsource("Karachi");
	flights[11].setsrcairport("South");
	flights[11].setdestination("Kingdom of Saudi Arabia");
	flights[11].setdestairport("Saudi International Airport");
	flights[11].settakingoff_time(temp);
	flights[11].setduration();
	flights[11].setplane(&cities[0].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	//Quetta Flights
	flights[12].settype("Local");
	flights[12].setsource("Quetta");
	flights[12].setsrcairport("South");
	flights[12].setdestination("Islamabad");
	flights[12].setdestairport("South");
	flights[12].settakingoff_time(temp);
	flights[12].setduration();
	flights[12].setplane(&cities[2].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[13].settype("Local");
	flights[13].setsource("Quetta");
	flights[13].setsrcairport("South");
	flights[13].setdestination("Peshawar");
	flights[13].setdestairport("South");
	flights[13].settakingoff_time(temp);
	flights[13].setduration();
	flights[13].setplane(&cities[2].getplane(rand() % 20));

	temp.day = rand() % 30 + 1;
	temp.month = rand() % 6 + 7;
	temp.year = 2021;
	temp.hour = rand() % 24;
	temp.mins = rand() % 60;

	flights[14].settype("International");
	flights[14].setsource("Quetta");
	flights[14].setsrcairport("South");
	flights[14].setdestination("United States");
	flights[14].setdestairport("Los Angelos' International Airport");
	flights[14].settakingoff_time(temp);
	flights[14].setduration();
	flights[14].setplane(&cities[2].getplane(rand() % 20));
}

void NPAFS::menu()
{
home:
	cout << setw(82) << "Welcome to New-Pak Airline Flight System.\n";
	cout << "Locally operational in Islamabad, Karachi, Lahore, Quetta & Peshawar.\n"
		<< "Internationally operational in United States, Canada, France, Japan, South Africa, United Kingdom, Iran, Iraq, Turkey,\nChina, Russia, Spain, Dubai, Kingdom of Saudi Arabia, New Zealand, Sweden, Denmark, Bahrain, Kuwait, Austria, Australia, Bangladesh, Panama, Afghanistan & Vietnam.\n";

	int apchoice;

	do
	{
		cout << "Enter 1 if you are an admin.\n"
			<< "Enter 2 if you are a passenger.\n"
			<< "Enter 3 to exit.\n"
			<< "Please enter your choice: ";
		cin >> apchoice;
	} while (apchoice < 1 || apchoice>3);
	cin.ignore();
	switch (apchoice)
	{
	case 1:
	{
		adminlogin();

	adminpanel:
		do
		{
			cout << "Enter 1 if you want to add a flight.\n"
				<< "Enter 2 to view all scheduled flights.\n"
				<< "Enter 3 if you want to edit a flight.\n"
				<< "Enter 4 to logout(to go back to home).\n"
				<< "Enter 5 to exit.\n"
				<< "Enter your choice: ";
			cin >> apchoice;
		} while (apchoice < 1 || apchoice>5);
		cin.ignore();
		switch (apchoice)
		{
		case 1:
		{
			addflight();
			goto adminpanel;
		}
		case 2:
		{
			displayallflights();
			goto adminpanel;
		}
		case 3:
		{
			editflight();
			goto adminpanel;
		}
		case 4:
		{
			cout << "Logged out!\n";
			curadmin.makeNULL();
			goto home;
		}
		case 5:
			exit(0);
		}
	}
	case 2:
	{
	passengerpanel:
		if (curuser.getname() == "NULL")
		{
			do
			{
				cout << "\n\nEnter 1 if you want to sign in.\n";
				cout << "Enter 2 if you want to sign up.\n"
					<< "Enter 3 if you want to see details of flights.\n"
					<< "Enter 4 to go to home.\n"
					<< "Enter 5 to exit.\n"
					<< "Please enter your choice: ";
				cin >> apchoice;
			} while (apchoice < 1 || apchoice>5);
			cin.ignore();
			switch (apchoice)
			{
			case 1:
			{
				userlogin();
				goto passengerpanel;
			}
			case 2:
			{
				adduser();
				goto passengerpanel;
			}
			case 3:
			{
				displayflights();
				goto passengerpanel;
			}
			case 4:
			{
				goto home;
			}
			case 5:
			{
				exit(0);
			}
			}
		}
		else
		{
			do
			{
				cout << "\n\nEnter 1 if you want to sign out(to go back).\n"
					<< "Enter 2 if you want to see details of flights.\n"
					<< "Enter 3 to manage your Profile (passport and tickets).\n"
					<< "Enter 4 if you want to exit.\n"
					<< "Please enter your choice: ";
				cin >> apchoice;
			} while (apchoice < 1 || apchoice > 4);

			switch (apchoice)
			{
			case 1:
			{
				cout << "Logged out, Successfully!\n";
				curuser.makeNULL();
				goto passengerpanel;
			}
			case 2:
			{
				displayflights();
				goto passengerpanel;
			}
			case 3:
			{
				manageuserprofile();
				goto passengerpanel;
			}
			case 4:
			{
				exit(0);
			}
			}
		}
	}
	case 3:
		exit(0);
	}



}

void NPAFS::citybasedflights()
{
	int cchoice;

	do
	{
		cout << "Please enter your city.\n"
			<< "Enter 1 for Karachi.\n"
			<< "Enter 2 for Peshawar.\n"
			<< "Enter 3 for Quetta.\n"
			<< "Enter 4 for Lahore.\n"
			<< "Enter 5 for Islamabad.\n"
			<< "Enter your choice: ";
		cin >> cchoice;
	} while (cchoice < 1 || cchoice>5);

	int airchoice;
	do
	{
		cout << "Please enter your preferred Airport.\n"
			<< "Enter 1 for North.\n"
			<< "Enter 2 for South.\n"
			<< "Enter your choice: ";
		cin >> airchoice;
	} while (airchoice < 1 || airchoice>2);
	cin.ignore();
	//cities[cchoice - 1].getairport(airchoice - 1).displayboard();
}

void NPAFS::displayallflights()
{
	cout << "Scheduled Flights are\n\n";

	for (int i = 0; i < flightsize; i++)
	{
		if (flights[i].getstatus() == true)
		{
			cout << i + 1 << ". " << flights[i].getid() << ", " << flights[i].gettype() << ", From " << flights[i].getsource() << " ("
				<< flights[i].getsrcairport() << ") to " << flights[i].getdestination() << " (" << flights[i].getdestairport() << ") "
				<< "Taking off at " << flights[i].gettakingoff_time().hour << ":" << flights[i].gettakingoff_time().mins << " on "
				<< flights[i].gettakingoff_time().day << "/" << flights[i].gettakingoff_time().month << "/" << flights[i].gettakingoff_time().year << "." << endl << endl;
		}
	}
}

void NPAFS::displayflights()
{
	int choice;
	do
	{
		cout << "Enter 1 to see flights city based.\n"
			<< "Enter 2 to see all scheduled flights.\n"
			<< "Enter your choice: ";
		cin >> choice;
	} while (choice < 1 || choice>2);
	cin.ignore();
	switch (choice)
	{
	case 1:
	{
		citybasedflights();
	}
	case 2:
	{
		displayallflights();
	}

	if (curuser.getname() != "NULL")
	{
		do
		{
			cout << "Enter 1 to book a flight.\n"
				<< "Enter 2 to go back.\n"
				<< "Enter your choice: ";
			cin >> choice;
		} while (choice < 1 || choice>2);
		cin.ignore();
		switch (choice)
		{
		case 1:
		{
			addbooking();
			break;
		}
		case 2:
		{
			return;
		}
		}
	}

	}
}

void NPAFS::manageuserprofile()
{
	if (curuser.getname() != "NULL")
	{
		int choice;
		do
		{
			cout << "Enter 1 if you want to add a visa of a country\n"
				<< "Enter 2 if you want to cancel a flight.\n"
				<< "Enter 3 to link your Bank Account.\n"
				<< "Enter your choice: ";
			cin >> choice;
		} while (choice < 1 || choice>3);
		cin.ignore();
		switch (choice)
		{
		case 1:
		{
			string v;
			do
			{
				cout << "Enter country for which u have visa: ";
				getline(cin, v);
			} while (!(v == "United States" || v == "Canada" || v == "France"
				|| v == "Japan" || v == "South Africa" || v == "United Kingdom"
				|| v == "Iran" || v == "Iraq" || v == "Turkey"
				|| v == "China" || v == "Russia" || v == "Spain"
				|| v == "Dubai" || v == "Kingdom of South Arabia" || v == "New Zealand"
				|| v == "Sweden" || v == "Denmark" || v == "Bahrain"
				|| v == "Kuwait" || v == "Austria" || v == "Australia"
				|| v == "Bangladesh" || v == "Panama" || v == "Afghanistan"
				|| v == "Vietnam"));

			if (curuser.uniquevisa(v))
			{
				curuser.addvisa(v);
				cout << "Visa of " << v << " added successfully.\n";
			}
			break;
		}
		case 2:
		{
			curuser.displayflights();
			curuser.cancelflight();
			break;
		}
		case 3:
		{
			curuser.setaccount();
		}
		}
	}
}

int NPAFS::findflightindex(int id)
{
	for (int i = 0; i < flightsize; i++)
	{
		if (flights[i].getid() == id)
			return i;
	}
	return -1;
}

void NPAFS::addflight()
{
	Flight_Schedule* tempflights = new Flight_Schedule[flightsize + 1];

	for (int i = 0; i < flightsize; i++)
	{
		tempflights[i] = flights[i];
	}

	tempflights[flightsize].addflight();
	tempflights[flightsize].setduration();

	string cityname = tempflights[flightsize].getsource();
	int xd = -1;

	if (cityname == "Karachi")
		xd = 0;
	else if (cityname == "Peshawar")
		xd = 1;
	else if (cityname == "Quetta")
		xd = 2;
	else if (cityname == "Lahore")
		xd = 3;
	else if (cityname == "Islamabad")
		xd = 4;

	cities[xd].displayplanes();

	int id;
	cout << "Enter id of airplane: ";
	cin >> id;
	cin.ignore();
	Airplane A = cities[xd].getplane(id);

	tempflights[flightsize].setplane(&A);

	string airport = tempflights[flightsize].getsrcairport();

	int ad = -1;
	if (airport == "North")
		ad = 0;
	else if (airport == "South")
		ad = 1;

	cities[xd].getairport(ad).addflight(tempflights[flightsize]);

	if (flightsize != 0)
		delete[] flights;

	flights = tempflights;
	tempflights = nullptr;

	flightsize++;
}

void NPAFS::editflight()
{
	int tempid;
againflightid:
	displayallflights();
	cout << "Enter id of the flight you want to book: ";
	cin >> tempid;

	int flightindex = findflightindex(tempid);

	if (flightindex == -1)
	{
		cout << "\nFlight not found..\n";
		goto againflightid;
	}
	
	int choice;
	do
	{
		cout << "Enter 1 if you want to change the status of flight to land.\n"
			<< "Enter 2 if you want to change the covid status.\n"
			<< "Enter 3 if you want to go back.\n"
			<< "Enter your choice: ";
		cin >> choice;
	} while (choice < 1 || choice>3);

	switch (choice)
	{
	case 1:
	{
		if (flights[flightindex].getstatus() == false)
		{
			cout << "Sorry! Status of this flight is already false.\n";
			return;
		}
		else
		{
			flights[flightindex].setstatus(false);
			cout << "Status of this flight is changed to false.\n";
			return;
		}
	}
	case 2:
	{
		if (flights[flightindex].getcovidstatus() == false)
		{
			flights[flightindex].setcovidstatus(true);
			cout << "Covid Status of this flight is changed to true.\n";
			return;
		}
		else
		{
			flights[flightindex].setcovidstatus(false);
			cout << "Covid Status of this flight is changed to false.\n";
			return;
		}
	}
	case 3:
	{
		return;
	}
	}
}

void NPAFS::addbooking()
{
	int tempid;
againflightid:
	cout << "Enter id of the flight you want to book: ";
	cin >> tempid;

	int flightindex = findflightindex(tempid);

	if (flightindex == -1)
	{
		cout << "\nFlight not found..\n";
		goto againflightid;
	}

	if (flights[flightindex].getstatus() == false)
	{
		cout << "Sorry! Tickets for this flight isn't available.\n";
		goto againflightid;
	}
	flights[flightindex].addbooking(curuser);
	int choice;
	do
	{
		cout << "Enter 1 if you want to book another flight.\n"
			<< "Enter 2 if you want to go back.\n"
			<< "Enter your choice: ";
		cin >> choice;
	} while (choice < 1 || choice>2);

	switch (choice)
	{
	case 1:
		goto againflightid;

	case 2:
	{
		return;
	}
	}

}

bool NPAFS::checkpassword(string stemp)
{
	string password;
passagain:
	cout << "Please Enter your password (must be of 8 characters): ";
	//getline(cin, password);

	char F[32];
	char a;
	int i = 0;
	while (1)
	{
		a = getch();

		if (a >= 32 && a <= 126)
		{
			F[i] = a;
			i++;
			cout << "*";
		}

		if (a == '\b' && i >= 1)
		{
			cout << "\b \b";
			i--;
		}

		if (a == '\r')
		{
			F[i] = '\0';
			break;
		}
	}

	cout << endl;
	password = F;

	if (password.length() != 8)
	{
		cout << "Incorrect Format!\n";
		goto passagain;
	}
	string temp = stemp;
	int pos = temp.find("\t");
	temp = temp.substr(pos + 1);
	pos = temp.find("\t");
	string pass = temp.substr(0, pos);

	if (password == pass)
		return true;
	else
	{
		int choice;
		cout << "Wrong Password.\n";
		do
		{
			cout << "Enter 1 to try again.\n"
				<< "Enter 2 to reset password.\n"
				<< "Enter 3 to go back to user input.\n";
			cin >> choice;
		} while (choice < 1 || choice>3);
		cin.ignore();
		switch (choice)
		{
		case 1:
			goto passagain;

		case 2:
		{
			//pass reset using pin
		}
		case 3:
			return false;
		}

	}

	return false;
}

void NPAFS::userlogin()
{
	passenger_file.open("passenger.txt", ios::in);

	if (passenger_file.is_open())
	{
		cout << "File is opened.\n";
	}

	string username;
againuserinput:
	cout << "Enter username (Blank spaces aren't allowed): ";
	getline(cin, username);

	string temp;

	getline(passenger_file, temp);
	string us;
	int pos = temp.find("\t");
	us = temp.substr(0, pos);

	if (username == us)
	{
		if (checkpassword(temp))
		{
			cout << "Logged in, successfully!\n";
			curuser.setdata(temp);
			passenger_file.close();
			return;
		}
	}
	while (!passenger_file.eof())
	{
		getline(passenger_file, temp);
		us = "NULL";
		pos = temp.find("\t");
		us = temp.substr(0, pos);

		if (username == us)
		{
			if (checkpassword(temp))
			{
				cout << "Logged in, successfully!\n";
				curuser.setdata(temp);
				passenger_file.close();
				return;
			}
		}

	}
	passenger_file.close();
	passenger_file.open("passenger.dat", ios::in);

	cout << "Username not found.\n"
		<< "Please enter username again.\n";
	goto againuserinput;
}

bool NPAFS::uniquecnic(string cnic)
{
	passenger_file.open("passenger.txt", ios::in);

	string temp;
	string us;
	getline(passenger_file, temp);
	int pos;

	for (int i = 0; i < 4; i++)
	{
		pos = temp.find("\t");
		temp = temp.substr(pos + 1);
	}

	us = temp;

	if (cnic == us)
	{
		passenger_file.close();
		return false;
	}

	while (!passenger_file.eof())
	{
		us = "NULL";
		getline(passenger_file, temp);
		for (int i = 0; i < 4; i++)
		{
			pos = temp.find("\t");
			temp = temp.substr(pos + 1);
		}

		us = temp;

		if (cnic == us)
		{
			passenger_file.close();
			return false;
		}
	}
	passenger_file.close();
	return true;
}

bool NPAFS::uniqueuser(string username)
{
	passenger_file.open("passenger.txt", ios::in);

	string temp;
	string us;
	getline(passenger_file, temp);
	int pos = temp.find("\t");
	us = temp.substr(0, pos);

	if (username == us)
	{
		passenger_file.close();
		return false;
	}

	while (!passenger_file.eof())
	{
		us = "NULL";
		getline(passenger_file, temp);
		pos = temp.find("\t");
		us = temp.substr(0, pos);

		if (username == us)
		{
			passenger_file.close();
			return false;
		}
	}
	passenger_file.close();
	return true;
}

void NPAFS::adduser()
{
	string un;
username:
	cout << "Enter username (blank spaces aren't allowed): ";
	getline(cin, un);
	int c = un.length();
	for (int i = 0; i <= c; i++)
	{
		if (un[i] == ' ')
		{
			cout << "Invalid format.\n";
			goto username;
		}
	}

	if (!uniqueuser(un))
	{
		cout << "Username already exists.\n"
			<< "Please enter another username.\n";
		goto username;
	}

	string pass, cpass;
pass:
	cout << "Please Enter your password (must be 8 characters long and use of minimum one special character, \nuppercase, lowercase, and numeric digit is must): ";
	//getline(cin, pass);

	char F[32];
	char a;
	int i = 0;
	while (1)
	{
		a = getch();

		if (a >= 32 && a <= 126)
		{
			F[i] = a;
			i++;
			cout << "*";
		}

		if (a == '\b' && i >= 1)
		{
			cout << "\b \b";
			i--;
		}

		if (a == '\r')
		{
			F[i] = '\0';
			break;
		}
	}
	pass = F;

	bool spe_check = false, upp_check = false, low_check = false, num_check = false;

	if (pass.length() != 8)
	{
		cout << "\nIncorrect Format!\n";
		goto pass;
	}

	for (int i = 0; i < 8; i++)
	{
		if (int(pass[i]) >= 48 && int(pass[i]) <= 57)
		{
			num_check = true;
		}
		else if (int(pass[i]) >= 65 && int(pass[i]) <= 90)
		{
			upp_check = true;
		}
		else if (int(pass[i]) >= 97 && int(pass[i]) <= 122)
		{
			low_check = true;
		}
		else
		{
			spe_check = true;
		}
	}

	if (num_check && spe_check && upp_check && low_check)
	{
		cout << "Enter password (again for confirmation): ";
		//getline(cin, cpass);
		char F[32];
		char a;
		int i = 0;
		while (1)
		{
			a = getch();

			if (a >= 32 && a <= 126)
			{
				F[i] = a;
				i++;
				cout << "*";
			}

			if (a == '\b' && i >= 1)
			{
				cout << "\b \b";
				i--;
			}

			if (a == '\r')
			{
				F[i] = '\0';
				break;
			}
		}
		cpass = F;


		if (pass == cpass)
		{
			cout << "\nPassword confirmed!\n";
		}
		else
		{
			cout << "\nPassword doesn't match.\n";
			goto pass;
		}
	}
	else
	{
		cout << "Wrong Format.\n";
		goto pass;
	}

	string pin;
pin:
	cout << "Enter four digit pin: ";
	//getline(cin, pin);

	char X[32];
	i = 0;
	while (1)
	{
		a = getch();

		if (a >= 32 && a <= 126)
		{
			X[i] = a;
			i++;
			cout << "*";
		}

		if (a == '\b' && i >= 1)
		{
			cout << "\b \b";
			i--;
		}

		if (a == '\r')
		{
			X[i] = '\0';
			break;
		}
	}
	pin = X;

	if (pin.length() != 4)
		goto pin;

	string name;
	cout << "Enter name: ";
	getline(cin, name);

cnic:
	long long cnic;
	cout << "Enter CNIC: ";
	cin >> cnic;
	cin.ignore();
	if (!(cnic > 0 && to_string(cnic).length() == 13))
	{
		cout << "Invalid CNIC!\n";
		goto cnic;
	}
	if (!uniquecnic(to_string(cnic)))
	{
		cout << "CNIC already exists.\n";
		goto cnic;
	}

	curuser.setdata(name, cnic, un, pass, pin);

	passenger_file.open("passenger.txt", ios::app);

	passenger_file << un << "\t" << pass << "\t" << pin << "\t" << name << "\t" << cnic << "\n";

	passenger_file.close();
}

void NPAFS::adminlogin()
{
	admin_file.open("admin.txt", ios::in);

	if (admin_file.is_open())
	{
		cout << "File is opened.\n";
	}

	string username;
againuserinput:
	cout << "Enter username (blank spaces aren't allowed): ";
	cin >> username;
	cin.ignore();
	string temp;

	getline(admin_file, temp);
	string us;
	int pos = temp.find("\t");
	us = temp.substr(0, pos);

	if (username == us)
	{
		if (checkpassword(temp))
		{
			cout << "Logged in, successfully!\n";
			curadmin.setdata(temp);
			admin_file.close();
			return;
		}
	}
	while (!admin_file.eof())
	{
		getline(admin_file, temp);
		pos = temp.find("\t");
		us = "NULL";
		us = temp.substr(0, pos);

		if (username == us)
		{
			if (checkpassword(temp))
			{
				cout << "Logged in, successfully!\n";
				curadmin.setdata(temp);
				admin_file.close();
				return;
			}
		}
	}
	admin_file.close();

	admin_file.open("admin.txt", ios::in);

	cout << "Username not found.\n"
		<< "Please enter username again.\n";
	goto againuserinput;
}

NPAFS::~NPAFS()
{
	delete[] flights, cities;
}

int main()
{
	NPAFS obj;

	obj.menu();
}