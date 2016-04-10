/*
 * Person.cpp
 */

#include "Road.h"

Road::Road(unsigned int id, const Coordinates &initialPos,
		const Coordinates &offset) :
		id(id), initialPos(initialPos), offset(offset) {
	name = "";
	twoWay = true;
	length = initialPos.getDistance(offset);
}

Road::Road(unsigned int id, double latitude, double longitude, double offsetX, double offsetY) : Road(id, Coordinates(latitude, longitude), Coordinates(offsetX, offsetY)) {
}

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

Coordinates Road::getInitialPos() const {
	return initialPos;
}

double Road::getLatitude() const {
	return initialPos.getX();
}

double Road::getLongitude() const {
	return initialPos.getY();
}

double Road::getOffsetX() const {
	return offset.getX();
}

double Road::getOffsetY() const {
	return offset.getY();
}

Coordinates Road::getOffset() const {
	return offset;
}

double Road::getLength() const {
	return length;
}

bool Road::operator ==(const Road &p2) const {
	return (id == p2.id);
}

ostream & operator <<(ostream &os, Road &p) {
	os << p.getName();
	return os;
}
