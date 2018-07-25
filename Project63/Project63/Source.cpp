#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <winapifamily.h>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <vector>




using namespace std;



const int n = 3; // can be made a memeber variable for class creating train objects
string trainType; // can be made a member variable for factory creating train-type object



 class cdt {

 public:
     static cdt* createInstance();
	 const std::string currentDateTime() {
		 time_t     now = time(0);
		 struct tm  tstruct;
		 char       buf[80];
		 localtime_s(&tstruct, &now);
		 // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		 // for more information about date/time format
		 strftime(buf, sizeof(buf), "%m-%d-%Y(%X)", &tstruct);

		 return buf;
	 }

 private:
	 cdt();
	 static cdt* T;
	 

};

 cdt::cdt() {}

 cdt* cdt::T = NULL;

 cdt* cdt::createInstance() {
 
	 if (T == NULL) {
	 
		 T = new cdt();
		 
	 }
	 
	 return T;
 }

 //class cdt {
 //public:
	// static cdt* createInstance() {
	// 
	//	 static cdt* T;
	//	 return T;
	// };
	// const std::string currentDateTime() {
	//	 time_t     now = time(0);
	//	 struct tm  tstruct;
	//	 char       buf[80];
	//	 localtime_s(&tstruct, &now);
	//	 // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	//	 // for more information about date/time format
	//	 strftime(buf, sizeof(buf), "%m-%d-%Y(%X)", &tstruct);
	//	 return buf;
	// }
 //private:
	// cdt();
	// 
	//};   // Meyer's Singleton : "More Efficient form of Singleton Design Pattern"


//add multiple methods for different costs, cancel-cost, ticket-cost, food-cost etc.
 class Tcost {

public: 
	void virtual calculate(int &a, string trainType) = 0;

};

// too rigid, need a data structure holding train objects which can automatically show the seating based on train type
class Avaliability {

public:

	void coachSelection(int &x) {
		cout << "Select Which train you want to check avaliability : " << endl;
		cout << "1. Bridgeport to New York " << endl;
		cout << "2. Bridgeport to New Jersey  " << endl << endl;
		cin >> x;
		cin.ignore();
	}

