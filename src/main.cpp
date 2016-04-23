/*
 * main.cpp
 *
 *  Created on: 08/04/2016
 *      Author: Bernardo Belchior | Maria Joao Mira Paulo | Pedro Costa
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

	//cout << "X= " << floor(((x-minLon)*gv->getheight())/(maxLon-minLon)) << endl;
	return floor(((x-minLon)*gv->getheight())/(maxLon-minLon));

}

int convertLatitudeToY(GraphViewer *gv, float y){
	//cout << "Y= " << floor(((y-minLat)*gv->getwidth())/(maxLat-minLat)) << endl;
	return floor(((y-minLat)*gv->getwidth())/(maxLat-minLat));
}

int populateGraph(Graph &mapGraph,GraphViewer *gv) {
	map<unsigned int,Point*> points;
	map<unsigned int,pair<Point*,Point*> > edges;
	map<unsigned int,Road*> roads;
	int edgeID=0;


	//2.txt SUBROADS(Road id; Road name; IsTwoWay)
	ifstream secFile("mapTest2.txt");
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
	ifstream mainFile("mapTest1.txt");
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
	ifstream thirdFile("mapTest3.txt");
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

				Road* road = roads.find(id)->second;

				mapGraph.addEdge(*(it1->second), *(it2->second), road, distance);

				if(road->getTwoWay()) {
					mapGraph.addEdge(*(it2->second), *(it1->second), road, distance);
					//gv->addEdge(edgeID, id1, id2,EdgeType::UNDIRECTED);
					//edgeID++;
				}else{
					//gv->addEdge(edgeID, id1, id2,EdgeType::DIRECTED);
					//edgeID++;
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
	int edgeID=0;
	for(unsigned int i=0; i< mapGraph.getVertexSet().size();i++ ){
		gv->addNode(mapGraph.getVertexSet()[i].getInfo().getId(),convertLatitudeToY(gv,mapGraph.getVertexSet()[i].getInfo().getLatitude()),convertLongitudeToX(gv,mapGraph.getVertexSet()[i].getInfo().getLongitude()));
		gv->setVertexLabel(mapGraph.getVertexSet()[i].getInfo().getId(), ".");
	}

	for(unsigned int i=0; i < mapGraph.getVertexSet().size();i++){
		for(unsigned int x=0; x < mapGraph.getVertexSet()[i].getAdj().size(); x++){

			int destID=mapGraph.getVertexSet()[i].getAdj()[x]->getDest()->getInfo().getId();
			int srcID=mapGraph.getVertexSet()[i].getAdj()[x]->getSrc()->getInfo().getId();


			gv->addEdge(edgeID, srcID, destID,EdgeType::UNDIRECTED);
			mapGraph.getVertexSet()[i].getAdj()[x]->setEdgeID(edgeID);
			//adiciona o nome das ruas
			//gv->setEdgeLabel(edgeID, mapGraph.getVertexSet()[i].getAdj()[x]->getRoadName());
			edgeID++;
		}
	}

	return 0;

}


int main() {
	Graph mapGraph = Graph();
	GraphViewer *gv = new GraphViewer(1000, 600, false);
	string startRoad,destinationRoad;
	gv->createWindow(1000, 800);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	cout << "Loading..." << endl;

	if(populateGraph(mapGraph,gv) > 0) {
		return 1;
	}

	populateGraphViewer(mapGraph, gv);

	gv->rearrange();


	// Adicionar função para atraves do nome da rua obter ID do vertice
	cout<<"Enter your Starting Point (Road Name): ";
	getline(cin,startRoad);
	cout <<"Enter your destiny (Road Name): ";
	getline(cin,destinationRoad);


	/*
	Vertex* start = mapGraph.getVertex(420777495);
	Vertex* destination = mapGraph.getVertex(3554953622);
	list<Vertex*> path = mapGraph.getShortestPath(start, destination);
	 */

	Vertex* start;
	start = mapGraph.getVertexFromRoadName(startRoad);

	while(start==NULL){
		cout<<"Invalid Starting Point. Enter a valid Road Name:"<<endl;
		getline(cin,startRoad);
		start = mapGraph.getVertexFromRoadName(startRoad);
	}

	Vertex* destination;
	destination = mapGraph.getVertexFromRoadName(destinationRoad);

	while(destination==NULL){
		cout<<"Invalid Destination Point. Enter a valid Road Name:"<<endl;
		getline(cin,destinationRoad);
		destination = mapGraph.getVertexFromRoadName(destinationRoad);
	}

	list<Vertex*> path = mapGraph.getShortestPath(start, destination);


	cout<<"Calculating your journey..."<<endl;

	cout << "Path from : " << start->getRoadName() << " to " << destination->getRoadName() << endl;

	if (path.size() > 1) {
		list<Vertex*>::iterator nextIt = path.begin()++;
		for (list<Vertex*>::iterator it = path.begin(); nextIt != path.end(); it++) {

			Road* roadBetween = (*it)->getRoadBetween(*nextIt);
			string roadName = (roadBetween == NULL) ? "" : roadBetween->getName();

			gv->setVertexColor((*it)->getInfo().getId(), "GREEN");

			for(unsigned int x=0; x< (*it)->getAdj().size(); x++){
				list<Vertex*>::iterator it2 = path.begin()++;
				for (list<Vertex*>::iterator it1 = path.begin(); it2 != path.end(); it1++){
					if((*it)->getAdj()[x]->getDest() == (*it1)){
						list<Vertex*>::iterator it4 = path.begin()++;
						for (list<Vertex*>::iterator it3 = path.begin(); it4 != path.end(); it3++){
							if((*it)->getAdj()[x]->getSrc() == (*it3)){
								gv->setEdgeThickness((*it)->getAdj()[x]->getEdgeID(), 5);
								gv->setEdgeLabel((*it)->getAdj()[x]->getEdgeID(), roadBetween->getName());
								gv->setEdgeColor((*it)->getAdj()[x]->getEdgeID(), "GREEN");
							}
							it4++;
						}
					}
					it2++;
				}
			}


			cout << "Rua: " << roadName << endl;
			nextIt++;
			for(unsigned int i = 0; i < destination->getAdj().size(); i++){
				if(destination->getAdj()[i]->getDest() == (*it)){
					gv->setEdgeThickness(destination->getAdj()[i]->getEdgeID(), 5);
					gv->setEdgeLabel(destination->getAdj()[i]->getEdgeID(), roadBetween->getName());
					gv->setEdgeColor(destination->getAdj()[i]->getEdgeID(), "GREEN");
				}
			}
		}
	}



	gv->setVertexColor(start->getInfo().getId(), "YELLOW");
	gv->setVertexColor(destination->getInfo().getId(), "MAGENTA");


	if (destination->getDistance() == DBL_MAX)
		cout << "Path not found.\n";
	else 
		cout << "Distance: " << destination->getDistance() << endl;

	int a;
	cin >> a;
	return 0;
}


