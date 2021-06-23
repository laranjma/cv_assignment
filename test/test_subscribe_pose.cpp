#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>
#include<tf2/LinearMath/Matrix3x3.h>
#include<tf2/LinearMath/Quaternion.h>
#include <visp3/core/vpMatrix.h>
#include <iostream>

class PoseSubscriber
{
private:
  ros::NodeHandle m_nh;
  ros::Subscriber m_pose_sub; 
  geometry_msgs::PoseStamped m_pose_msg;
  std::vector<double> m_pose;
  std::vector<std::vector<double>> m_pose_data;

public:
  
  PoseSubscriber(ros::NodeHandle &_nh){
    m_nh = _nh;
    m_pose.resize(8);
    //m_pose_data.reserve()
    m_pose_sub = m_nh.subscribe<geometry_msgs::PoseStamped>("/orb_slam2_mono/pose", 1000, &PoseSubscriber::poseCallback, this);
  }
  ~PoseSubscriber(){};

  void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) 
  {
    // Camera position in map frame
    double tx = msg->pose.position.x;
    double ty = msg->pose.position.y;
    double tz = msg->pose.position.z;
    double qx = msg->pose.orientation.x;
    double qy = msg->pose.orientation.y;
    double qz = msg->pose.orientation.z;
    double qw = msg->pose.orientation.w;

    // Store pose in array
    m_pose[0] =  msg->header.seq;;
    m_pose[1] = tx;
    m_pose[2] = ty;
    m_pose[3] = tz;
    m_pose[4] = qx;
    m_pose[5] = qy;
    m_pose[6] = qz;
    m_pose[7] = qw;
    m_pose_data.push_back(m_pose);
    /*std::cout<<"pose = "<<tx<<", "<<ty<<", "<<tz<<", "<<qx<<", "<<qy<<", "<<qz<<", "<<qw<<", "<<std::endl;
    std::cout<<"M POSE = "<<m_pose.size()<<std::endl;
    std::cout<<"M POSE_DATA = "<<m_pose_data.size()<<std::endl;
    */
    return;
  }

  void writeDataInFile(const char *_filename/*, const char *_header*/)
  {
    std::ofstream myfile;
    myfile.open(_filename);
    const unsigned int rows = m_pose_data.size();
    const unsigned int cols = m_pose_data[0].size();

    std::cout<<"DATA SIZE = "<<rows<<" "<<cols<<std::endl;

    //myfile << _header << std::endl;
    for(unsigned int i=0; i < rows; i++)
    {
      for(unsigned int j=0; j < cols; j++)
      {
        myfile << std::fixed << std::setprecision(8) << m_pose_data[i][j] <<"\t";
      }
      myfile << "\n";
    }
    myfile.close();
    return;
  }
};

int main(int argc, char **argv)
{
  // Start node
  ROS_INFO("test_subscribe_pose Launched");
  ros::init(argc, argv, "test_subscribe_pose");
  ros::NodeHandle nh("~");

   /*// Get node parameters
  std::string cam_info_topic, frame_id, cam_info_url;
  nh.getParam("cam_info_topic", cam_info_topic);
  nh.getParam("frame_id", frame_id);
  nh.getParam("camera_info_url", cam_info_url);
  std::cout <<"Advertising to topic "<<cam_info_topic<<std::endl;
  */ 
  
  // ROS subscriber
  PoseSubscriber pose_sub(nh);

  // Loop
  ros::Rate r(10);
  while(ros::ok())
  {
    ros::spinOnce();    
    r.sleep();
  }

  // Write pose data into file
  char* filename = new char[99];
  std::snprintf(filename,99,"/tmp/orbslam_pose.dat");
  //char* header_data = new char[999];
  //std::snprintf(header_data,999,"#Txyz\tQxyzw");
  //char * header = (char *) malloc(1 + strlen(header_data) );//(char *) malloc(1 + strlen(header_data) );
  //strcpy(header, header_data);
  pose_sub.writeDataInFile(filename);
  std::cout<<"write done"<<std::endl;  
  ros::shutdown();
  return 0;
}

