#!/bin/bash
sudo modprobe usbip-core
sudo modprobe vhci-hcd
sudo usbip attach -r 147.102.3.34 -b 1-1.2
sudo usbip attach -r 147.102.3.34 -b 1-1.4
