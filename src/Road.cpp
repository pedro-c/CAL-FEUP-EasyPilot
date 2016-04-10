/*
* Person.cpp
*/

#include "Road.h"

Road::Road(string n, int a) : name(n), age(a) {}
Road::Road() {}

string Road::getName() const {
	return name;
}

bool Road::operator == (const Road &p2) const {
	return (name == p2.name && age == p2.age);
}

ostream & operator << (ostream &os, Road &p) {
	os << p.getName();
	return os;
}
