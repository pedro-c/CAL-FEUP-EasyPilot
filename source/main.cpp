/*
 * main.cpp
 *
 *  Created on: 08/04/2016
 *      Author: Bernardo Belchior | Maria Jo�o Mira Paulo | Pedro Costa
 */

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sstream>

#include "Graph.h"
#include "Intersection.h"
#include "Road.h"

using namespace std;

//1.txt NODES(NodeID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
//2.txt SUBROADS(Road id; Road name; IsTwoWay)
//3.txt ROADS(Node id; Road id 1; Road id 2)

int readTxtFiles() {
	vector<Intersection*> intersections;
	vector<Road*> roads;

	ifstream mainFile("roads.txt");
	if (mainFile.is_open()) {
		while (!mainFile.eof()) {
			unsigned int id;
			double lat, lon, offX, offY;
			char garbage;

			mainFile >> id >> garbage >> lat >> garbage >> lon >> garbage >> offX >> garbage >> offY;
			intersections.push_back(new Intersection(id, lat, lon, offX, offY));
		}
		mainFile.close();
	} else {
		cout << "Unable to open file";
		return 1;
	}

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

			if(tw.find("True") == -1)
				twoWay = false;
			else
				twoWay = true;

			roads.push_back(new Road(id, name, twoWay));
		}
		secFile.close();
	} else {
		cout << "Unable to open file";
		return 2;
	}

	//Debug printing.
	for(unsigned int i = 0; i < intersections.size(); i++) {
		cout << "Intersection id: " << intersections[i]->getId() << "\tLat: " << intersections[i]->getLatitude() << "\tLong: " << intersections[i]->getLongitude() << endl;
	}

	for(unsigned int i = 0; i < roads.size(); i++) {
		cout << "Road id: " << roads[i]->getId() << "\tName: " << roads[i]->getName() << "\tTwoWay: " << roads[i]->getTwoWay() << endl;
	}

	return 0;
}


int main() {
	Graph<Intersection> map();
	if(readTxtFiles() > 0)
		return 1;
	return 0;
}


