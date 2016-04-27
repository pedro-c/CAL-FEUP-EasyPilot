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
	vector<Vertex> getVertexSet() const;
	bool addVertex(const Point &in);
	bool addEdge(const Point &sourc, const Point &dest, Road* road);
	void printVertexes() const;
	list<Vertex*> getShortestPath(Vertex* source, Vertex *goal);
	Vertex* getVertexFromID(unsigned int pointID);
	Vertex* getVertexFromRoadName(const string &roadName);
	unsigned int getVertexSetSize() const;
	Vertex* getVertexFromIndex(unsigned int index);
private:
	void computePaths(Vertex* source);
	void resetVertexes();
	void resetPathfinding();
};

#endif /* GRAPH_H_ */
