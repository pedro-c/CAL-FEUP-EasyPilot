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
	double x;
	double y;
public:
	Coordinates();
	Coordinates(double x, double y);
	double getX() const;
	double getY() const;
	double getDistance(Coordinates c1, Coordinates c2);

};



#endif /* SRC_COORDINATES_H_ */
