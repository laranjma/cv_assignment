# cv_assignment

This code implements a localization algorithm based on ORB-SLAM 2 and tested with the AQUALOC dataset

## Install

This code was tested on:

1. Ubuntu 18.04
2. ROS Melodic

Instructions to install ORB-SLAM 2: --
[https://github.com/appliedAI-Initiative/orb_slam_2_ros](https://github.com/appliedAI-Initiative/orb_slam_2_ros)

To download this code, enter:
```
git clone git@github.com:laranjma/cv_assignment.git
```
To compile this code, enter:
```
cd ~/catkin_ws
catkin build imgproc
```
To launch the localization node:
```
roslaunch imgproc aqualoc_orb_slam2.launch
```
Set the data location with the first argument of the launch file.
Use ```RVIZ``` and ```image_view``` to visualize the map and debugging image, respectively.
The camera's poses are stored in ```/tmp/orbslam_pose.dat```.

To plot the estimated and ground truth trajectories enter:
```python plot3D.py ../data/colmap_traj_sequence_6.txt ../data/orbslam_pose.dat```