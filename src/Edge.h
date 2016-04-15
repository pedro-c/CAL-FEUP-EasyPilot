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
	Vertex<T> * src;
	Road* road;
public:
	Edge(Vertex<T>* s, Vertex<T> *d, Road* road);
	friend class Graph<T> ;
	friend class Vertex<T> ;
};


template<class T>
Edge<T>::Edge(Vertex<T> *s, Vertex<T> *d, Road* road) :
	src(s), dest(d), road(road) { }

#endif /* SRC_EDGE_H_ */
