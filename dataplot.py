#!/usr/bin/env python3
from numpy import genfromtxt
import numpy as np
from math import *
import argparse
import csv
import matplotlib.pyplot as plt
import pandas as pd
import os
import re



dir_path = os.path.dirname(os.path.realpath(__file__))
print(dir_path)


timefile_name =dir_path + "/output/" "time.txt"
xfile_name =dir_path + "/output/" "xt_pos_vel.txt"
yfile_name =dir_path + "/output/" "yt_pos_vel.txt"

tdata = pd.read_csv(timefile_name,header = None)
xdata = pd.read_csv(xfile_name, sep="    ", header = None)
# print(xdata)
# input()
# tdata
xdata.columns = ["pos", "vel"]
ydata = pd.read_csv(yfile_name, sep="    ",header = None)
ydata.columns = ["pos", "vel"]

vdata=[]
for i in range(len(xdata["pos"])):
    temp_v = sqrt(xdata["vel"][i] ** 2 + ydata["vel"][i] ** 2)
    vdata.append(temp_v)
    if temp_v>0.45:
        print(str(i)+"-th step-exceed limit, cur_velocity = ", temp_v)
    

#figure for x,y position
plt.scatter(xdata["pos"], ydata["pos"], facecolor='white',edgecolor='black')      #initial point

#figure for x,y velocity
print("length of time: ", len(tdata))
print("length of x vel: ", len(xdata["vel"]))
fig = plt.subplot(2,1,1)
plt.xlabel('Time steps [-]')
plt.ylabel("vx and vy")
plt.plot(tdata,xdata["vel"],color='g')      #initial point
plt.plot(tdata,ydata["vel"], color='r')      #initial point
fig2 = plt.subplot(2, 1, 2)
plt.xlabel('Time steps [-]')
plt.ylabel("velocity [m/s]")
plt.plot(tdata,vdata,color='k')      #initial point

plt.show()
