#pragma once

#include <string>
#include "Coordinates.h"

using namespace std;

class Road {
	unsigned int id;
	Coordinates initialPos;
	Coordinates offset;
	double length;
	string name;
	bool twoWay;
public:
	Road(unsigned int id, const Coordinates &initialPos, const Coordinates &offset);
	Road(unsigned int id, double latitude, double longitude, double offsetX, double offsetY);
	void setName(const string &name);
	const string& getName() const;
	void setTwoWay(bool twoWay);
	bool getTwoWay() const;
	unsigned int getId() const;
	Coordinates getInitialPos() const;
	double getLatitude() const;
	double getLongitude() const;
	Coordinates getOffset() const;
	double getOffsetX() const;
	double getOffsetY() const;
	double getLength() const;
	bool operator == (const Road &p2) const;
	friend ostream & operator << (ostream &os, Road &p);
};


