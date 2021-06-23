#include "imgproc/ImgPublisher.h"

//#define ML_DEBUG_MODE

namespace ml
{
ImgPublisher::ImgPublisher(ros::NodeHandle _nh, std::string& _imgTopic, std::string& _encoding)
{
  image_transport::ImageTransport it(_nh);
  m_pub = it.advertise(_imgTopic, 1);
  m_encoding = _encoding;
}

void ImgPublisher::PublishImg(const cv::Mat& _img)
{
#ifdef ML_DEBUG_MODE
std::cout<<"ImgPublisher::PublishImg()\n";
#endif
  m_msg = cv_bridge::CvImage(std_msgs::Header(), m_encoding, _img).toImageMsg();
  m_pub.publish(m_msg);
  return;
}
}
