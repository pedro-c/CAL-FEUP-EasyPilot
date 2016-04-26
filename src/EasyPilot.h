/*
 * EasyPilot.h
 *
 *  Created on: 24/04/2016
 *      Author: Bernardo
 */

#ifndef SRC_EASYPILOT_H_
#define SRC_EASYPILOT_H_

#include "graphviewer.h"
#include "Graph.h"

#define FILE_READING_FAILURE 1
#define START_NODE_COLOR "YELLOW"
#define PATH_FOUND_COLOR "GREEN"
#define END_NODE_COLOR "MAGENTA"
#define POI_NODE_COLOR "ORANGE"

class EasyPilot {
	GraphViewer *gv;
	Graph mapGraph;
	const float maxLat = 41.1856;
	const float minLat = 41.1705;
	const float maxLon = -8.5902;
	const float minLon = -8.6161;
	const int ImageX = 1758;
	const int ImageY = 2261;
public:
	EasyPilot(unsigned int windowWidth, unsigned int windowHeight);
	void start();
private:
	int populateGraph();
	void displayPath(const list<Vertex*> &path, Vertex* start,
			Vertex* destination);
	void populateGraphViewer();
	Vertex* readVertex();
	void addNodesToGraphViewer();
	void addEdgesToGraphViewer();
	int convertLongitudeToX(float x);
	int convertLatitudeToY(float y);
};

#endif /* SRC_EASYPILOT_H_ */
