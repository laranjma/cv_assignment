#include "imgproc/ImgPublisher.h"
#include "opencv2/highgui.hpp"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_imgPublisher");
  ros::NodeHandle nh;

  // Load images from files
  std::cout<<"Loading images...\n";
  std::vector<cv::String> img_names;
  std::string file_path = "/home/matheus/Documents/tii/dataset/archaeo_sequence_6_raw_data/raw_data/images_sequence_6/*.png";
  //std::string file_path = "/home/matheus/Documents/tii/dataset/archaeo_sequence_6_raw_data/raw_data/img_seq_6/*.png";
  cv::glob(file_path, img_names, false);
  size_t count = img_names.size(); //number of png files in images folder

  // Create image publisher
  std::string encoding("bgr8");
  std::string topic ("/camera/image_raw");
  ml::ImgPublisher imgPub(nh,topic,encoding);

  /*// Sleep (wait other nodes to start)
  cv::Mat img = cv::imread(img_names[0]);
  imgPub.PublishImg(img);  
  ros::spinOnce();
  std::this_thread::sleep_for (std::chrono::seconds(5));
  */

  // Run
  std::cout<<"Start publishing...\n";
  cv::Mat img;
  ros::Rate r(20);
  int k = 0;
  while (ros::ok() && k < count)
  {
    
    //if(!images[k].empty())
    //{
      std::cout<<"k = "<<k<<"/"<<img_names.size()<<std::endl;
      img = cv::imread(img_names[k]);
      //cv::imshow("img",images[k]);
      //cv::waitKey(0);

      imgPub.PublishImg(img);
      k++;
    //}
    //else
      //std::cout<<"No image received\n";
      ros::spinOnce();
    r.sleep();
  }
  std::cout<<"shutdown img Publisher\n";
  ros::shutdown();
  return 0;
}
