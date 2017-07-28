# Yuan_CSCI2270_FinalProject

***Summary:

In this project, I intend to develop a navigation system that find the nearest path between two locations. The path finding algorithm I intend to employ is the A star algorithm.  Every city has its own node which store its longitude and altitude, distance between its nearest cities along with road name. The cities’ connection grill will be stored as graph. In A star algorithm, there are three value to be calculated, heuristic value H, travel expense G and total value F which equals H + G. H will be calculated by longitude and altitude. G value will be pass along the journey. Two lists will be created, an open list and a close list. From the starting point, the algorithm will put starting point into close list and calculate the its nearest nodes’ F value and put these nodes inside an open list. Put this node into the close list. Then sort the open list, and choose the lowest F value node and reevaluate the F value of the nodes around it. There will be nodes that repeat, leave them unchanged if its previous G value is lower than the new G value.  Then re-sort the open list and repeat the process above until it finds the destination node. The difference between A star algorithm and Dijkstra's algorithm is that the A star algorithm has a sense of "direction". Value H will guide the process to the right direction. Unlike Dijkstra's algorithm, A star will not calculate the shorter path for the node that in the oppesite direction of the destination node.  So, Dijkstra's algortithm take long time if the map is the whole North America. But A star algorithm will run considerablly faster than Dijkstra. 

The data structures used here are array queue and graph. The open list will be stored in array and the “map” will be stored as graph. The functions of this program include inserting/deleting city nodes, add/delete path between two nodes and calculate the quickest path. The program will print out the path with road name and the total distance. 

***Instruction:

The program contains pre-installed map that contains most major cities to north of denver inside Colorado. The edges between cities can be view write after the program open. The city name is not capital sensitive, but you need to spell write and use space if the name contains more than two words. 

***Follow the printed instruction and you might want to prepare some information if you wish to insert anything.

To insert city vertex, type in the coordinate of the city, one city it connected to that already inside the map, the major road name between two cities and the total distance. 

To delete city, just insert the city name.

To insert path, type in path name, two cities that already inside graph and distance.

To delete path, type in two city vertices that were already connected by edge and the road name. Plus, road name is capital sensitive. So, use capital words. You can reference it from the print out right after you open the program.

Since the surrounding is famillar, you will know if the answer is correct right away.

***Dependencies:

download header.h and main.cpp under the same file inorder to exicute it perfectly. Just run main.cpp.

***System Requirement 

I wrote it in VM of Linux. 

***Enhancement

If I can pull information directly from google. This program can perform A star algorithm all around Ammerica. 

***Writen by Hao Yuan

