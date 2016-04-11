/*
 * Intersection.h
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#ifndef SRC_INTERSECTION_H_
#define SRC_INTERSECTION_H_

#include "Coordinates.h"

using namespace std;

class Intersection{
	unsigned int id;
	Coordinates position;
	Coordinates projection;
public:
	Intersection(unsigned int id, double posX, double posY, double projX, double projY);
	Intersection(unsigned int id, const Coordinates &position, const Coordinates &projection);
	unsigned int getId() const;
	Coordinates getPosition() const;
	double getLatitude() const;
	double getLongitude() const;
	Coordinates getProjection() const;
	double getProjectionX() const;
	double getProjectionY() const;
};


#endif /* SRC_INTERSECTION_H_ */
