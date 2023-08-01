>unfinished / incomplete
# Automatic navigation through map

* navigation is done with A* algorithm
* you can select the target/destination with a ncurses program which visualizes the map

### getdistances.cpp
Gets raw distances of a 360 degrees scan and outputs to stdout.

### get-point.c
Find the closest point in a 2d array which has a distance OB and angle a.<br>
<img src="https://user-images.githubusercontent.com/80053394/222142020-4f6b1e7e-7f2f-4634-bc72-4ad1756abff2.png" alt="cosine-sine" width="300"/>

### get-arr.c
Creates a 2d array from output of getdistances (like get-point in a loop). Then it creates
a 700x700 bmp from the array using the stb library.<br>
<img src="https://github.com/ikozyris/rplidar-ev3/assets/80053394/6ce07946-a4fa-4985-8cc5-19c27fe28c8e" alt="circle" width="300"/><br>
Download the STB libraries used in this project:
```
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h
```

### print-map-ncurses.c
> TODO: read graph from get-arr or delete this file
>
Press enter when you putted the cursor above the white (A_STANDOUT) space.<br>
That will be the destination
Then q to exit.

### navigation.cpp
> TODO: read graph from get-arr
> 
Reads the coordinates created by the previous program and prints the shortest path to the destination using the A* algorithm (from geeksforgeeks).<br>
Note: the source is the left-most bottom-most corner of the graph (map).

