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
Utilize ```RVIZ``` and ```image_view``` to visualize the map and debugging image, respectively.
