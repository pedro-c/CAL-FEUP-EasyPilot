/*
 * Graph.cpp
 *
 *  Created on: 18/04/2016
 *      Author: Bernardo
 */

#include "Graph.h"
#include "Vertex.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cfloat>
#include <queue>

using namespace std;

Graph::Graph() : lastComputedPath(NULL) { }

int Graph::getNumVertex() const {
	return vertexSet.size();
}

vector<Vertex> Graph::getVertexSet() const {
	return vertexSet;
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

list<Vertex*> Graph::getShortestPath(Vertex* source, Vertex* goal) {
	if(lastComputedPath == NULL || source != lastComputedPath)
		computePaths(source);

	list<Vertex*> path = list<Vertex*>();
	Vertex* v = goal;

	while(v->previous != NULL) {
		path.push_front(v->previous);
		v = v->previous;
	}

	return path;
}

void Graph::computePaths(Vertex* source) {
	resetPathfinding();

	source->minDistance = 0;

	priority_queue<Vertex*> toBeProcessed = priority_queue<Vertex*>();
	toBeProcessed.push(source);

	while(!toBeProcessed.empty()) {
		Vertex* beingProcessed = toBeProcessed.top();
		toBeProcessed.pop();
		beingProcessed->visited = true;

		for(unsigned int i = 0; i < beingProcessed->adj.size(); i++) {
			Vertex* dest = beingProcessed->adj[i]->dest;
			double distanceToDest = beingProcessed->adj[i]->distance + beingProcessed->minDistance;

			if(distanceToDest < dest->minDistance) {
				dest->minDistance = distanceToDest;
				dest->previous = beingProcessed;
			}

			if(!dest->visited) {
				toBeProcessed.push(dest);
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

void Graph::resetVertexes() {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i].visited = false;
	}
}

void Graph::resetPathfinding() {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i].visited = false;
		vertexSet[i].minDistance = DBL_MAX;
		vertexSet[i].previous = NULL;
	}
}
