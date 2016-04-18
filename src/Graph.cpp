/*
 * Graph.cpp
 *
 *  Created on: 18/04/2016
 *      Author: Bernardo
 */

#include "Graph.h"
#include <iostream>
#include <algorithm>

using namespace std;

Graph::Graph() : lastComputedPath(NULL) { }

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

list<Vertex*> Graph::getShortestPath(Vertex& start, Vertex& goal) {
	if(start != *lastComputedPath)
		computePaths(start);

	list<Vertex*> path = list<Vertex*>();
	Vertex* v = &goal;

	while(v->previous != NULL) {
		path.push_front(v->previous);
	}

	return path;
}

void Graph::computePaths(Vertex &start) {
	lastComputedPath = &start;

	start.previous = NULL;
	start.minDistance = 0;
	vector<Vertex> vertexVector = vector<Vertex>();
	vertexVector.push_back(start);
	sort(vertexVector.begin(), vertexVector.end());

	while(!vertexVector.empty()) {
		Vertex* u = &vertexVector.front();
		vertexVector.erase(vertexVector.begin());

		for(unsigned int i = 0; i < u->adj.size(); i++) {
			Edge* e = u->adj[i];
			Vertex* v = e->dest;
			double distance = e->distance;
			double distanceThroughU = u->minDistance + distance;

			if(distanceThroughU < v->minDistance) {
				vertexVector.erase(find(vertexVector.begin(), vertexVector.end(), *v));

				v->minDistance = distanceThroughU;
				v->previous = u;

				vertexVector.push_back(*v);
				sort(vertexVector.begin(), vertexVector.end());
			}
		}
	}
}

Vertex* Graph::getVertex(unsigned int pointID) {
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i].info.getId() == pointID)
			return &vertexSet[i];
	}

	return NULL;
}

