/*
 * Vertex.cpp
 *
 *  Created on: 18/04/2016
 *      Author: Bernardo
 */

#include "Vertex.h"

Vertex::Vertex(const Point &in) :
		info(in), visited(false) {
}

bool Vertex::operator==(const Vertex &rhs) {
	return this->info == rhs.info;
}




