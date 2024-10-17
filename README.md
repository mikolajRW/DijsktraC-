# DijsktraC++
A project written in C++ that utilizes Dijkstra's algorithm and BFS to find the shortest path on a map.



A rectangular map divided into squares is given. Each field on the map can be empty (impassable, represented by '.'), 
be part of a road (passable in both directions, represented by '#'), or be a city (passable like a road, represented by '#'). 
The name of each city is given on the map, and each letter occupies one field (the field with the letter is impassable). 
Moving through one field takes one minute. We can only move between fields adjacent by sides. Additionally, selected cities are connected by one-way air connections. 
The name of a city will be adjacent (by side or corner) to the city with the first or last letter of the name.
The name will be unambiguously assigned to the city. There will be no number or letter before or after the name of the city (if there is such a field).

Example of the maps and the solutions can be found in Example_maps.zip file


Additional remarks this was a student project and it was forbbiden to use many libraries, that is why class called my_own_string exists in this project
