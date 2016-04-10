/*
 * Person.cpp
 */

#include "Road.h"

Road::Road(string n, unsigned int id, double latitude, double longitude, double offsetX, double offsetY) : name(n), id(id), latitude(latitude), longitude(longitude), offsetX(offsetX), offsetY(offsetY) {}
Road::Road() {}

string Road::getName() const {
	return name;
}

unsigned int Road:: getId() const{
	return id;
}
double Road:: getLatitude() const{
	return latitude;
}
double Road:: getLongitude() const{
	return longitude;
}
double Road:: getOffsetX() const{
	return offsetX;
}
double Road:: getOffsetY() const{
	return offsetY;
}

bool Road::operator == (const Road &p2) const {
	return (id==p2.id);
}

ostream & operator << (ostream &os, Road &p) {
	os << p.getName();
	return os;
}
