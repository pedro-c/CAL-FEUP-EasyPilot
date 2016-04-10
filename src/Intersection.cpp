/*
 * Intersection.cpp
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#include "Intersection.h"

Intersection::Intersection(unsigned int id) : id(id) {}
Intersection::Intersection(){}

unsigned int Intersection::getId() const{
	return id;
}
