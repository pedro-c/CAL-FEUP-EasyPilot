/*
 * Coordinates.cpp
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#include "Coordinates.h"
#include <cmath>

Coordinates::Coordinates(){
	this->id=0;
	this->x=0;
	this->y=0;
	this->latitude=0;
	this->longitude=0;
}

Coordinates::Coordinates(unsigned int id,double latitude, double longitude, double x, double y) {
	this->id=id;
	this->latitude=latitude;
	this->longitude=longitude;
	this->x=x;
	this->y=y;

}

unsigned int Coordinates:: getId() const{
	return id;
}


double Coordinates:: getX() const{
	return x;
}

double Coordinates:: getY() const{
	return y;
}

double  Coordinates:: getLatitude() const{
	return latitude;
}

double  Coordinates:: getLongitude() const{
	return longitude;
}

double Coordinates::getDistance(const Coordinates &c) const {
	return sqrt(pow((this->x-c.x),2)+ pow((this->y-c.y),2));
}

