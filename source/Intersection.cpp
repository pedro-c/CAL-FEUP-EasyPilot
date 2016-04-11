/*
 * Intersection.cpp
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#include "Intersection.h"

Intersection::Intersection(unsigned int id, double posX, double posY, double projX, double projY) :
	Intersection(id, Coordinates(posX, posY), Coordinates(projX, projY)) { }

Intersection::Intersection(unsigned int id, const Coordinates &position, const Coordinates &projection) :
	id(id), position(position), projection(projection) { }

unsigned int Intersection::getId() const{
	return id;
}

Coordinates Intersection::getPosition() const {
	return position;
}

double Intersection::getLatitude() const {
	return position.getX();
}

double Intersection::getLongitude() const {
	return position.getY();
}

Coordinates Intersection::getProjection() const {
	return projection;
}

double Intersection::getProjectionX() const {
	return projection.getX();
}

double Intersection::getProjectionY() const {
	return projection.getY();
}