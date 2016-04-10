#pragma once

#include <string>
using namespace std;

class Road {
	string name;
	unsigned int id;
	double latitude;
	double longitude;
	double offsetX;
	double offsetY;

public:
	Road();
	Road(string n, unsigned int id, double latitude, double longitude, double offsetX, double offsetY);
	string getName() const;
	unsigned int getId() const;
	double getLatitude() const;
	double getLongitude() const;
	double getOffsetX() const;
	double getOffsetY() const;
	bool operator == (const Road &p2) const;
	friend ostream & operator << (ostream &os, Road &p);
};


