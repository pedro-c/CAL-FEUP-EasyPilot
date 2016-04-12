/*
 * Coordinates.h
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#ifndef SRC_COORDINATES_H_
#define SRC_COORDINATES_H_

using namespace std;

class Coordinates{
	unsigned int id;
	double latitude;
	double longitude;
	double x;
	double y;

public:
	Coordinates();
	Coordinates(unsigned int id,double latitude, double longitude, double x, double y);
	unsigned int getId() const;
	double getX() const;
	double getY() const;
	double getLatitude() const;
	double getLongitude() const;
	double getDistance(const Coordinates &c) const;
};



#endif /* SRC_COORDINATES_H_ */
