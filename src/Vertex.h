/*
 * Vertex.h
 *
 *  Created on: 10/04/2016
 *      Author: mariajoaomirapaulo
 */

#ifndef SRC_VERTEX_H_
#define SRC_VERTEX_H_

#include <vector>
#include "Graph.h"

class Edge;
class Graph;

class Vertex {
	friend class Graph;
	Point info;
	vector<Edge*> adj;
	bool visited;
	double minDistance;
	Vertex* previous;
public:
	Point getInfo() const;
	Vertex(const Point &in);
	Road* getRoadBetween(Vertex* dest) const;
	double getDistance() const;
	string getRoadName() const;
	bool operator==(const Vertex &rhs);
	bool operator<(const Vertex &rhs);
	bool operator!=(const Vertex &rhs);
};

#endif /* SRC_VERTEX_H_ */
