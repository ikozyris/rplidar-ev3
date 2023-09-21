#!/bin/bash
sudo modprobe usbip-core
sudo modprobe vhci-hcd
# first parameter is IP address
sudo usbip attach -r $1 -b 1-1.1 # Lidar
sudo usbip attach -r $1 -b 1-1.2 # Camera
