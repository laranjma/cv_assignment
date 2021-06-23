#ifndef IMGPUBLISHER_H
#define IMGPUBLISHER_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

namespace ml
{
class ImgPublisher
{
public:
  // Functions
  ImgPublisher(ros::NodeHandle _nh, std::string& _imgTopic, std::string& _encoding);
  void PublishImg(const cv::Mat& _img);

  // Variables
  ros::NodeHandle m_nh;
  image_transport::Publisher m_pub;
  sensor_msgs::ImagePtr m_msg;
  std::string m_encoding;

};
};
#endif // IMGPUBLISHER_H
