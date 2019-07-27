#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <iostream>
#include <pcl/filters/voxel_grid.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl_ros/transforms.h>

#include <eigen3/Eigen/Dense>

#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>
#include <pcl/kdtree/kdtree_flann.h>
#include "tf_conversions/tf_eigen.h"

using namespace Eigen;
using namespace std;

class P_mapping
{
public:

    P_mapping();
    void pclCallback(const sensor_msgs::PointCloud2::ConstPtr& recived_pcl_msg);
    float step(float t);
    int grid_search(pcl::PointXYZI point);
    pcl::PointCloud<pcl::PointXYZI> cell;
    pcl::PointCloud<pcl::PointXYZI>::Ptr cellPTR;

public:
    string sensor_model_publish_topic;
    string map_publish_topic;
    string pcl_subscribe_topic;
    tf::TransformListener listener;
    string sensor_frame;
    string base_frame;

private:
    ros::NodeHandle n,n2;
    ros::Publisher pub1,pub2;
    ros::Subscriber sub;
    float resolution_ratio;
    float leaf_size;
    float max_clamping;
    float min_clamping;

    float map_resolution;
    float x_min;
    float x_max;
    float y_min;
    float y_max;
    float z_min;
    float z_max;
    int a;
    int b;
    int c;
	


};
