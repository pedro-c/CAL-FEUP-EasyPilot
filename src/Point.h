/*
 * Coordinates.h
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include "Road.h"

using namespace std;


class Point{
	Road* road;
	unsigned int id;
	double latitude;
	double longitude;
	double x;
	double y;

public:
	Point();
	Point(Road* road, unsigned int id,double latitude, double longitude, double x, double y);
	unsigned int getId() const;
	void setRoad(Road* road);
	unsigned int getRoadId() const;
	double getX() const;
	double getY() const;
	double getLatitude() const;
	double getLongitude() const;
	double getDistance(const Point &c) const;
	bool operator==(const Point &rhs) const;
	friend ostream &operator<<(ostream& out, const Point &point);
};


#endif /* SRC_POINT_H_ */
