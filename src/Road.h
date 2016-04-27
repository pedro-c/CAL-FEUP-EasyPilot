#pragma once

#include <string>

using namespace std;

/**
 * @brief Class Road
 * This class contains a unique identifier for each road, its name
 * and a boolean flag telling if the road is one or two ways;
 */

class Road {
	unsigned int id; /** <private member containing the unique identifier> */
	string name; /**<private member containing the road name>  */
	bool twoWay; /**<private member that specifies if the road is twoWay, true if so or false if not>  */
public:
	Road();
	Road(unsigned int id, bool twoWay);
	Road(unsigned int id, const string &name, bool twoWay);
	void setName(const string &name);
	const string& getName() const;
	void setTwoWay(bool twoWay);
	bool getTwoWay() const;
	unsigned int getId() const;
	bool operator == (const Road &p2) const;
	friend ostream & operator << (ostream &os, Road &p);
};


