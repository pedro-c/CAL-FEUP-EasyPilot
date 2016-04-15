/*
 * Coordinates.cpp
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */
#include "Point.h"

#include "Road.h"
#include <cmath>
#include <iostream>


Point::Point(){
	this->road = 0;
	this->id=0;
	this->x=0;
	this->y=0;
	this->latitude=0;
	this->longitude=0;
}

Point::Point(Road* road, unsigned int id,double latitude, double longitude, double x, double y) {
	this->road=road;
	this->id=id;
	this->latitude=latitude;
	this->longitude=longitude;
	this->x=x;
	this->y=y;

}

void Point::setRoad(Road* road) {
	this->road = road;
}

unsigned int Point::getRoadId() const{
	return road->getId();
}


unsigned int Point:: getId() const{
	return id;
}


double Point:: getX() const{
	return x;
}

double Point:: getY() const{
	return y;
}

double  Point:: getLatitude() const{
	return latitude;
}

double  Point:: getLongitude() const{
	return longitude;
}

double Point::getDistance(const Point &c) const {
	return sqrt(pow((this->x-c.x),2)+ pow((this->y-c.y),2));
}

bool Point::operator==(const Point &rhs) const {
	return this->id == rhs.id;
}

ostream& operator<<(ostream& out, const Point &point) {
	out << "ID: " << point.id << "\tLatitude: " << point.latitude << "\tLongitude: " << point.longitude;
	return out;
}

