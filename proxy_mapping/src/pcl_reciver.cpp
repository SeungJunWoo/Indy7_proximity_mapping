#include "../include/proxy_mapping.h"

void P_mapping::pclCallback(const sensor_msgs::PointCloud2::ConstPtr &recived_pcl_msg)
{
  std::cout << "pointcloud recieved!!" << endl;
  // Convert the sensor_msgs/PointCloud2 data to pcl/PointCloud
  pcl::PointCloud<pcl::PointXYZ>::Ptr raw_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromROSMsg(*recived_pcl_msg, *raw_cloud);

  //sensor modeling
  pcl::PointCloud<pcl::PointXYZI>::Ptr model_cloud(new pcl::PointCloud<pcl::PointXYZI>);

  for (size_t i = 0; i < raw_cloud->points.size(); ++i)
  {
    for (size_t j = 1; j < resolution_ratio + 1; ++j)
    {
      float t;
      t = (1.0 / resolution_ratio) * j;
      pcl::PointXYZI temp_point;
      temp_point.x = (raw_cloud->points[i].x) * t;
      temp_point.y = (raw_cloud->points[i].y) * t;
      temp_point.z = (raw_cloud->points[i].z) * t;
      temp_point.intensity = step(t);
      model_cloud->push_back(temp_point);
    }
  }

  // voxel filtering
  pcl::PointCloud<pcl::PointXYZI>::Ptr model_cloud_filtered(new pcl::PointCloud<pcl::PointXYZI>);

  pcl::VoxelGrid<pcl::PointXYZI> vox;
  vox.setInputCloud(model_cloud);
  vox.setLeafSize(leaf_size, leaf_size, leaf_size);
  vox.filter(*model_cloud_filtered);

  // Convert To ROS data type
  pcl::PCLPointCloud2 model_cloud_p;
  pcl::toPCLPointCloud2(*model_cloud_filtered, model_cloud_p);
  sensor_msgs::PointCloud2 model_output;
  pcl_conversions::fromPCL(model_cloud_p, model_output);
  model_output.header.frame_id = sensor_frame;
  pub1.publish(model_output);

  // pcl transform
  sensor_msgs::PointCloud2 global_pcd;
  pcl_ros::transformPointCloud(base_frame, model_output, global_pcd, listener);

  // Convert the sensor_msgs/PointCloud2 data to pcl/PointCloud
  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);
  pcl::fromROSMsg(global_pcd, *cloud);

  for (size_t i = 0; i < cloud->points.size(); ++i)
  {
    int k = grid_search(cloud->points[i]);

    cell.points[k].intensity += cloud->points[i].intensity;

    if (cell.points[k].intensity >= max_clamping)
    {
      cell.points[k].intensity = max_clamping;
    }
    else if (cell.points[k].intensity <= min_clamping)
    {
      cell.points[k].intensity = min_clamping;
    }
  }

  pcl::PointCloud<pcl::PointXYZRGB> coloured_point_cloud;
  for (size_t i = 0; i < cell.points.size(); ++i)
  {
    if (cell.points[i].intensity > 1)
    {
      pcl::PointXYZRGB temp_point;
      temp_point.x = cell.points[i].x;
      temp_point.y = cell.points[i].y;
      temp_point.z = cell.points[i].z;
      temp_point.r = 135;
      temp_point.g = 206;
      temp_point.b = 235;
      coloured_point_cloud.push_back(temp_point);
    }
  }

  // Convert To ROS data type
  pcl::PCLPointCloud2 cloud_p;
  pcl::toPCLPointCloud2(coloured_point_cloud, cloud_p);
  sensor_msgs::PointCloud2 output;
  pcl_conversions::fromPCL(cloud_p, output);
  output.header.frame_id = base_frame;
  pub2.publish(output);
}
