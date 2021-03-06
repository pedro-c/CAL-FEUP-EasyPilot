/*
 * EasyPilot.cpp
 *
 *  Created on: 24/04/2016
 *      Author: Bernardo
 */

#include "EasyPilot.h"
#include <fstream>
#include <map>
#include <set>
#include <cfloat>

const string EasyPilot::START_NODE_COLOR = "YELLOW";
const string EasyPilot::PATH_FOUND_COLOR = "GREEN";
const string EasyPilot::END_NODE_COLOR = "MAGENTA";
const string EasyPilot::POI_NODE_COLOR = "ORANGE";
const float EasyPilot::MAX_LAT = 41.186;
const float EasyPilot::MIN_LAT = 41.13921;
const float EasyPilot::MAX_LON = -8.57601;
const float EasyPilot::MIN_LON = -8.65271;
const int EasyPilot::IMAGE_X = 2000;
const int EasyPilot::IMAGE_Y = 2464;

EasyPilot::EasyPilot(unsigned int windowWidth, unsigned int windowHeight) {
	mapGraph = Graph();
	gv = new GraphViewer(windowWidth, windowHeight, false);
	gv->setBackground("outputSmall.png");
	gv->createWindow(windowWidth, windowHeight);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
}

void EasyPilot::start() {
	float distance = 0;
	char answer = 'Y';
	Vertex* begin;
	Vertex* destination;
	list<Vertex*> path;
	cout << "Reading files...\n";
	populateGraph();
	cout << "Finished reading files ...\n";
	cout << "Populating graph viewer...\n";
	populateGraphViewer();
	cout << "Finished populating graph viewer...\n";

	//cout << "Please introduce the starting point: ";
	Vertex* start = readVertex();
	begin = start;

	while(toupper(answer) == 'Y'){
		destination = readVertex();
		list<Vertex*> temp = mapGraph.getShortestPath(start, destination);

		if(destination->getDistance() != DBL_MAX) {
			distance += destination->getDistance();
			cout << "\nDistance between " << start->getRoadName() << " and " << destination->getRoadName() << " is " << destination->getDistance() << " kilometers.\n";
		}

		list<Vertex*>::iterator it2=temp.end();
		list<Vertex*>::iterator it1=temp.begin();
		list<Vertex*>::iterator it=path.end();
		path.insert(it,it1,it2);

		start=destination;
		cout << "Do you want to add another place? (Y/N) ";
		cin >> answer;
		cin.ignore();
		cin.clear();
	}

	displayPath(path, begin, destination);
	if(distance > 0)
		cout << "\nTotal path distance is " << distance << " kilometers.\n";
}

