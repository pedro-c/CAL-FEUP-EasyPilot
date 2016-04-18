/*
 * Vertex.cpp
 *
 *  Created on: 18/04/2016
 *      Author: Bernardo
 */

#include "Vertex.h"
#include <limits>

Vertex::Vertex(const Point &in) :
		info(in), visited(false), minDistance(numeric_limits<double>::infinity()), previous(NULL) {
}

bool Vertex::operator==(const Vertex &rhs) {
	return this->info == rhs.info;
}

bool Vertex::operator<(const Vertex &rhs) {
	return this->minDistance < rhs.minDistance;
}

bool Vertex::operator!=(const Vertex &rhs) {
	return !(*this == rhs);
}



