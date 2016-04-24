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

vector<Edge*> Vertex::getAdj() const{
	return adj;
}

Point Vertex::getInfo() const{
	return info;
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

double Vertex::getDistance() const {
	return minDistance;
}

string Vertex::getRoadName() const {
	if(adj.size() == 1)
		return adj[0]->road->getName();
	else if (adj.size() > 1) {
		return "Interseção entre " + adj[0]->road->getName() + " e " + adj[1]->road->getName();
	}
	else return "";
}

bool Vertex::operator!=(const Vertex &rhs) {
	return !(*this == rhs);
}



