#!/usr/bin/env micropython
from ev3dev2.sensor.lego import InfraredSensor, GyroSensor, ColorSensor
from time import sleep

# Connect sensors to any sensor ports
gy = GyroSensor() 
ir = InfraredSensor()
cl = ColorSensor
sound = Sound()
angle = gy.angle

    print(cl.reflected_light_intensity)
    sleep(1)
    print(str(angle) + ' degrees')
    sleep(0.5)
    print(ir.value()*1.4)
    exit()
