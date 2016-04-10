/*
 * main.cpp
 *
 *  Created on: 08/04/2016
 *      Author: Bernardo Belchior | Maria João Mira Paulo | Pedro Costa
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//1.txt NODES(NodeID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
//2.txt SUBROADS(Road id; Road name; IsTwoWay)
//3.txt ROADS(Node id; Road id 1; Road id 2)

int readTxtFiles() {
	string line;
	ifstream myfile("/assets/roads.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//perform action
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return 0;
}


int main() {

}


