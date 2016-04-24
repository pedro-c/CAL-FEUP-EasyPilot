/*
 * EasyPilot.cpp
 *
 *  Created on: 24/04/2016
 *      Author: Bernardo
 */

#include "EasyPilot.h"
#include <map>
#include <fstream>
#include <sstream>

EasyPilot::EasyPilot(unsigned int windowWidth, unsigned int windowHeight) {
	mapGraph = Graph();
	gv = new GraphViewer(windowWidth, windowHeight, false);

	gv->setBackground("sjoao.png");
	gv->createWindow(windowWidth, windowHeight);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
}

void EasyPilot::start() {
	cout << "Reading files...\n";
	populateGraph();
	cout << "Finished reading files ...\n";
	cout << "Populating graph viewer...\n";
	populateGraphViewer();
	cout << "Finished populating graph viewer...\n";

	cout << "Please introduce the start road name: ";
	Vertex* start = readVertex();
	cout << "Please introduce the destination road name: ";
	Vertex* destination = readVertex();

	displayPath(mapGraph.getShortestPath(start, destination), start,
			destination);
}

int EasyPilot::populateGraph() {
	//Used to temporarily store information from the text files.
	map<unsigned int, Point*> points;
	map<unsigned int, Road*> roads;

	//2.txt SUBROADS(Road id; Road name; IsTwoWay)
	ifstream secFile("sjoao2.txt");
	if (secFile.is_open()) {
		while (!secFile.eof()) {
			unsigned int roadID;
			char garbage;
			string name, twoWayStr;
			bool isTwoWay;

			secFile >> roadID >> garbage;

			getline(secFile, name, ';');
			getline(secFile, twoWayStr);

			if (twoWayStr.find("True") == string::npos)
				isTwoWay = false;
			else
				isTwoWay = true;

			roads.insert(
					std::pair<unsigned int, Road*>(roadID,
							new Road(roadID, name, isTwoWay)));
		}
		secFile.close();
	} else {
		cout << "Unable to open file roads2.txt.\n";
		exit(FILE_READING_FAILURE);
	}

	//1.txt NODES(PointID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
	ifstream mainFile("sjoao1.txt");
	if (mainFile.is_open()) {
		while (!mainFile.eof()) {
			unsigned int nodeID;
			double latitude, longitude, projectionX, projectionY;
			char garbage;

			mainFile >> nodeID >> garbage >> latitude >> garbage >> longitude
			>> garbage >> projectionX >> garbage >> projectionY;

			if (latitude > minLat && latitude < maxLat && longitude > minLon
					&& longitude < maxLon) {
				Point* c = new Point(nodeID, latitude, longitude, projectionX,
						projectionY);
				points.insert(std::pair<unsigned int, Point*>(nodeID, c));
				mapGraph.addVertex(*c);
			}
		}
		mainFile.close();
	} else {
		cout << "Unable to open file roads.txt.\n";
		exit(FILE_READING_FAILURE);
	}

	//3.txt ROADS(Road id; PointID 1; PointID 2)
	ifstream thirdFile("sjoao3.txt");
	if (thirdFile.is_open()) {
		while (!thirdFile.eof()) {
			unsigned int roadID;
			unsigned int firstNodeID;
			unsigned int secondNodeID;
			char garbage;

			thirdFile >> roadID >> garbage >> firstNodeID >> garbage
			>> secondNodeID >> garbage;

			map<unsigned int, Point*>::iterator firstNodeIterator,
			secondNodeIterator;

			firstNodeIterator = points.find(firstNodeID);
			secondNodeIterator = points.find(secondNodeID);
			if (firstNodeIterator != points.end()
					&& secondNodeIterator != points.end()) {
				double distance = (firstNodeIterator->second)->getDistance(
						*(secondNodeIterator->second));

				Road* road = roads.find(roadID)->second;

				mapGraph.addEdge(*(firstNodeIterator->second),
						*(secondNodeIterator->second), road, distance);

				if (road->getTwoWay())
					mapGraph.addEdge(*(secondNodeIterator->second),
							*(firstNodeIterator->second), road, distance);
			}
		}
		thirdFile.close();
	} else {
		cout << "Unable to open file roads3.txt.\n";
		exit(FILE_READING_FAILURE);
	}

	return 0;
}

