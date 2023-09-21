#!/bin/bash
while true
do
streamer -c /dev/video3 -o tmp.jpeg # capture image
mogrify -rotate 180 tmp.jpeg # rotate image 180 degrees - upside down
mv tmp.jpeg outfile.jpeg
#xdg-open outfile.jpeg # open image
#rm outfile.jpeg # clean up
done
