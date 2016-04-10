/*
 * Coordinates.cpp
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#include "Coordinates.h"
#include <cmath>
#include <ctgmath>

Coordinates::Coordinates() : Coordinates(0, 0) { }

Coordinates::Coordinates(double x, double y) : x(x), y(y) {}


double Coordinates:: getX() const{
	return x;
}

double Coordinates:: getY() const{
	return y;
}

double Coordinates::getDistance(const Coordinates &c) const {
	return sqrt(pow((this->x-c.x),2)+ pow((this->y-c.y),2));
}

