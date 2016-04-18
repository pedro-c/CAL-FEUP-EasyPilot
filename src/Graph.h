/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Point.h"
#include "Vertex.h"
#include "Edge.h"

class Edge;
class Vertex;

class Graph {
	vector<Vertex> vertexSet;
public:
	int getNumVertex() const;
	bool addVertex(const Point &in);
	bool addEdge(const Point &sourc, const Point &dest, Road* road, double distance);
	void printVertexes() const;
	vector<Vertex> getShortestPath(Vertex* start, Vertex* goal);
	Vertex* getVertex(unsigned int pointID);
};

#endif /* GRAPH_H_ */
