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
#include <cfloat>
#include <cstdio>
#include <math.h>
#include <cstdlib>


#include "Graph.h"
#include "Point.h"
#include "Road.h"
#include "graphviewer.h"

float maxLat=0;
float minLat=0;
float maxLon=0;
float minLon=0;
bool flag = true;
using namespace std;

//1.txt NODES(PointID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
//2.txt SUBROADS(Road id; Road name; IsTwoWay)
//3.txt ROADS(Road id; PointID 1; PointID 2)

int convertLongitudeToX(GraphViewer *gv, float x){

	cout << "X= " << ((x-minLon)*gv->getheight())/(maxLon-minLon) << endl;
	return ((x-minLon)*gv->getheight())/(maxLon-minLon);

}

int convertLatitudeToY(GraphViewer *gv, float y){
	cout << "Y= " << ((y-minLat)*gv->getwidth())/(maxLat-minLat) << endl;
	return ((y-minLat)*gv->getwidth())/(maxLat-minLat);
}

int populateGraph(Graph &mapGraph,GraphViewer *gv) {
	map<unsigned int,Point*> points;
	map<unsigned int,pair<Point*,Point*> > edges;
	map<unsigned int,Road*> roads;
	int edgeID=0;


	//2.txt SUBROADS(Road id; Road name; IsTwoWay)
	ifstream secFile("map2.txt");
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
	ifstream mainFile("map1.txt");
	if (mainFile.is_open()) {
		while (!mainFile.eof()) {
			unsigned int id;
			double lat, lon, offX, offY;
			char garbage;

			mainFile >> id >> garbage >> lat >> garbage >> lon >> garbage >> offX >> garbage >> offY;


			if(flag){
				maxLon=lon;
				minLon=lon;
				maxLat=lat;
				minLat=lat;
				flag=false;
			}

			if(lon > maxLon){
				maxLon=lon;
			}
			if(lon < minLon){
				minLon=lon;
			}
			if(lat > maxLat){
				maxLat=lat;
			}
			if(lat < minLat){
				minLat=lat;
			}

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
	ifstream thirdFile("map3.txt");
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
					gv->addEdge(edgeID, id1, id2,EdgeType::UNDIRECTED);
					edgeID++;

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

int populateGraphViewer(Graph mapGraph, GraphViewer *gv){

	for(unsigned int i=0; i< mapGraph.getVertexSet().size();i++ ){
		gv->addNode(mapGraph.getVertexSet()[i].getInfo().getId(),convertLatitudeToY(gv,mapGraph.getVertexSet()[i].getInfo().getLatitude()),convertLongitudeToX(gv,mapGraph.getVertexSet()[i].getInfo().getLongitude()));

	}


	return 0;

}


int main() {
	Graph mapGraph = Graph();
	GraphViewer *gv = new GraphViewer(600, 600, true);
	gv->createWindow(600, 600);


	cout << "Loading..." << endl;

	if(populateGraph(mapGraph,gv) > 0) {
		return 1;
	}

	populateGraphViewer(mapGraph, gv);


	Vertex* start = mapGraph.getVertex(26015916);
	Vertex* destination = mapGraph.getVertex(26015892);
	list<Vertex*> path = mapGraph.getShortestPath(start, destination);

	cout << "Path from : " << start->getRoadName() << " to " << destination->getRoadName() << endl;

	if (path.size() > 1) {
		list<Vertex*>::iterator nextIt = path.begin()++;
		for (list<Vertex*>::iterator it = path.begin(); nextIt != path.end(); it++) {

			Road* roadBetween = (*it)->getRoadBetween(*nextIt);
			string roadName = (roadBetween == NULL) ? "" : roadBetween->getName();

			cout << "Rua: " << roadName << endl;
			nextIt++;
		}
	}


	/*	gv->createWindow(600, 600);
		gv->defineVertexColor("blue");
		gv->defineEdgeColor("black");
		gv->addNode(0);
		gv->rearrange();
		gv->addNode(1);
		gv->rearrange();
		//gv->addEdge(01,0,1,EdgeType::UNDIRECTED);
		gv->addEdge(01,0,1, EdgeType::DIRECTED);
		gv->addNode(2);
		*/

	if (destination->getDistance() == DBL_MAX)
		cout << "Path not found.\n";
	else 
		cout << "Distance: " << destination->getDistance() << endl;

	int a;
	cin >> a;
	return 0;
}


