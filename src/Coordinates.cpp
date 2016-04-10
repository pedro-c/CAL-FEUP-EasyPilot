/*
 * Coordinates.cpp
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#include "Coordinates.h"
#include <cmath>
#include <ctgmath>

Coordinates::Coordinates(double x, double y) : x(x), y(y) {}
Coordinates::Coordinates(){}


double Coordinates:: getX() const{
	return x;
}

double Coordinates:: getY() const{
	return y;
}

double Coordinates::getDistance(Coordinates c1, Coordinates c2){
	return sqrt(pow((c2.x-c1.x),2)+ pow((c2.y-c1.y),2));
}