	void show(int a[][n], int b[][n], int c[][n], int d[][n], int n, int x) {

		cdt *cdt = cdt::createInstance();

		for (int i = 0; i < n; i++) {

			for (int j = 0; j < n; j++) {

				if(trainType == "NT"){
				if (x == 1)
				{
					cout << a[i][j] << "   ";
				}
				if (x == 2) {

					cout << b[i][j] << "    ";
				}
				}

				if (trainType == "ET") {
					if (x == 1)
					{
						cout << c[i][j] << "   ";
					}
					if (x == 2) {

						cout << d[i][j] << "    ";
					}
				}
			}

			cout << endl;
		}

		cout << cdt->currentDateTime();
		cout << endl;

	}

};


 /*no need to inherit, violating single responsibility
  * file_in, confirm, print ticket -> can be condensed into one, infact can be moved out completely(?) - file operations
  * preference, give ticket are unnecesarily lenghtly
  */
 class reservation : public Tcost {

	 cdt *cdt = cdt::createInstance();
	 int cost;

public:


	void file_in(string &name, int &age, string &g, string &f, string &s) {


		ifstream istream;
		cout << "Create & Enter Notepad  file directory containing Required info in the following order : " << endl << " Name on first line & Age, Gender, Food Choice on Second line" << endl;
		getline(cin, s);
		istream.open(s);
		getline(istream, name);
		istream >> age;
		istream >> g;
		istream >> f;

		istream.close();

		cout << name << "  " << age << "  " << g << "  " << f << endl;
	
	}

	void confirm(string &name, int &age, string &g, string &f, string s) {


		char c;

		cout << endl;
		cout << "Are these your reservation final details : Y/N" << endl;
		cin >> c;
		cin.ignore();
		if (c == 'Y' || c == 'y') {

			return;
		}
		if (c == 'N' || c == 'n') {

			cout << "Change your details in the file:  " << endl;
			file_in(name, age, g, f, s);

		}
	}

	void calculate(int &age, string trainType) {


		if (trainType == "NT") {
		
			if (age <= 18 || age >= 55) {

				cost = 50;

			}
			if (age > 18 && age < 55) {

				cost = 200;

			}
		
		}

		if (trainType == "ET") {

			if (age <= 18 || age >= 55) {

				cost = 25;

			}
			if (age > 18 && age < 55) {

				cost = 400;

			}

		}


	}

	int preference(int a[][n], int b[][n], int c[][n], int d[][n], int n, int x, string& s) {

		int scount = 0;
		cout << "Would you prefer Window or Non-Window Seat: W/NW " << endl;
		cin >> s;

		if (trainType == "NT") {
			if (s == "W" || s == "w") {

				if (x == 1) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) == 0) {

									if (a[i][j] == 0) { scount += 1; }
								}

							}

							else {

								if (((i + j) % 2) != 0) {

									if (a[i][j] == 0) { scount += 1; }
								}

							}

						}
					}

				}
				if (x == 2) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) == 0) {

									if (b[i][j] == 0) { scount += 1; }
								}

							}

							else {

								if (((i + j) % 2) != 0) {

									if (b[i][j] == 0) { scount += 1; }
								}

							}

						}
					}

				}
			}
			if (s == "NW" || s == "Nw" || s == "nW" || s == "nw") {


				if (x = 1) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) != 0) {

									if (a[i][j] == 0) { scount += 1; }
								}

							}


						}
					}
				}

				if (x = 2) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) != 0) {

									if (b[i][j] == 0) { scount += 1; }
								}

							}


						}
					}
				}

			}
		}

		if (trainType == "ET") {
			if (s == "W" || s == "w") {

				if (x == 1) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) == 0) {

									if (c[i][j] == 0) { scount += 1; }
								}

							}

							else {

								if (((i + j) % 2) != 0) {

									if (c[i][j] == 0) { scount += 1; }
								}

							}

						}
					}

				}
				if (x == 2) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) == 0) {

									if (d[i][j] == 0) { scount += 1; }
								}

							}

							else {

								if (((i + j) % 2) != 0) {

									if (d[i][j] == 0) { scount += 1; }
								}

							}

						}
					}

				}
			}
			if (s == "NW" || s == "Nw" || s == "nW" || s == "nw") {


				if (x = 1) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) != 0) {

									if (c[i][j] == 0) { scount += 1; }
								}

							}


						}
					}
				}

				if (x = 2) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) != 0) {

									if (d[i][j] == 0) { scount += 1; }
								}

							}


						}
					}
				}

			}
		}

		if (scount == 0)
		{
			cout << "No Avalaibility";
		}
		return scount;
	}

	int giveSeat(int a[][n], int b[][n], int c[][n], int d[][n], int n, int scount, string& s, int x) {

		int seatnum;

		if (trainType == "NT") {
			if (scount != 0 && (s == "W" || s == "w")) {

				if (x == 1) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) == 0) {

									if (a[i][j] == 0) {
										a[i][j] = (i + rand());
										seatnum = a[i][j];
										return seatnum;

									}
								}

							}
							else {

								if (((i + j) % 2) != 0) {

									if (a[i][j] == 0) {
										a[i][j] = (i + j);
										seatnum = (i + j);
										return seatnum;
									}
								}

							}

						}
					}

				}
				if (x == 2) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) == 0) {

									if (b[i][j] == 0) {

										b[i][j] = (i + rand());
										seatnum = b[i][j];
										return seatnum;

									}
								}
							}

							else {

								if (((i + j) % 2) != 0) {

									if (b[i][j] == 0) {
										b[i][j] = (i + j);
										seatnum = (i + j);
										return seatnum;
									}
								}

							}

						}
					}
				}
			}
	        if (scount != 0 && s == "NW" || s == "Nw" || s == "nW" || s == "nw") {

				if (x == 1) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) != 0) {

									if (a[i][j] == 0) {
										a[i][j] = (i + (rand() % 10));
										seatnum = a[i][j];
										return seatnum;
									}
								}

							}

							else {

								if (((i + j) % 2) == 0) {

									if (a[i][j] == 0) {

										a[i][j] = (i + j);
										seatnum = (i + j);
										return seatnum;
									}
								}

							}

						}
					}

				}
				if (x == 2) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) != 0) {

									if (b[i][j] == 0) {
										b[i][j] = (i + rand());
										seatnum = b[i][j];
										return seatnum;
									}
								}

							}

							else {

								if (((i + j) % 2) == 0) {

									if (b[i][j] == 0) {

										b[i][j] = (i + j);
										seatnum = (i + j);
										return seatnum;
									}
								}

							}

						}
					}

				}

			}
		}

		if (trainType == "ET") {
			if (scount != 0 && (s == "W" || s == "w")) {

				if (x == 1) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) == 0) {

									if (c[i][j] == 0) {
										c[i][j] = (i + rand());
										seatnum = c[i][j];
										return seatnum;

									}
								}

							}
							else {

								if (((i + j) % 2) != 0) {

									if (c[i][j] == 0) {
										c[i][j] = (i + j);
										seatnum = (i + j);
										return seatnum;
									}
								}

							}

						}
					}

				}
				if (x == 2) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) == 0) {

									if (d[i][j] == 0) {

										d[i][j] = (i + rand());
										seatnum = d[i][j];
										return seatnum;

									}
								}
							}

							else {

								if (((i + j) % 2) != 0) {

									if (d[i][j] == 0) {
										d[i][j] = (i + j);
										seatnum = (i + j);
										return seatnum;
									}
								}

							}

						}
					}
				}
			}
			if (scount != 0 && s == "NW" || s == "Nw" || s == "nW" || s == "nw") {

				if (x == 1) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) != 0) {

									if (c[i][j] == 0) {
										c[i][j] = (i + (rand() % 10));
										seatnum = c[i][j];
										return seatnum;
									}
								}

							}

							else {

								if (((i + j) % 2) == 0) {

									if (c[i][j] == 0) {

										c[i][j] = (i + j);
										seatnum = (i + j);
										return seatnum;
									}
								}

							}

						}
					}

				}
				if (x == 2) {

					for (int i = 0; i < n; i++) {

						for (int j = 0; j < n; j++) {

							if (i % 2 == 0) {

								if (((i + j) % 2) != 0) {

									if (d[i][j] == 0) {
										d[i][j] = (i + rand());
										seatnum = d[i][j];
										return seatnum;
									}
								}

							}

							else {

								if (((i + j) % 2) == 0) {

									if (d[i][j] == 0) {

										d[i][j] = (i + j);
										seatnum = (i + j);
										return seatnum;
									}
								}

							}

						}
					}

				}

			}
		}
		return 0;
	}

	void printTicket(int& fseat, string s, int x, string trainType) {
	
	
		ofstream ostream;
		ostream.open(s, ios::app);

		ostream <<"\t" << x << "\t";
		ostream << fseat << "\t";
		ostream << "$" <<cost <<endl;
		ostream << cdt->currentDateTime() << endl << endl;
		ostream << "These are your Final " <<trainType<< " Reservation Details !!!" <<endl;
		ostream << "Symbol NT stands for Normal Train " << "  &  " << "Symbol ET stands for Express Train" << endl;
		ostream.close();
	
		cout << endl;
		cout << endl << "Printing your Seat and Travel cost ....." << endl;
		cout << "Processing Complete ...." << endl;
		cout << "Carry this conformation when you travel" << endl;
		cout << "Happy Journey !!!" << endl << endl;
	}

};

















