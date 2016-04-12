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

using namespace std;

template<class T> class Edge;

template<class T>
class Edge {
	Vertex<T> * dest;
	Road* road;
public:
	Edge(Vertex<T> *d, Road* road);
	~Edge();
	friend class Graph<T> ;
	friend class Vertex<T> ;
};


template<class T>
Edge<T>::Edge(Vertex<T> *d, Road* road) :
		dest(d), road(road) { }

template<class T>
Edge<T>::~Edge() {
	delete road;
}

#endif /* SRC_EDGE_H_ */
