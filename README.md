# EasyPilot
Navigation System using graphs and www.openstreetmap.org maps converted to text files for the Algorithm Analysis and Conception (CAL) class of the Master in Informatics and Computer Engineering (MIEIC) at the Faculty of Engineering of the University of Porto (FEUP).

# TXT MAP Files
- 1.txt NODES (NodeID; Latitude; Longitude; projectionCoordinates.X, projectionCoordinates.Y)
- 2.txt SUBROADS (Road id; Road name; IsTwoWay)
- 3.txt ROADS (Node id; Road id 1; Road id 2)


O projeto necessita da sintaxe de C++11 de modo a correr corretamente.
O programa foi criado no Eclipse, portanto, à partida, não necessitará de instruções de compilação especiais, tirando a flag -static.
Pode ser ainda necessario adicionar a biblioteca: wsock32 em Properties -> C/C++ Build -> Settings -> MinGW C++ Linker -> Libraries.