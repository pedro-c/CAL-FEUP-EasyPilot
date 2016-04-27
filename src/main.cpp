/*
 * main.cpp
 *
 *  Created on: 08/04/2016
 *      Author: Bernardo Belchior | Maria Joao Mira Paulo | Pedro Costa
 */

#include <iostream>

#include "EasyPilot.h"


using namespace std;

/**
* @brief Main do programa.
* Populates the graph and the graphviewer with all the nodes and edges and starts
* the interface.
*/

int main() {
	EasyPilot easyPilot(1200, 700);
	easyPilot.start();

	cin.ignore();

	return 0;
}


