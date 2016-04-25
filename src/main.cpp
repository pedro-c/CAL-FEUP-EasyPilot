/*
 * main.cpp
 *
 *  Created on: 08/04/2016
 *      Author: Bernardo Belchior | Maria Joao Mira Paulo | Pedro Costa
 */

#include <iostream>

#include "EasyPilot.h"


using namespace std;

//1.txt NODES(PointID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
//2.txt SUBROADS(Road id; Road name; IsTwoWay)
//3.txt ROADS(Road id; PointID 1; PointID 2)

int main() {
	EasyPilot easyPilot(1200, 700);
	easyPilot.start();

	return 0;
}