/*cancellation class implements the memento feature
 *Design is improper - needs corrections
 */

class memento {

private:
	
	string _name;
	int   _age;
	string _gender;
	string _food;
	int _tnum;
	int _seat;
	string _foodcost;
	string _dt;
public:
	memento(const string &name, const int &age, const string &g, const string &f, const int &tnum, const int &seat, const string &y, const string &h)
	{

		
		_name = name;
		_age = age;
		_gender = g;
		_food = f;
		_tnum = tnum;
		_seat = seat;
		_foodcost = y;
		_dt = h;

	}


	string getName() {

		return  _name;
	}
	int getage() {

		return _age;
	}
	string getGender() {

		return  _gender;
	}
	string getFood() {

		return _food;
	}
	int getTnum() {


		return _tnum;
	}
	int getSeat() {

		return _seat;
	}
	string getFoodcost() {

		return _foodcost;
	}
	string getdt() {

		return _dt;
	}
};

class Originator {


	string _name;
	int _age;
	string _gender;
	string _food;
	int _tnum;
	int _seat;
	string _foodcost;
	string _dt;

public:
	memento* setState(const string &name, const int &age, const string &g, const string &f, const int &tnum, const int &seat, const string &y, const string &h) {

		memento* m = new memento(name, age, g, f, tnum, seat, y, h);

		_name = name;
		_age = age;
		_gender = g;
		_food = f;
		_tnum = tnum;
		_seat = seat;
		_foodcost = y;
		_dt = h;
		

		return m;
	}



