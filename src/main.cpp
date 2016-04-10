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

#include "Graph.h"
#include "Intersection.h"
#include "Road.h"

using namespace std;

//1.txt NODES(NodeID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
//2.txt SUBROADS(Road id; Road name; IsTwoWay)
//3.txt ROADS(Node id; Road id 1; Road id 2)

int readTxtFiles() {
	vector<Road*> roads;

	char dir[200];
	getcwd(dir, 199);
	cout << dir;

	ifstream mainFile("../assets/roads.txt");
	if (mainFile.is_open()) {
		while (!mainFile.eof()) {
			unsigned int id;
			double lat, lon, offX, offY;
			char garbage;

			mainFile >> id >> garbage >> lat >> garbage >> lon >> garbage >> offX >> garbage >> offY;
			roads.push_back(new Road(id, lat, lon, offX, offY));
		}
		mainFile.close();
	} else
		cout << "Unable to open file";

	for(unsigned int i = 0; i < roads.size(); i++) {
		cout << "Road id: " << roads[i]->getId() << "\tLat: " << roads[i]->getLatitude() << "\tLong: " << roads[i]->getLongitude() << "\tLength: " << roads[i]->getLength() << endl;
	}

	return 0;
}


int main() {
	Graph<Intersection> map();
	readTxtFiles();
	return 0;
}


