/*
 * Coordinates.h
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include "Road.h"
#include <math.h>
#define PI 3.14159265359

using namespace std;


class Point{
	unsigned long id;
	double latitude;
	double longitude;
	double x;
	double y;
	string POI = "";

public:
	Point();
	Point(unsigned long id,double latitude, double longitude, double x, double y);
	unsigned long getId() const;
	double getX() const;
	double getY() const;
	double getLatitude() const;
	double getLongitude() const;
	void setPOI(string POI);
	string getPOI() const;
	double getDistance(const Point &c) const;
	bool operator==(const Point &rhs) const;
	friend ostream &operator<<(ostream& out, const Point &point);
};


#endif /* SRC_POINT_H_ */
