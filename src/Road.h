#pragma once

#include <string>

using namespace std;

class Road {
	unsigned int id;
	string name;
	bool twoWay;
public:
	Road();
	Road(unsigned int id, bool twoWay);
	Road(unsigned int id, const string &name, bool twoWay);
	void setName(const string &name);
	const string& getName() const;
	void setTwoWay(bool twoWay);
	bool getTwoWay() const;
	unsigned int getId() const;
	bool operator == (const Road &p2) const;
	friend ostream & operator << (ostream &os, Road &p);
};