void EasyPilot::displayPath(const list<Vertex*> &path, Vertex* start,
		Vertex* destination) {

	if (path.size() < 1) {
		cout << "Path not found.\nAre you sure there is a connection?\n";
		return;
	}

	list<Vertex*>::const_iterator nextIt = path.begin()++;

	for (list<Vertex*>::const_iterator it = path.begin(); nextIt != path.end(); it++) {
		Edge* edgeBetween = (*it)->getEdgeBetween(*nextIt);
		Road* roadBetween = edgeBetween->getRoad();

		gv->setVertexColor((*it)->getInfo().getId(), PATH_FOUND_COLOR);
		cout << (*it)->getRoadName() << endl;
		if(edgeBetween != NULL) {

			//If the road is two way, we have to color both of the edges.
			if(roadBetween->getTwoWay()) {
				gv->setEdgeThickness((*nextIt)->getEdgeBetween(*it)->getEdgeID(), 5);
				gv->setEdgeColor((*nextIt)->getEdgeBetween(*it)->getEdgeID(), PATH_FOUND_COLOR);
			}

			gv->setEdgeThickness(edgeBetween->getEdgeID(), 5);
			gv->setEdgeColor(edgeBetween->getEdgeID(), PATH_FOUND_COLOR);
		}

		nextIt++;
	}

	//gv->setVertexColor((*(path.end()--))->getInfo().getId(), END_NODE_COLOR);
	//gv->setVertexColor((*path.begin())->getInfo().getId(), START_NODE_COLOR);
	cout << "cheguei\n";
	cout << (*(path.end()--))->getRoadName() << endl;

	gv->setVertexColor(start->getInfo().getId(), START_NODE_COLOR);
	gv->setVertexColor(destination->getInfo().getId(), END_NODE_COLOR);
}

void EasyPilot::addNodesToGraphViewer() {
	for (unsigned int i = 0; i < mapGraph.getVertexSet().size(); i++) {
		Vertex* vertex = &mapGraph.getVertexSet()[i];

		gv->addNode(vertex->getInfo().getId(),
				convertLatitudeToY(vertex->getInfo().getLatitude()),
				convertLongitudeToX(vertex->getInfo().getLongitude()));
		gv->setVertexLabel(vertex->getInfo().getId(), ".");
	}
}

void EasyPilot::addEdgesToGraphViewer() {
	for (unsigned int i = 0; i < mapGraph.getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < mapGraph.getVertexSet()[i].getAdj().size();
				j++) {
			Edge* edge = mapGraph.getVertexSet()[i].getAdj()[j];
			int destID = edge->getDestination()->getInfo().getId();
			int srcID = edge->getSource()->getInfo().getId();

			if (edge->getRoad()->getTwoWay()) {
				//FIXME: Do not remove the other edge, instead check if it is in the graph already.
				gv->removeEdge(edge->getDestination()->getEdgeBetween(edge->getSource())->getEdgeID());
				gv->addEdge(edge->getEdgeID(), srcID, destID,
						EdgeType::UNDIRECTED);
			} else {
				gv->addEdge(edge->getEdgeID(), srcID, destID,
						EdgeType::DIRECTED);
			}
		}
	}
}

void EasyPilot::populateGraphViewer() {
	cout << "Adding nodes to graph viewer...\n";
	addNodesToGraphViewer();
	cout << "Finished adding nodes to graph viewer...\n";
	cout << "Adding edges to graph viewer...\n";
	addEdgesToGraphViewer();
	cout << "Finished adding edges to graph viewer...\n";

	gv->rearrange();
}

Vertex* EasyPilot::readVertex() {
	Vertex *vertex;
	string roadName;

	getline(cin, roadName);

	while ((vertex = mapGraph.getVertexFromRoadName(roadName)) == NULL) {
		cout << "Invalid road name. Try again.\n";
		getline(cin, roadName);
	}

	return vertex;
}

int EasyPilot::convertLongitudeToX(float x) {
	return floor(((x - minLon) * (ImageY)) / (maxLon - minLon));
}

int EasyPilot::convertLatitudeToY(float y) {
	return floor(((y - minLat) * (ImageX)) / (maxLat - minLat));
}

