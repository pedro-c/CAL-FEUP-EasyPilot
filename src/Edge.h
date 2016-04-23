/*
 * Edge.h
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include <vector>
#include "Graph.h"
#include "Road.h"


class Vertex;
class Graph;

class Edge {
	Vertex* src;
	Vertex* dest;
	unsigned int edgeID = 0;
	Road* road;
	double distance;
public:
	Edge(Vertex* s, Vertex *d, Road* road, double distance);
	Vertex* getSrc() const;
	Vertex* getDest() const;
	void setEdgeID(int id);
	int getEdgeID() const;
	Road* getRoad() const;
	string getRoadName() const;
	friend class Graph;
	friend class Vertex;
};

#endif /* SRC_EDGE_H_ */
