#!/bin/bash
streamer -c /dev/video3 -b 4 -o outfile.jpeg #capture image with 4-bit colour
mogrify -rotate 180 outfile.jpeg #rotate image 180 degrees - upside down
xdg-open outfile.jpeg #open image with default viewer
#sleep 5;
#sudo killall shotwell #uncomment if you use shotwell 
rm outfile.jpeg #clean up
