/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
using namespace std;

template<class T> class Edge;
template<class T> class Graph;

template<class T>
class Vertex {
	T info;
	vector<Edge<T> > adj;
	bool visited;
public:
	Vertex(T in);
	friend class Graph<T> ;
};

template<class T>
Vertex<T>::Vertex(T in) :
		info(in), visited(false) {
}

template<class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T> ;
	friend class Vertex<T> ;
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
		dest(d), weight(w) {
}

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
public:
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const T &in) {
		Vertex<T>* vertice = new Vertex<T>(in);

		for (unsigned int i = 0; i < vertexSet.size(); i++) {
			if (vertexSet[i]->info == vertice->info)
				return false;
		}

		vertexSet.push_back(vertice);
		return true;
	}
	bool addEdge(const T &sourc, const T &dest, double w) {

		int indiceSourc = 0;
		int indiceDest = 0;
		bool existeSourc, existeDest;

		for (unsigned int i = 0; i < vertexSet.size(); i++) {
			if (vertexSet[i]->info == sourc) {
				indiceSourc = i;
				existeSourc = true;
			}
		}

		for (unsigned int i = 0; i < vertexSet.size(); i++) {
			if (vertexSet[i]->info == dest) {
				indiceDest = i;
				existeDest = true;
			}
		}

		if (!existeDest)
			return false;
		if (!existeSourc)
			return false;

		Edge<T> aresta(vertexSet[indiceDest], w);

		vertexSet[indiceSourc]->adj.push_back(aresta);

		return true;

	}
	bool removeVertex(const T &in) {
		Vertex<T>* vertice = new Vertex<T>(in);
		int indice = -1;
		for (unsigned int i = 0; i < vertexSet.size(); i++) {
			if (vertexSet[i]->info == vertice->info)
				indice = i;
		}
		if (indice == -1)
			return false;

		for (unsigned int i = 0; i < vertexSet.size(); i++)
			for (unsigned int x = 0; i < vertexSet[i]->adj.size(); x++)
				if (vertexSet[i]->adj[x].dest->info == vertice->info)
					vertexSet[i]->adj.erase(vertexSet[i]->adj.begin() + x);

		vertexSet.erase(vertexSet.begin() + indice);
		return true;
	}
	bool removeEdge(const T &sourc, const T &dest) {
		int indiceSourc = 0;
		int indiceDest = 0;
		bool existeSourc, existeDest;

		for (unsigned int i = 0; i < vertexSet.size(); i++) {
			if (vertexSet[i]->info == sourc) {
				indiceSourc = i;
				existeSourc = true;
			}
		}

		for (unsigned int i=0; i< vertexSet[indiceSourc]->adj.size();i++)
			if(vertexSet[indiceSourc]->adj[i].dest->info==dest){
				indiceDest=i;
				existeDest=true;
			}


		if (!existeDest)
			return false;
		if (!existeSourc)
			return false;

		vertexSet[indiceSourc]->adj.erase(vertexSet[indiceSourc]->adj.begin()+indiceDest);
		return true;

	}
};

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

#endif /* GRAPH_H_ */
