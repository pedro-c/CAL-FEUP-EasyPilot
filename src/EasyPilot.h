/*
 * EasyPilot.h
 *
 *  Created on: 24/04/2016
 *      Author: Bernardo
 */

#ifndef SRC_EASYPILOT_H_
#define SRC_EASYPILOT_H_

#include "graphviewer.h"
#include "Graph.h"

#define FILE_READING_FAILURE 1
/*#define START_NODE_COLOR "YELLOW"
#define PATH_FOUND_COLOR "GREEN"
#define END_NODE_COLOR "MAGENTA"
#define POI_NODE_COLOR "ORANGE"*/


/**
 * @brief Class EasyPilot.
 * Main class of the program.
 */
class EasyPilot {
	GraphViewer *gv; /** < Pointer to Graph Viewer Interface*/
	Graph mapGraph; /** < Graph that contains the map */
	const static string START_NODE_COLOR; /** < Start node color */
	const static string PATH_FOUND_COLOR; /** < Nodes in the path color*/
	const static string END_NODE_COLOR; /** < End node color*/
	const static string POI_NODE_COLOR; /** < Points of interest color*/
	const static float MAX_LAT; /** < Maximum latitude*/
	const static float MIN_LAT; /** < Minimum latitude*/
	const static float MAX_LON; /** < Maximum longitude*/
	const static float MIN_LON; /** < Minimum longitude*/
	const static int IMAGE_X; /** < Image width*/
	const static int IMAGE_Y; /** < Image height*/
public:
	/**
	 * @brief EasyPilot constructor
	 *
	 * @param windowWidth Graphical interface window width
	 * @param windowHeight Graphical interface window height
	 */
	EasyPilot(unsigned int windowWidth, unsigned int windowHeight);

	/**
	 * @brief Starts the program
	 */
	void start();

	/**
	 * @brief Gives the distance between to strings
	 *
	 * @param pattern Pattern to search
	 * @param text Text to search
	 *
	 * @return Returns the distance
	 */
	static unsigned int editDistance(const string &pattern, const string &text);

	/**
	 * @brief Computes the prefix of the given pattern
	 *
	 * @param pattern Pattern to compute the prefix
	 * @param prefix Prefix
	 */
	static void computePrefix(const string &pattern, unsigned int prefix[]);
private:
	/**
	 * @brief Populates the graph with information read from files
	 *
	 * @return Returns 0 on success.
	 */
	int populateGraph();

	/**
	 * @brief Displays path in GUI
	 *
	 * @param path Path to be displayed
	 * @param start Start node
	 * @param destination Destination node
	 */
	void displayPath(const list<Vertex*> &path, Vertex* start,
			Vertex* destination);

	/**
	 * @brief Populates the GUI with nodes and edges from the graph
	 */
	void populateGraphViewer();

	/**
	 * @brief Reads a vertex from the console.
	 *
	 * @return Returns the vertex read.
	 */
	Vertex* readVertex();

	/**
	 * @brief Adds nodes to the GUI
	 */
	void addNodesToGraphViewer();

	/**
	 * @brief Adds edges to the GUI
	 */
	void addEdgesToGraphViewer();

	/**
	 * @brief Converts longitude to the x GUI coordinate
	 *
	 * @param longitude Longitude to convert
	 *
	 * @return Returns the x coordinate
	 */
	int convertLongitudeToX(float longitude);

	/**
	 * @brief Converts latitude to the y GUI coordinate
	 *
	 * @param latitude Latitude to convert
	 *
	 * @return Returns the y coordinate
	 */
	int convertLatitudeToY(float latitude);
};

#endif /* SRC_EASYPILOT_H_ */
