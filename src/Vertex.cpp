/*
 * Vertex.cpp
 *
 *  Created on: 18/04/2016
 *      Author: Bernardo
 */

#include "Vertex.h"
#include <cfloat>

Vertex::Vertex(const Point &in) :
		info(in), visited(false), minDistance(DBL_MAX), previous(NULL) {
}

bool Vertex::operator==(const Vertex &rhs) {
	return this->info == rhs.info;
}

bool Vertex::operator<(const Vertex &rhs) {
	return this->minDistance < rhs.minDistance;
}

Road* Vertex::getRoadBetween(Vertex* dest) const {
	for(unsigned int i = 0; i < adj.size(); i++) {
		if(adj[i]->dest == dest)
			return adj[i]->road;
	}

	return NULL;
}

bool Vertex::operator!=(const Vertex &rhs) {
	return !(*this == rhs);
}



