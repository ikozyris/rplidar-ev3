#!/usr/bin/env python
import subprocess
import termios, tty, sys
#from ev3dev2.sound import Sound
from ev3dev2.sensor.lego import InfraredSensor
from ev3dev2.motor import LargeMotor

motor_left = LargeMotor('outC') #C
motor_right = LargeMotor('outB') #B
ir = InfraredSensor('in4')

print("W for forward, S for Backwards, D for right, A for left, Space to stop"
	  "and Q to quit gracefully")
print("\n=======================")


def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    tty.setcbreak(fd)
    ch = sys.stdin.read(1)
    termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

    return ch

#def threating():
#	sound.speak('You should be afraid of me!')

def forward():
	motor_left.run_forever(speed_sp=650)
	motor_right.run_forever(speed_sp=650)

def back():
	motor_left.run_forever(speed_sp=-400)
	motor_right.run_forever(speed_sp=-400)

def left():
	motor_left.run_forever(speed_sp=-350)
	motor_right.run_forever(speed_sp=350)

def right():
	motor_left.run_forever(speed_sp=350)
	motor_right.run_forever(speed_sp=-350)

def stop():
	motor_left.run_forever(speed_sp=0)
	motor_right.run_forever(speed_sp=0)

while True:
   	k = getch()
   	if ir.proximity < 10 * 1.4: # to detect objects closer than about 10cm
    	print("Proximity Alert")
      	print(ir.value() * 1.4)

#   if k == 'n':
#      threating()
   	if k == 's':
   		back()
   	if k == 'w':
   		forward()
   	if k == 'd':
   		right()
   	if k == 'a':
   		left()
   	if k == ' ':
   		stop()
   	if k == 'q':
   		exit()

