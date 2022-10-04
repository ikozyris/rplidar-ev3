#!/bin/bash
modprobe usbip-core; modprobe usbip-host
usbip bind -b 1-1.2
usbip bind -b 1-1.4
usbipd -D
