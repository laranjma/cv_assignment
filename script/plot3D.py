#!/usr/bin/python

import os
import sys
from os import listdir, read
from os.path import isfile, join
import matplotlib
#matplotlib.rcParams['pdf.fonttype'] = 42
#matplotlib.rcParams['ps.fonttype'] = 42
matplotlib.rcParams['text.usetex'] = True
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from math import asin, sqrt



# global plot params
lt = 2 # line tickness
xmax = 20 # x-axis max value
ymin = -0.4 # y-axis min value
ymax = 0.2 # y-axis max value
tfs = 14 # title font size
lbfs = 14 # label font size
lfs = 12 # legend font size
lloc = 1 # legand location
lnc = 2 # nb colomn for legend
ms = 15 # markersize
'''
# tether features
Hmax = 0.70
DHmax = 0.50
# graphs limits
alpha_min = -25
alpha_max = 45
dalpha = 10
H_min = -0.25
H_max = 0.45
dH = 0.1
xmax = 300
dx = 50
v_min = -0.3
v_max = 0.3
dv = 0.1
'''
	

def plotTrajectory(traj_gt, traj_es, labelx, labely):
    # Data to plot
    x1 = traj_gt[:,0]
    y1 = traj_gt[:,1]
    z1 = traj_gt[:,2]
    x2 = traj_es[:,0]
    y2 = traj_es[:,1]
    z2 = traj_es[:,2]    

		
    # Plot
    plt.clf()
    ax = plt.gca()
    ax.set_title(r'Trajectory XY',fontsize=tfs)
    ax.set_xlabel(labelx)
    ax.set_ylabel(labely)
    plt.grid()
    ax.invert_yaxis()
    ax.scatter(x1,y1,c='green', marker=".",edgecolors='none', s=30, label=r'ground truth')
    ax.scatter(x2,y2,c='red', marker=".",edgecolors='none', s=30, label=r'estimated')
    legend = ax.legend(loc='upper right',ncol=lnc,fontsize=lfs)
    plt.savefig("trajectory_xy.png",format="png")
    #plt.show(block=False)

    # Plot
    plt.clf()
    ax = plt.gca()
    ax.set_title(r'Trajectory XZ',fontsize=tfs)
    ax.set_xlabel('x(m)')
    ax.set_ylabel('z(m)')
    plt.grid()
    ax.invert_yaxis()
    ax.scatter(x1,z1,c='green', marker=".",edgecolors='none', s=30, label=r'ground truth')
    ax.scatter(x2,z2,c='red', marker=".",edgecolors='none', s=30, label=r'estimated')
    legend = ax.legend(loc='upper left',ncol=lnc,fontsize=lfs)
    plt.savefig("trajectory_xz.png",format="png")

    return

def readTrajectory(fname):
    # read the whole file into a single variable, which is a list of every row of the file
    f = open(fname, 'r')
    lines = f.readlines()#[5:] skip header
    f.close()
	
    # initialize some variable to be lists
    tmp = np.empty(len(lines))
    traj = np.empty([len(lines),7])    

    # scan the rows of the file stored in lines, and put the values into some variables
    l=0
    for line in lines:
        p = line.split()
        tmp[l] = float(p[0])
        traj[l][0] = float(p[1])
        traj[l][1] = float(p[2])
        traj[l][2] = float(p[3])
        traj[l][3] = float(p[4])
        traj[l][4] = float(p[5])
        traj[l][5] = float(p[6])
        traj[l][6] = float(p[7])
        l = l+1	

    return traj

if __name__ == '__main__':
    # absolute dir the script is in
    script_dir = os.path.dirname(__file__) 
	
    # Ground truth and estimated trajectories
    rel_path1 = sys.argv[1]
    rel_path2 = sys.argv[2]
    filepath1 = os.path.join(script_dir, rel_path1)
    filepath2 = os.path.join(script_dir, rel_path2)
	
    # initialize some variable to be lists
    #tmp = np.empty(len(lines))
    #traj_grt = np.empty([len(lines),7])
    #traj_est = np.empty([len(lines),7])

    traj_grt = readTrajectory(filepath1)
    traj_est = readTrajectory(filepath2)
    traj_est[:,2] = -traj_est[:,2]
    traj_est[:,0:3] = traj_est[:,0:3] + traj_grt[0,0:3]
    
    '''
	'''    	
    print(traj_grt[2,:])
    plotTrajectory(traj_grt, traj_est, 'x(m)', 'y(m)')
    #plotTetherShape("tethershape.eps",sest)
    #plotVel("vel_r2.eps",vcmd)
    #plot_TetherShape_Vel("tethershape_vel.eps",sest[:300],vcmd[:300])
