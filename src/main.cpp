/*
 * main.cpp
 *
 *  Created on: 08/04/2016
 *      Author: Bernardo Belchior | Maria Jo�o Mira Paulo | Pedro Costa
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include "Graph.h"
#include "Point.h"
#include "Road.h"


using namespace std;

//1.txt NODES(PointID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
//2.txt SUBROADS(Road id; Road name; IsTwoWay)
//3.txt ROADS(Road id; PointID 1; PointID 2)

int populateGraph(Graph &mapGraph) {
	map<unsigned int,Point*> points;
	map<unsigned int,pair<Point*,Point*> > edges;
	map<unsigned int,Road*> roads;

	//2.txt SUBROADS(Road id; Road name; IsTwoWay)
	ifstream secFile("roads2.txt");
	if (secFile.is_open()) {
		while (!secFile.eof()) {
			string line;
			unsigned int id;
			char garbage;
			string name, tw;
			bool twoWay = true;

			getline(secFile, line);

			stringstream ss(line);

			ss >> id >> garbage;

			getline(ss, name, ';');
			getline(ss, tw);

			if (tw.find("True") == -1)
				twoWay = false;
			else
				twoWay = true;


			roads.insert(std::pair<unsigned int, Road*>(id,new Road(id, name, twoWay)));
		}
		secFile.close();
	} else {
		cout << "Unable to open file roads2.txt.\n";
		return 2;
	}

	//1.txt NODES(PointID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
	ifstream mainFile("roads.txt");
	if (mainFile.is_open()) {
		while (!mainFile.eof()) {
			unsigned int id;
			double lat, lon, offX, offY;
			char garbage;

			mainFile >> id >> garbage >> lat >> garbage >> lon >> garbage >> offX >> garbage >> offY;

			Point* c = new Point(id,lat,lon,offX,offY);
			points.insert(std::pair<unsigned int,Point*>(id,c));
			mapGraph.addVertex(*c);
		}
		mainFile.close();
	} else {
		cout << "Unable to open file roads.txt.\n";
		return 1;
	}

	//3.txt ROADS(Road id; PointID 1; PointID 2)
	ifstream thirdFile("roads3.txt");
	if (thirdFile.is_open()) {
		while (!thirdFile.eof()) {
			unsigned int id;
			unsigned int id1;
			unsigned int id2;
			char garbage;

			thirdFile >> id >> garbage >> id1 >> garbage >> id2 >> garbage;

			map<unsigned int,Point*>::iterator it1, it2;

			it1=points.find(id1);
			it2=points.find(id2);
			if(it1 != points.end() && it2 != points.end()){
				pair<Point*,Point*> PairDots=make_pair(it1->second,it2->second);

				edges.insert(std::pair<unsigned int, pair<Point*,Point*> >(id,PairDots));
				double distance=(it1->second)->getDistance(*(it2->second));
				/*cout << "Ponto 1 - latitude: " << (it1->second)->getLatitude();
				cout << " Ponto 1 - longitude: " << (it1->second)->getLongitude() << endl;
				cout << "Ponto 2 - latitude: " << (it2->second)->getLatitude();
				cout << "Ponto 1 - longitude: " << (it2->second)->getLongitude() << endl;
				cout << "Distance: " << distance << endl;*/

				Road* road = roads.find(id)->second;

				mapGraph.addEdge(*(it1->second), *(it2->second), road, distance);

				if(road->getTwoWay()) {
					mapGraph.addEdge(*(it2->second), *(it1->second), road, distance);
				}
			}
		}
		thirdFile.close();
	} else {
		cout << "Unable to open file roads3.txt.\n";
		return 3;
	}

	return 0;
}




int main() {
	Graph mapGraph = Graph();

	cout << "Loading..." << endl;

	if(populateGraph(mapGraph) > 0) {
		return 1;
	}
	/*
	string begin;
	string goal;

	cout << "Indique onde se encontra: " << endl;
	getline(cin,begin);
	cout << "Indique o destino: " << endl;
	getline(cin, goal);
	*/
	//mapGraph.printVertexes();
	/*
	list<Vertex*> path = mapGraph.getShortestPath(mapGraph.getVertex(26015916), mapGraph.getVertex(26015892));

	for(list<Vertex*>::iterator it = path.begin(); it != path.end(); it++) {
		list<Vertex*>::iterator nextIt = it;
		nextIt++;
		Road* roadBetween = (*it)->getRoadBetween(*nextIt);
		string roadName = (roadBetween == NULL) ? "" : roadBetween->getName();

		cout << "Rua: " << roadName << endl;
	}
	 */
	//mapGraph.printVertexes();




	//mapGraph.getShortestDistance(mapGraph.getVertex(435240919), mapGraph.getVertex(128591046));
	Vertex* start = mapGraph.getVertex(112613584);
	Vertex* destination = mapGraph.getVertex(2060757071);
	
	//Vertex* start = mapGraph.findVertexByRoadName(begin);
	//Vertex* destination = mapGraph.findVertexByRoadName(goal);
	
	list<Vertex*> path = mapGraph.getShortestPath(start, destination);
	cout << path.size() << endl;
	cout << "Path from : " << start->getRoadName() << " to " << destination->getRoadName() << endl;

	for(list<Vertex*>::iterator it = path.begin(); it != path.end(); it++) {
		list<Vertex*>::iterator nextIt = it;
		//nextIt++;
		//Road* roadBetween = (*it)->getRoadBetween(*nextIt);
		//string roadName = (roadBetween == NULL) ? "" : roadBetween->getName();

		string roadName = (*it)->getRoadName();

		cout << "Rua: " << roadName << endl;
	}

	cout << "Distance: " << mapGraph.getVertex(2060757071)->getDistance() << endl;

	int a;
	cin >> a;
	return 0;
}


