// Create a new file: depth_viewer_node.cpp
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

void depthCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg);
        
        // Normalize depth for visualization
        cv::Mat normalized;
        cv::normalize(cv_ptr->image, normalized, 0, 255, cv::NORM_MINMAX, CV_8UC1);
        
        cv::imshow("Depth Viewer", normalized);
        cv::waitKey(1);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "depth_viewer");
    ros::NodeHandle nh;
    
    ros::Subscriber sub = nh.subscribe("/camera/aligned_depth_to_color/image_raw", 1, depthCallback);
    
    cv::namedWindow("Depth Viewer");
    ros::spin();
    
    cv::destroyWindow("Depth Viewer");
    return 0;
}
