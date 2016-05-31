# EasyPilot
Navigation System using graphs and www.openstreetmap.org maps converted to text files for the Algorithm Analysis and Conception (CAL) class of the Master in Informatics and Computer Engineering (MIEIC) at the Faculty of Engineering of the University of Porto (FEUP).

# TXT MAP Files
- 1.txt NODES (NodeID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
- 2.txt SUBROADS (Road id; Road name; IsTwoWay)
- 3.txt ROADS (Node id; Road id 1; Road id 2)

The group decided to add Points of Interest as well as Suburb. As such, the above mentioned text files were modified as seen in "porto" files in the repository. 

# Compile and Run

The project needs the C++11 syntax in order to run properly.
If you are using Eclipse, make sure to add -static to the linker.
On Windows, you need to add "wsock32" under Properties -> C/C++ Build -> Settings -> MinGW C++ Linker -> Libraries.
