/*
 * main.cpp
 *
 *  Created on: 08/04/2016
 *      Author: Bernardo Belchior | Maria Jo�o Mira Paulo | Pedro Costa
 */

#include <iostream>
#include <fstream>
#include <string>
//#include <unistd.h>
#include <sstream>
#include <map>

#include "Graph.h"
#include "Road.h"
#include "Coordinates.h"


using namespace std;

//1.txt NODES(NodeID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
//2.txt SUBROADS(Road id; Road name; IsTwoWay)
//3.txt ROADS(Node id; Road id 1; Road id 2)

int readTxtFiles() {


	std::map<unsigned int,Coordinates> dots;
	std::map<unsigned int,pair<Coordinates,Coordinates> > edges;
	std::map<unsigned int,Road*> road;


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


			road.insert(std::pair<unsigned int, Road*>(id,new Road(id, name, twoWay)));

		}
		secFile.close();
	} else {
		cout << "Unable to open file";
		return 2;
	}


	ifstream mainFile("roads.txt");
	if (mainFile.is_open()) {
		while (!mainFile.eof()) {
			unsigned int id;
			double lat, lon, offX, offY;
			char garbage;

			mainFile >> id >> garbage >> lat >> garbage >> lon >> garbage >> offX >> garbage >> offY;

			std::map<unsigned int,Road*>::iterator it;
			it=road.find(id);

			Coordinates c(0,id,lat,lon,offX,offY);
			dots.insert(std::pair<unsigned int,Coordinates>(id,c));


		}
		mainFile.close();
	} else {
		cout << "Unable to open file";
		return 1;
	}




	ifstream thirdFile("roads3.txt");
	if (thirdFile.is_open()) {
		while (!thirdFile.eof()) {
			unsigned int id;
			unsigned int id1;
			unsigned int id2;
			char garbage;

			thirdFile >> id >> garbage >> id1 >> garbage >> id2 >> garbage;

			std::map<unsigned int,Coordinates>::iterator it1;
			std::map<unsigned int,Coordinates>::iterator it2;

			it1=dots.find(id1);
			it2=dots.find(id2);
			if(it1 != dots.end() && it2 != dots.end()){

				it1->second.setRoad(road.find(id)->second);
				it2->second.setRoad(road.find(id)->second);

				pair<Coordinates,Coordinates> PairDots=make_pair(it1->second,it2->second);

				edges.insert(std::pair<unsigned int, pair<Coordinates,Coordinates> >(id,PairDots));

			}
		}
		thirdFile.close();
	} else {
		cout << "Unable to open file";
		return 1;
	}


	//Debug printing.

	for(std::map<unsigned int,pair<Coordinates,Coordinates> >::iterator it=edges.begin();it!=edges.end();it++){
		cout<<"idRua:"<<it->first<<" Ponto1:"<<it->second.first.getId()<<" Ponto2:"<<it->second.second.getId() << endl;
	}

	for(std::map<unsigned int,Coordinates>::iterator it=dots.begin();it!=dots.end();it++){
		cout << "idRua:" << it->second.getId() << " id:" << it->first << " Latitude:" << it->second.getLatitude() << "Longitude:" << it->second.getLongitude() << endl;
	}

	for (std::map<unsigned int, Road*>::iterator it = road.begin(); it != road.end(); it++) {
		string s;
		if (it->second->getTwoWay()) {
			s = "TRUE";
		}else{
			s = "FALSE";
		}
		cout << "idRua: " << it->second->getId() <<  " Nome: " << it->second->getName() << "  twoWay: " << it->second->getTwoWay() << endl;
	}




	char c;
	cin >> c;

	return 0;
}


int main() {
	if(readTxtFiles() > 0) {
		return 1;
	}

	return 0;
}


