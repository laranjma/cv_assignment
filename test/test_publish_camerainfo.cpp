#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <camera_info_manager/camera_info_manager.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


int main(int argc, char **argv)
{
  // Start node
  ROS_INFO("calibration_monocam Launched");
  ros::init(argc, argv, "calibration_monocam");
  ros::NodeHandle nh("~");
  
  // Get node parameters
  std::string cam_info_topic, frame_id, cam_info_url;
  nh.getParam("cam_info_topic", cam_info_topic);
  nh.getParam("frame_id", frame_id);
  nh.getParam("camera_info_url", cam_info_url);
  std::cout <<"Advertising to topic "<<cam_info_topic<<std::endl;
  
  // Get camera info
  camera_info_manager::CameraInfoManager cam_info_manager(nh,frame_id);
  if(cam_info_manager.validateURL(cam_info_url))
  {
    // Load camera info
    cam_info_manager.loadCameraInfo(cam_info_url);
    sensor_msgs::CameraInfo cam_info_msg = cam_info_manager.getCameraInfo();
    cam_info_msg.header.frame_id = frame_id;
    
    // Start publisher
    ros::Publisher pub_caminfo = nh.advertise<sensor_msgs::CameraInfo>(cam_info_topic, 1);
    
    // Loop
    ros::Rate r(15);
    while(ros::ok())
    {
      ros::spinOnce();    
      cam_info_msg.header.stamp = ros::Time::now();
      pub_caminfo.publish(cam_info_msg);
      r.sleep();
    }    
  }
  else
    std::cout<<"Unkown URL for camera information. Unable to load camera file\n";
  


  return 0;
}

