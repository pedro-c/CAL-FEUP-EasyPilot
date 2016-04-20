/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include "Point.h"
#include "Vertex.h"
#include "Edge.h"

class Edge;
class Vertex;

class Graph {
	vector<Vertex> vertexSet;
	Vertex* lastComputedPath;
public:
	Graph();
	int getNumVertex() const;
	bool addVertex(const Point &in);
	bool addEdge(const Point &sourc, const Point &dest, Road* road, double distance);
	void printVertexes() const;
	vector<Vertex*> getShortestPath(Vertex *goal);
	void Graph::computePaths(Vertex *start);
	Vertex* getVertex(unsigned int pointID);
	void getShortestDistance(Vertex* target, Vertex* source);
	void getShortestPathNames(Vertex* target);
private:
	//void computePaths(Vertex* start);
	//void resetVertexes();
};

#endif /* GRAPH_H_ */
