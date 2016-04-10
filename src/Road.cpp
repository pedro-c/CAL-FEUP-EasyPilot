/*
 * Road.cpp
 */

#include "Road.h"


Road::Road(unsigned int id, const string &name, bool twoWay) :
	id(id), name(name), twoWay(twoWay) { }

void Road::setTwoWay(bool twoWay) {
	this->twoWay = twoWay;
}

bool Road::getTwoWay() const {
	return twoWay;
}

void Road::setName(const string &name) {
	this->name = name;
}

const string& Road::getName() const {
	return this->name;
}

unsigned int Road::getId() const {
	return id;
}

bool Road::operator ==(const Road &p2) const {
	return (id == p2.id);
}

ostream & operator <<(ostream &os, Road &p) {
	os << p.getName();
	return os;
}