	string getName() {

		return  _name;
	}     
	int getage() {

		return _age;
	}                  
	string getGender() {

		return  _gender;
	}
	string getFood() {

		return _food;
	}
	int  getTnum() {


		return _tnum;
	}
	int getSeat() {

		return _seat;
	}
	string getFoodcost() {

		return _foodcost;
	}
	string getdt() {

		return _dt;
	}


	void undo(memento *old) {

		_name = old->getName();
		_age = old->getage();
		_gender = old->getGender();
		_food = old->getFood();
		_tnum = old->getTnum();
		_seat = old->getSeat();
		_foodcost = old->getFoodcost();
		_dt = old->getdt();

	}

};

class caretaker {

	 vector<memento*> v;
	 Originator *o = new Originator();
	 memento* M;
	 vector<memento*> ::iterator i;


public:

	void takeBackup(const string &name, const int &age, const string& g, const string& f, const int& tnum, const int& tseat, const string& foodcost, const string& dt) {

		

		M = o->setState(name, age, g, f, tnum, tseat, foodcost, dt);
		v.push_back(M);

	}
	void restoreBackup() {


		string s;
		ofstream ostream;
		
			cin.ignore();
			cout << "Enter File name : " << endl;
			getline(cin, s);
			
			o->undo(v.front());

			ostream.open(s);
			ostream.trunc;
			ostream.close();

			ostream.open(s);

			ostream << o->getName() << endl;
			ostream << o->getage() << "  ";
			ostream << o->getGender() << "  ";
			ostream << o ->getFood() << "  ";
			ostream << o->getTnum() << "  ";
			ostream << o->getSeat() << "  ";
			ostream << o->getFoodcost() << endl;
			ostream << o->getdt() << endl << endl;
			ostream << "These are your Final " << trainType << " Reservation Details !!!" << endl;
			ostream << "Symbol NT stands for Normal Train " << "  &  " << "Symbol ET stands for Express Train" << endl;

	        ostream.close();

	
	}

};





/*
 * No need for inheritance
 * too much repeated code, unnecesary arguments
 */
class cancellation : public Tcost {


	 reservation rs;

public:


	cdt *t = cdt::createInstance();

	void confirm(string &s, int &x, int &fseat) {
	
		

		string name, g, f, dt, foodcost;
		int age, tnum, tseat;
		char c;

		ifstream istream;
		ofstream ostream;

		cout << "Enter file confirming your Registration:  " << endl;
		getline(cin, s);

		istream.open(s);

		getline(istream, name);              
		istream >> age;
		istream >> g;
		istream >> f;
		istream >> tnum;
		istream >> tseat;
		istream.ignore();
		getline(istream, foodcost); 
		istream.ignore();   
		getline(istream, dt);

		istream.close();


		cout << "Your Details are : " << endl;
		cout << name << endl;
		cout << age <<"   "<< g << "   " << f << "   " << tnum << "   " << tseat << "   "<< "   " << foodcost << "    "<<dt ;

		
		cout << endl;
		cout << "Are these your reservation final details : Y/N" << endl;
		cin >> c;
	

		if (c == 'Y' || c == 'y') {

			x = tnum;
			fseat = tseat;
			return;
		}
		else if (c == 'N' || c == 'n') {
			
			
			confirm(s,x,fseat);

		}

		else { 
			cout << "Enter Valid Input "; 
		}

	}

	void removeSeat(int a[][n], int b[][n], int c[][n], int d[][n], int n,int &x, int &fseat) {
	
		if (trainType == "NT") {
			if (x == 1) {

				for (int i = 0; i < n; i++) {

					for (int j = 0; j < n; j++) {

						if (a[i][j] == fseat) {

							a[i][j] = 0;
						}

					}
				}
			}

			if (x == 2) {

				for (int i = 0; i < n; i++) {

					for (int j = 0; j < n; j++) {

						if (b[i][j] == fseat) {

							b[i][j] = 0;
						}

					}
				}
			}
		}


		if (trainType == "ET") {
			if (x == 1) {

				for (int i = 0; i < n; i++) {

					for (int j = 0; j < n; j++) {

						if (c[i][j] == fseat) {

							c[i][j] = 0;
						}

					}
				}
			}

			if (x == 2) {

				for (int i = 0; i < n; i++) {

					for (int j = 0; j < n; j++) {

						if (d[i][j] == fseat) {

							d[i][j] = 0;
						}

					}
				}
			}
		}

	
	}

