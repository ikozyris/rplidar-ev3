#!/usr/bin/env python
import subprocess
import termios, tty, sys
from ev3dev.ev3 import *
from ev3dev2.motor import LargeMotor

motor_left = LargeMotor('outC') #C
motor_right = LargeMotor('outB') #B
ir = InfraredSensor('in4')

print("\n=======================")

   if ir.proximity < 10*1.4: # to detect objects closer than about 40cm
        print("Proximity Alert")
   
   sleep (0.01) # Give the CPU a rest

def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    tty.setcbreak(fd)
    ch = sys.stdin.read(1)
    termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

    return ch

def threating():
   subprocess.call(['python3', 'marchaImperial'])

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
   print(k)
   if k == 'n':
      threating()
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

