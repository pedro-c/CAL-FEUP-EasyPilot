/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

template<class T> class Edge;
template<class T> class Graph;

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
public:
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, Road* road);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	void printVertexes() const;
};

template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
bool Graph<T>::addVertex(const T &in) {
	Vertex<T>* vertex = new Vertex<T>(in);

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info == vertex->info)
			return false;
	}

	vertexSet.push_back(vertex);
	return true;
}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, Road* road) {
	int sourceIndex = 0;
	int destIndex = 0;
	bool hasSource, hasDest;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info == sourc) {
			sourceIndex = i;
			hasSource = true;
		}
	}

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info == dest) {
			destIndex = i;
			hasDest = true;
		}
	}

	if (!hasDest)
		return false;
	if (!hasSource)
		return false;

	Edge<T> edge(vertexSet[destIndex], road);

	vertexSet[sourceIndex]->adj.push_back(edge);

	return true;
}

template<class T>
bool Graph<T>::removeVertex(const T &in) {
	Vertex<T>* vertex = new Vertex<T>(in);
	int index = -1;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info == vertex->info)
			index = i;
	}
	if (index == -1)
		return false;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
		for (unsigned int x = 0; i < vertexSet[i]->adj.size(); x++)
			if (vertexSet[i]->adj[x].dest->info == vertex->info)
				vertexSet[i]->adj.erase(vertexSet[i]->adj.begin() + x);

	vertexSet.erase(vertexSet.begin() + index);
	return true;
}

template<class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	int sourceIndex = 0;
	int destIndex = 0;
	bool hasSource, hasDest;

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info == sourc) {
			sourceIndex = i;
			hasSource = true;
		}
	}

	for (unsigned int i = 0; i < vertexSet[sourceIndex]->adj.size(); i++) {
		if (vertexSet[sourceIndex]->adj[i].dest->info == dest) {
			destIndex = i;
			hasDest = true;
		}
	}

	if (!hasSource)
		return false;
	if (!hasDest)
		return false;

	vertexSet[sourceIndex]->adj.erase(
			vertexSet[sourceIndex]->adj.begin() + destIndex);
	return true;
}

template<class T>
void Graph<T>::printVertexes() const {
	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		cout << vertexSet[i]->info << " and have " << vertexSet[i]->adj.size() << " edges.\n";
	}
}

#endif /* GRAPH_H_ */
