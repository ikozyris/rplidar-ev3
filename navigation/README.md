>unfinished / incomplete
# Automatic navigation through map

* navigation is done with A* algorithm
* you can select the target/destination with a ncurses program which visualizes the map

### getdistances.cpp
Gets raw distances of a 360 degrees scan and outputs to stdout.

> TODO create-map.cpp<br>
> Creates the map of the area based on data by getdistances.
> The algorithm would be to find the point in a 2d array based on theta(degrees) and distance
> Needs some trigonometry knowledge.

### print-map-ncurses.c

Press enter when you putted the cursor above the white (A_STANDOUT) space.<br>
That will be the destination
Then q to exit.

### navigation.cpp

Reads the coordinates created by the previous program and prints the shortest path to the destination.<br>
Note: the source is the left-most bottom-most corner of the graph (map).

