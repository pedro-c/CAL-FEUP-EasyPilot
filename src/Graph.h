/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Point.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;

template<class T> class Edge;
template<class T> class Graph;

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, Road* road);
	void printVertexes() const;
	vector<Point*> getShortestPath(unsigned int startID, unsigned int goalID);
	Vertex<T>* getVertex(unsigned int pointID);
};

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
bool Graph<T>::addVertex(const T &in) {
	Vertex<T>* vertex = new Vertex<T>(in);

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (*(vertexSet[i]->info) == *(vertex->info))
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
		if (*(vertexSet[i]->info) == sourc) {
			sourceIndex = i;
			hasSource = true;
		}
	}

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (*(vertexSet[i]->info) == dest) {
			destIndex = i;
			hasDest = true;
		}
	}

	if (!hasDest || !hasSource)
		return false;

	Edge<T>* edge = new Edge<T>(vertexSet[sourceIndex], vertexSet[destIndex], road);
	vertexSet[sourceIndex]->adj.push_back(edge);

	if (road->getTwoWay())
		vertexSet[destIndex]->adj.push_back(edge);

	return true;
}

template<class T>
void Graph<T>::printVertexes() const {
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		cout << vertexSet[i]->info << " and have " << vertexSet[i]->adj.size() << " edges.\n";
	}
}

template<class T>
vector<Point*> Graph<T>::getShortestPath(unsigned int startID, unsigned int goalID) {
	vector<Point*> path;
	Vertex<T>* start = getVertex(startID);
	Vertex<T>* goal = getVertex(goalID);

	/*
	if (start == NULL || goal == NULL)
		throw NULL;
	
	*/
	
	
	/*
	https://en.wikipedia.org/wiki/A*_search_algorithm#Description
	function A*(start, goal)
		// The set of nodes already evaluated.
		closedSet : = {}
		// The set of currently discovered nodes still to be evaluated.
		// Initially, only the start node is known.
	openSet: = { start }
		// For each node, which node it can most efficiently be reached from.
		// If a node can be reached from many nodes, cameFrom will eventually contain the
		// most efficient previous step.
	cameFrom: = the empty map

		// For each node, the cost of getting from the start node to that node.
		gScore : = map with default value of Infinity
		// The cost of going from start to start is zero.
		gScore[start] : = 0
		// For each node, the total cost of getting from the start node to the goal
		// by passing by that node. That value is partly known, partly heuristic.
		fScore : = map with default value of Infinity
		// For the first node, that value is completely heuristic.
		fScore[start] : = heuristic_cost_estimate(start, goal)

		while openSet is not empty
			current : = the node in openSet having the lowest fScore[] value
			if current = goal
				return reconstruct_path(cameFrom, current)

				openSet.Remove(current)
				closedSet.Add(current)
				for each neighbor of current
					if neighbor in closedSet
						continue		// Ignore the neighbor which is already evaluated.
										// The distance from start to a neighbor
						tentative_gScore : = gScore[current] + dist_between(current, neighbor)
						if neighbor not in openSet	// Discover a new node
							openSet.Add(neighbor)
						else if tentative_gScore >= gScore[neighbor]
							continue		// This is not a better path.

											// This path is the best until now. Record it!
							cameFrom[neighbor] : = current
							gScore[neighbor] : = tentative_gScore
							fScore[neighbor] : = gScore[neighbor] + heuristic_cost_estimate(neighbor, goal)

							return failure

							function reconstruct_path(cameFrom, current)
							total_path : = [current]
							while current in cameFrom.Keys :
								current : = cameFrom[current]
								total_path.append(current)
								return total_path*/


	return path;
}

template<class T>
Vertex<T>* Graph<T>::getVertex(unsigned int pointID) {
	for (int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->info->getId() == pointID)
			return vertexSet[i];
	}

	return NULL;
}

#endif /* GRAPH_H_ */
