# rplidar-ev3
A repo for remote controlling a LEGO EV3 with rplidar and usbip

## How does it work
The robot has an EV3 onboard connected to the motors and to a usb hub with additional dc power from an external battery. In the hub there is the rplidar and a wifi dongle. The lidar is accesed using usbip, which means it can be accesed from anywhere in the world! The robot is controlled from a remote computer from an ssh connection.

## Software Installation
1. Install EV3dev: https://www.ev3dev.org/
2. Setup usbip: https://www.linux-magazine.com/Issues/2018/208/Tutorial-USB-IP
3. Install rplidar_sdk: https://github.com/Slamtec/rplidar_sdk  -> [also check this for gcc 11+](https://github.com/Slamtec/rplidar_sdk/pull/64)

Now, to use the lidar install ``` python3 ``` and the following libraries:
```
rplidar-roboticia
matplotlib
```
## Project structure
├── bot<br>
│   ├── control-bot.py      ->Move the robot<br>
│   ├── sensors.py          ->Get sensors status<br>
│   └── usbip.sh            ->Setup usbip server<br>
├── LICENSE<br>
├── navigation<br>
│   ├── get-distances.cpp   ->Get a 360 scan<br>
│   ├── get-point.c         ->Find the point in a 2d array<br>
│   ├── naver-ncurses.c     ->Set the destination for below<br>
│   ├── navigation.cpp      ->A* algorithm for navigating in the area<br>
│   ├── print-map-ncurses.c ->Print map nicely<br>
│   └── README.md<br>
├── pc<br>
│   ├── camcap.sh           ->Capture an image<br>
│   ├── rplidar-live.py     ->Live data from lidar displayed with matplot and numpy<br>
│   └── usbip.sh            ->Connect to robot's usbip server<br>
└── README.md<br>




## Hardware setup
The Lidar is an RPlidar, I used the A1 model. <br>
Motors: 2 Large motors on B and C <br>
Sensors: Proximity, Color, Gyro

