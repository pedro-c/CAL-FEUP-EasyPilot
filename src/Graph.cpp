/*
 * Graph.cpp
 *
 *  Created on: 18/04/2016
 *      Author: Bernardo
 */

#include "Graph.h"
#include <iostream>

using namespace std;

int Graph::getNumVertex() const {
	return vertexSet.size();
}

bool Graph::addVertex(const Point &in) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info == in)
			return false;
	}

	vertexSet.push_back(Vertex(in));
	return true;
}

bool Graph::addEdge(const Point &sourc, const Point &dest, Road* road,
		double distance) {
	int sourceIndex = 0;
	int destIndex = 0;
	bool hasSource, hasDest;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info == sourc) {
			sourceIndex = i;
			hasSource = true;
		}
	}

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info == dest) {
			destIndex = i;
			hasDest = true;
		}
	}

	if (!hasDest || !hasSource)
		return false;

	Edge* edge = new Edge(&vertexSet[sourceIndex], &vertexSet[destIndex], road, distance);
	vertexSet[sourceIndex].adj.push_back(edge);

	if (road->getTwoWay())
		vertexSet[destIndex].adj.push_back(edge);

	return true;
}

void Graph::printVertexes() const {
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		cout << vertexSet[i].info << " and have " << vertexSet[i].adj.size()
				<< " edges.\n";
	}
}

vector<Vertex> Graph::getShortestPath(Vertex* start, Vertex* goal) {

}

Vertex* Graph::getVertex(unsigned int pointID) {
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info.getId() == pointID)
			return &vertexSet[i];
	}

	return NULL;
}

