>unfinished / incomplete
# Automatic navigation through map

* navigation is done with A* algorithm
* you can select the target/destination with a ncurses program which visualizes the map


### print-map-ncurses.c

Press enter when you putted the cursor above the white (A_STANDOUT) space.<br>
Then q to exit.

### navigation.cpp

Reads the coordinates created by the previous program and prints the shortest path to the destination.<br>
Note: the source is the left-most bottom-most corner of the graph (map).

> TODO create-map.cpp
> creates the map of the area with rplidar slamtec sdk
> Currently only prints raw reading from the lidar