int EasyPilot::populateGraph() {
	//Used to temporarily store information from the text files.
	map<unsigned long, Point*> points;
	map<unsigned long, Road*> roads;

	//2.txt SUBROADS(Road id; Road name; IsTwoWay)
	ifstream secFile("porto2.txt");
	if (secFile.is_open()) {
		while (!secFile.eof()) {
			unsigned long roadID;
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
					std::pair<unsigned long, Road*>(roadID,
							new Road(roadID, name, isTwoWay)));
		}
		secFile.close();
	} else {
		cout << "Unable to open file roads2.txt.\n";
		exit(FILE_READING_FAILURE);
	}

	//1.txt NODES(PointID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
	ifstream mainFile("porto1.txt");
	if (mainFile.is_open()) {
		while (!mainFile.eof()) {
			unsigned long nodeID;
			double latitude, longitude, projectionX, projectionY;
			char garbage;
			string POI;
			string suburb;

			mainFile >> nodeID >> garbage >> latitude >> garbage >> longitude
			>> garbage >> projectionX >> garbage >> projectionY >> garbage;

			getline(mainFile, suburb, ';');
			getline(mainFile, POI, ';');

			if (latitude > MIN_LAT && latitude < MAX_LAT && longitude > MIN_LON	&& longitude < MAX_LON) {
				Point* c = new Point(nodeID, latitude, longitude, projectionX,
						projectionY);
				points.insert(std::pair<unsigned long, Point*>(nodeID, c));
				c->setPOI(POI);
				c->setSuburb(suburb);
				mapGraph.addVertex(*c);
			}
		}
		mainFile.close();
	} else {
		cout << "Unable to open file roads.txt.\n";
		exit(FILE_READING_FAILURE);
	}

	//3.txt ROADS(Road id; PointID 1; PointID 2)
	ifstream thirdFile("porto3.txt");
	if (thirdFile.is_open()) {
		while (!thirdFile.eof()) {
			unsigned long roadID;
			unsigned long firstNodeID;
			unsigned long secondNodeID;
			char garbage;

			thirdFile >> roadID >> garbage >> firstNodeID >> garbage
			>> secondNodeID >> garbage;

			map<unsigned long, Point*>::iterator firstNodeIterator, secondNodeIterator;

			firstNodeIterator = points.find(firstNodeID);
			secondNodeIterator = points.find(secondNodeID);
			if (firstNodeIterator != points.end()
					&& secondNodeIterator != points.end()) {

				Road* road = roads.find(roadID)->second;

				mapGraph.addEdge(*(firstNodeIterator->second),
						*(secondNodeIterator->second), road);

				if (road->getTwoWay())
					mapGraph.addEdge(*(secondNodeIterator->second),
							*(firstNodeIterator->second), road);
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
	list<Vertex*>::const_iterator it;
	for (it = path.begin(); nextIt != path.end(); it++) {
		nextIt++;
		Edge* edgeBetween = (*it)->getEdgeBetween(*nextIt);

		gv->setVertexColor((*it)->getInfo().getId(), PATH_FOUND_COLOR);
		if(edgeBetween != NULL) {
			//If the road is two way, we have to color both of the edges.
			//Even though one of them may not be displayed

			if(edgeBetween->getRoad()->getTwoWay()) {
				gv->setEdgeThickness((*nextIt)->getEdgeBetween(*it)->getEdgeID(), 5);
				gv->setEdgeColor((*nextIt)->getEdgeBetween(*it)->getEdgeID(), PATH_FOUND_COLOR);
			}

			gv->setEdgeThickness(edgeBetween->getEdgeID(), 5);
			gv->setEdgeColor(edgeBetween->getEdgeID(), PATH_FOUND_COLOR);
		}
	}

	gv->setVertexColor((*path.begin())->getInfo().getId(), START_NODE_COLOR);
	gv->setVertexColor(destination->getInfo().getId(), END_NODE_COLOR);
}

void EasyPilot::addNodesToGraphViewer() {
	for (unsigned int i = 0; i < mapGraph.getVertexSetSize(); i++) {
		Vertex* vertex = mapGraph.getVertexFromIndex(i);

		gv->addNode(vertex->getInfo().getId(),
				convertLatitudeToY(vertex->getInfo().getLatitude()),
				convertLongitudeToX(vertex->getInfo().getLongitude()));
		gv->setVertexLabel(vertex->getInfo().getId(), ".");

		if(vertex->getInfo().getPOI() != ""){
			gv->setVertexColor(vertex->getInfo().getId(),POI_NODE_COLOR);
			gv->setVertexLabel(vertex->getInfo().getId(), vertex->getInfo().getPOI());
		}
	}
}

void EasyPilot::addEdgesToGraphViewer() {
	set<unsigned int> addedEdges = set<unsigned int>();

	for (unsigned int i = 0; i < mapGraph.getVertexSetSize(); i++) {
		Vertex* vertex = mapGraph.getVertexFromIndex(i);
		for (unsigned int j = 0; j < vertex->getAdj().size();
				j++) {
			Edge* edge = vertex->getAdj()[j];
			int destID = edge->getDestination()->getInfo().getId();
			int srcID = edge->getSource()->getInfo().getId();

			if (edge->getRoad()->getTwoWay()) {
				set<unsigned int>::iterator it = addedEdges.find(edge->getDestination()->getEdgeBetween(edge->getSource())->getEdgeID());
				if(it != addedEdges.end())  {
					addedEdges.erase(it);
				} else {
					gv->addEdge(edge->getEdgeID(), srcID, destID, EdgeType::UNDIRECTED);
					addedEdges.insert(edge->getEdgeID());
				}
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

void EasyPilot::computePrefix(const string &pattern, int prefix[]) {
	unsigned int length = pattern.length();
	int k = -1;

	prefix[0] = -1;

	for (unsigned int i = 1; i < length; i++) {
		while (k > -1 && tolower(pattern[k+1]) != tolower(pattern[i])) {
			k = prefix[k];
		}

		if (tolower(pattern[k+1]) == tolower(pattern[i]))
			k++;

		prefix[i] = k;
	}
}

int EasyPilot::exactMatch(const string &text, const string &pattern) {
	int num = 0;
	int prefix[pattern.length()];

	computePrefix(pattern, prefix);

	int q = -1;
	for (unsigned int i = 0; i < text.length(); i++) {

		while (q > -1 && tolower(pattern[q+1]) != tolower(text[i]))
			q = prefix[q];

		if (tolower(pattern[q+1]) == tolower(text[i]))
			q++;

		if (q == pattern.length() - 1) {
			num++;
			q = prefix[q];
		}
	}

	return num;
}

unsigned int EasyPilot::editDistance(const string &pattern, const string &text) {
	unsigned int distance[text.length()+1];
	unsigned int oldDistance, newDistance;

	for (unsigned int i = 0; i <= text.length(); i++)
		distance[i] = i;

	for (unsigned int i = 1; i <= pattern.length(); i++) {
		oldDistance = distance[0];
		distance[0] = i;

		for (unsigned int j = 1; j <= text.length(); j++) {
			//Check is not case sensitive
			if (tolower(pattern[i-1]) == tolower(text[j-1]))
				newDistance = oldDistance;
			else {
				newDistance = min(oldDistance, min(distance[j], distance[j-1]));
				newDistance++;
			}

			oldDistance = distance[j];
			distance[j] = newDistance;
		}
	}

	return distance[text.length()];
}

Vertex* EasyPilot::readVertex() {
	Vertex *vertex;
	string roadName;

	cout << "Please introduce a point: ";
	getline(cin, roadName);

	while ((vertex = mapGraph.getVertexFromRoadName(roadName)) == NULL) {
		cout << "Invalid road name. Try again.\n";
		getline(cin, roadName);
	}

	cout << "What suburb does the road belong to?\n";

	string suburb;
	getline(cin, suburb);

	if(!exactMatch(vertex->getInfo().getSuburb(), suburb)) {
		cout << "The road you provided does not belong to the suburb you specified.\nDo you want to choose another road? (Y/N)\n";

		string answer;
		cin >> answer;

		cin.ignore();
		cin.clear();

		if(exactMatch("Y", answer))
			return readVertex();
	}

	return vertex;
}

int EasyPilot::convertLongitudeToX(float longitude) {
	return floor(((longitude - MIN_LON) * (IMAGE_Y)) / (MAX_LON - MIN_LON));
}

int EasyPilot::convertLatitudeToY(float latitude) {
	return floor(((latitude - MIN_LAT) * (IMAGE_X)) / (MAX_LAT - MIN_LAT));
}

