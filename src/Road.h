#pragma once

#include <string>
using namespace std;

class Road {
	string name;
	int age;
public:
	Road();
	Road(string n, int a);
	string getName() const;
	bool operator == (const Road &p2) const;
	friend ostream & operator << (ostream &os, Road &p);
};


