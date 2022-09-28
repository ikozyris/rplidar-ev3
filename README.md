# rplidar-ev3
A repo for remote controlling a LEGO EV3 with rplidar and usbip

## How does it work
The robot has an EV3 onboard connected to the motors and to a usb hub with additional dc power from an external battery. In the hub there is the rplidar and a wifi dongle. The lidar is accesed using usbip, which means it can be accesed from anywhere in the world! The robot is controlled from a remote computer from an ssh connection.

## Software Installation
1. Setup usbip: https://www.linux-magazine.com/Issues/2018/208/Tutorial-USB-IP
2. Install EV3dev: https://www.ev3dev.org/

Now, to use the lidar install ``` python3 ``` and the following libraries:
```
rplidar-roboticia
matplotlib
```

## Hardware setup
The Lidar is an RPlidar, I used the A1 model.

TODO
