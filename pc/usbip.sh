#!/bin/bash
sudo modprobe usbip-core
sudo modprobe vhci-hcd
sudo usbip attach -r IP_ADRESS -b 1-1.2
sudo usbip attach -r IP_ADRESS -b 1-1.4