	int cancel(int a[][n], int b[][n], int c[][n], int d[][n], int n,int &fseat, string &s, int scount, int x, char& rsc) {
	

		caretaker cr;

		char c1,cha;
		string name, g, f, dt, foodcost;
		int age, tnum, tseat;
		int ccost = 0;

		ifstream istream;
		ofstream ostream;
         
		cin.ignore();

			cout << "Starting Cancellation with following Details..." << endl;

			istream.open(s);

			getline(istream, name);
			istream >> age;
			istream >> g;
			istream >> f;
			istream >> tnum;
			istream >> tseat;
			istream.ignore();
			getline(istream, foodcost);
			istream.ignore();
			getline(istream, dt);


			
		

			cout << name << endl << age << "   " << g << "   " << f << "   " << tnum << "   " << tseat << "   " << "   " << foodcost << "    " << dt;

			cout << endl;
			cout << "You will be charged with Cancellation fee ..." << endl;
			cout << "Confirm Cancellation : Y/N" << endl;
			cin >> c1;
			cin.ignore();

			if (c1 == 'Y' || c1 == 'y') {

				
				char ch;
				cout << endl;
				cout << "Do you want to Backup Current Info : Y/N  " << endl;
				cin >> ch;
				
				
				if (ch =='Y'||ch=='y') {
					
					cr.takeBackup(name, age, g, f, tnum, tseat, foodcost, dt);
				}
				
				ostream.open(s);
				ostream.trunc;
				calculate(ccost, trainType);
				ostream << "Fee for Cancellation is : " <<"$" << ccost;
				ostream.close();
    



				cout << "Cancellation Complete ..." << endl;


				cout << "Do you want to restore previous Y/N : " << endl;
				cin >> cha;

				if (cha == 'Y' || cha == 'y') {

				
					cr.restoreBackup();
					rsc = 'N';
					istream.close();
					return 0;

				}
				if (cha == 'Y' || cha == 'y') {
				
					istream.close();
					return 0;
				}

			}
			else if (c1 == 'N' || c1 == 'n') {

			
				cout << "Cancellation Stopped....." << endl;
				istream.close();
				return 0;

			}
        	else
			{
				cout << " Invalid Input " << endl;
				istream.close();
				return 0;
			}
		
			istream.close();
			return 0;
	}

	void calculate(int &ccost, string s) {

		ofstream ostream;

		if (s == "NT") {

			ccost = 5;
			cout << "Cost for Cancellation posted back to the file .... " << endl;
			ostream << "$" << 5 << endl;
			ostream << t->currentDateTime();
			ostream.close();
		}

		if (s == "ET") {

			ccost = 10;
			cout << "Cost for Cancellation posted back to the file .... " << endl;
			ostream << "$" << 10 << endl;
			ostream << t->currentDateTime();
			ostream.close();
		}

	}

};

/*
 * factory pattern in general
 * factory method would be sufficient
 *
 */
class Train {

public:
	void virtual startTicketReservation(Train* train) = 0;

};


class Normaltrain : public Train {


public:

	void startTicketReservation(Train* train) {

		::trainType = "NT";


	}

};


class Expresstrain : public Train {

public:

	void startTicketReservation(Train* train) {

		::trainType = "ET";

	}

};



//Interface for train type selection

class intermediate {


public:

	Train*  method() {

		int a;


		cout << "------------------------------------------------------------------------";
		cout << "                        Railway Reservation System               " << endl << endl;
		cout << "------------------------------------------------------------------------" << endl;



		cout << endl << "------------------------------------------------------------------------" << endl;
		cout << "Enter Your Transport Choice" << endl << endl;
		cout << "1. Normal Train   " << endl;
		cout << "2. Express Train   " << endl;
		cout << endl << "------------------------------------------------------------------------" << endl;

		cin >> a;
		cout << endl;
		cin.ignore();

		if (a != 1 && a != 2) {

			cout << "Enter Valid Choice : " << endl;
			method();
		}

		if (a == 1) {

			cout << "Transfering you to the next step ...." << endl;
			std::chrono::seconds dura(3);
			std::this_thread::sleep_for(dura);
			return new Normaltrain();

		}
		if (a == 2) {

			cout << "Transfering you to the next step ...." << endl;
			std::chrono::seconds dura(3);
			std::this_thread::sleep_for(dura);
			return new Expresstrain();

		}

		return nullptr;
	};


};



class reservationInterface {


	reservation res;
	Avaliability av;
	cancellation cl;


	void fill(int a[][n], int b[][n], int c[][n], int d[][n], int n) {


		for (int i = 0; i < n; i++) {

			for (int j = 0; j < n; j++) {

				a[i][j] = 0;
				b[i][j] = 0;
				c[i][j] = 0;
				d[i][j] = 0;

			}

		}

	}

