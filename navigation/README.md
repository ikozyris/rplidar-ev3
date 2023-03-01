>unfinished / incomplete
# Automatic navigation through map

* navigation is done with A* algorithm
* you can select the target/destination with a ncurses program which visualizes the map

### getdistances.cpp
Gets raw distances of a 360 degrees scan and outputs to stdout.

### get-point.c
Find the closest point in a 2d array which has a distance OB and angle a.<br>
<img src="https://user-images.githubusercontent.com/80053394/222142020-4f6b1e7e-7f2f-4634-bc72-4ad1756abff2.png" alt="cos-sine" width="300"/>

> TODO create-map.cpp
> Creates the map from the output of getpoint.c


### print-map-ncurses.c

Press enter when you putted the cursor above the white (A_STANDOUT) space.<br>
That will be the destination
Then q to exit.

### navigation.cpp

Reads the coordinates created by the previous program and prints the shortest path to the destination.<br>
Note: the source is the left-most bottom-most corner of the graph (map).

