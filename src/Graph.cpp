/*
 * Graph.cpp
 *
 *  Created on: 18/04/2016
 *      Author: Bernardo
 */

#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cfloat>

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

/*list<Vertex*> Graph::getShortestPath(Vertex* start, Vertex* goal) {
	if(lastComputedPath == NULL || start != lastComputedPath)
		computePaths(start);

	list<Vertex*> path = list<Vertex*>();
	Vertex* v = goal;

	while(v->previous != NULL) {
		path.push_front(v->previous);
	}

	return path;
}

void Graph::computePaths(Vertex *start) {
	resetVertexes();

	lastComputedPath = start;

	start->previous = NULL;
	start->minDistance = 0;
	vector<Vertex*> vertexVector = vector<Vertex*>();
	vertexVector.push_back(start);
	sort(vertexVector.begin(), vertexVector.end());

	while(!vertexVector.empty()) {
		Vertex* u = vertexVector.front();
		u->visited = true;
		vertexVector.erase(vertexVector.begin());

		for(unsigned int i = 0; i < u->adj.size(); i++) {
			Edge* e = u->adj[i];
			Vertex* v = e->dest;
			if(v->visited)
				continue;
			double distance = e->distance;
			double distanceThroughU = u->minDistance + distance;

			if(distanceThroughU < v->minDistance) {
				vector<Vertex*>::iterator vertexIndex;
				if((vertexIndex = find(vertexVector.begin(), vertexVector.end(), v)) != vertexVector.end()) {
					vertexVector.erase(vertexIndex);

					v->minDistance = distanceThroughU;
					v->previous = u;

					vertexVector.push_back(v);
					sort(vertexVector.begin(), vertexVector.end());
				}
			}
		}
	}
}*/

void Graph::computePaths(Vertex *start) { }

list<Vertex*> Graph::getShortestPath(Vertex* start, Vertex* goal) {
	map<unsigned int, double> min_distance = map<unsigned int, double>();
	int source, target;

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		min_distance.insert(vertexSet[i].info.getId(), DBL_MAX);
	}

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		if(*goal == vertexSet[i]) {
			target = i;
		}
	}

	min_distance[ source ] = 0;
	set< pair<int, Vertex*> > active_vertices;
	active_vertices.insert( {0, start} );

	while (!active_vertices.empty()) {
		Vertex* where = active_vertices.begin()->second;
		if (where == goal)
			return min_distance[where];
		active_vertices.erase( active_vertices.begin() );
		for (unsigned int i = 0; i < where->adj.size(); i++) {
			Edge* edge = where->adj[i];
			if (min_distance[edge->dest] > min_distance[where] + edge->distance) {
				active_vertices.erase( { min_distance[edge->dest], edge->dest } );
				min_distance[edge->dest] = min_distance[where] + edge->distance;
				active_vertices.insert( { min_distance[edge->dest], edge->dest } );
			}
		}

	}
	return DBL_MAX;
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