	void ClearConsoleToColors(int ForgC, int BackC)
	{
		WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
		//Get the handle to the current output buffer...
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		//This is used to reset the carat/cursor to the top left.
		COORD coord = { 0, 0 };
		//A return value... indicating how many chars were written
		//   not used but we need to capture this since it will be
		//   written anyway (passing NULL causes an access violation).
		DWORD count;

		//This is a structure containing all of the console info
		// it is used here to find the size of the console.
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		//Here we will set the current color
		SetConsoleTextAttribute(hStdOut, wColor);
		if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
		{
			//This fills the buffer with a given character (in this case 32=space).
			FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

			FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
			//This will set our cursor position for the next print statement.
			SetConsoleCursorPosition(hStdOut, coord);
		}
		return;
	}

	int ny[n][n];
	int nj[n][n];
	int ny1[n][n];
	int nj1[n][n];


	string name, g, f, s, win;
	int a, x, age, scount, first = 0, fseat;
	ifstream istream;
	char character = 'Y', rsc;


public:


	void reserveTicket(string trainType) {


		ClearConsoleToColors(0, 15);


		if (character == 'Y' || character == 'N') {
			fill(ny, nj, ny1, nj1, n);
		}


		cout << "------------------------------------------------------------------------";
		cout << "           Railway Reservation System -  Ticket Reservation             " << endl << endl;
		cout << "------------------------------------------------------------------------" << endl;


		
		do {

			cout << endl << "------------------------------------------------------------------------" << endl;
			cout << "Enter Your Choice" << endl << endl;
			cout << "1. Reservation   " << endl;
			cout << "2. Cancellation   " << endl;
			cout << "3. Avaliability  " << endl << endl;
			cout << endl << "------------------------------------------------------------------------" << endl;

			cin >> a;
			cout << endl;
			cin.ignore();


			switch (a)
			{

			case 1:
				cout << "------------------------------------------------------------------------" << endl;
				cout << "Reservation Section" << endl << endl;

				av.coachSelection(x);
				res.file_in(name, age, g, f, s);
				res.confirm(name, age, g, f, s);
				res.calculate(age, trainType);
				scount = res.preference(ny, nj, ny1, nj1, n, x, win);
				if (scount != 0) {
					fseat = res.giveSeat(ny, nj, ny1, nj1, n, scount, win, x);
					res.printTicket(fseat, s, x, trainType);
				}
				cout << endl << "------------------------------------------------------------------------" << endl;
				break;

			case 2:
				cout << "------------------------------------------------------------------------" << endl;
				cout << "Cancellation Section" << endl << endl;
				cl.confirm(s, x, fseat);
				cl.cancel(ny, nj, ny1, nj1, n, fseat, s, scount, x, rsc);
				if (rsc == 'N') { break; }
				cl.removeSeat(ny, nj, ny1, nj1, n, x, fseat);
				cout << endl << "------------------------------------------------------------------------" << endl;
				break;

			case 3:
				cout << "------------------------------------------------------------------------" << endl;
				cout << "Avaliability Section" << endl << endl;
				av.coachSelection(x);
				av.show(ny, nj, ny1, nj1, n, x);
				cout << endl << "------------------------------------------------------------------------" << endl;
				break;

			default:
				cout << "Enter valid choice";
				break;

			}

			cout << "Do your want to continue : (Y/N)   ";
			cin >> character;
			cout << endl;

		} while (character == 'Y' || character == 'y');

		if (character == 'N' || character == 'n') {
			


			cout << "Transfering you to the Main Page ...." << endl;
			std::chrono::seconds dura(3);
			std::this_thread::sleep_for(dura);

			system("cls");
			ClearConsoleToColors(15, 0);
			intermediate i;
			Train* t = i.method();
			system("cls");
			ClearConsoleToColors(0, 15);
			reserveTicket(::trainType);
			

		
		}

	}

};


 class facadeInterface{
 
	 reservationInterface ri;

 public:

	 void  callRI() {
	 
		 ri.reserveTicket(trainType);
	 
	 }

	 void fi() {
		 

		 intermediate* i = new intermediate();
         Train* train = i->method();
         train->startTicketReservation(train);
            
	 }

 };



 int main() {

	 
	 facadeInterface i;

	 i.fi();
	 i.callRI();
	 system("pause");
	 return 0;

 }