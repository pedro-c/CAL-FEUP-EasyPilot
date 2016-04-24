/*
 * Edge.cpp
 *
 *  Created on: 18/04/2016
 *      Author: Bernardo
 */

#include "Edge.h"

unsigned int Edge::nextEdgeID = 0;

Edge::Edge(Vertex *s, Vertex *d, Road* road, double distance) :
	source(s), destination(d), road(road), distance(distance), edgeID(nextEdgeID) {
	nextEdgeID++;
}

Vertex* Edge::getSource() const{
	return source;
}

Vertex* Edge::getDestination() const{
	return destination;
}

string Edge::getRoadName() const{
	return road->getName();
}

Road* Edge::getRoad() const{
	return road;
}

void Edge::setEdgeID(int id){
	edgeID=id;
}
unsigned int Edge::getEdgeID() const{
	return edgeID;
}
