#include "../include/proxy_mapping.h"

P_mapping::P_mapping()
{
  n.getParam("proxy_mapping/map_publish_topic", map_publish_topic);
  n.getParam("proxy_mapping/sensor_model_publish_topic", sensor_model_publish_topic);
  n.getParam("proxy_mapping/pcl_subscribe_topic", pcl_subscribe_topic);
  n.getParam("proxy_mapping/map_resolution", map_resolution);
  n.getParam("proxy_mapping/x_min", x_min);
  n.getParam("proxy_mapping/x_max", x_max);
  n.getParam("proxy_mapping/y_min", y_min);
  n.getParam("proxy_mapping/y_max", y_max);
  n.getParam("proxy_mapping/z_min", z_min);
  n.getParam("proxy_mapping/z_max", z_max);
  n.getParam("proxy_mapping/resolution_ratio", resolution_ratio);
  n.getParam("proxy_mapping/leaf_size", leaf_size);
  n.getParam("proxy_mapping/sensor_frame", sensor_frame);
  n.getParam("proxy_mapping/base_frame", base_frame);
  n.getParam("proxy_mapping/max_clamping", max_clamping);
  n.getParam("proxy_mapping/min_clamping", min_clamping);

  a = round((x_max-x_min)/map_resolution);
  b = round((y_max-y_min)/map_resolution);
  c = round((z_max-z_min)/map_resolution);

  for (int x = 0; x < a; x++ )
  {
    for (int y = 0; y < b; y++ )
    {
      for (int z = 0; z < c; z++ )
      {
        pcl::PointXYZI temp_point;
        temp_point.x = x_min + (x*map_resolution);
        temp_point.y = y_min + (y*map_resolution);
        temp_point.z = z_min + (z*map_resolution);
        temp_point.intensity = 0.0;
        cell.push_back(temp_point);
      }
    }
  }

  // cout<<cell.points.size()<<endl;
  // pcl::PointXYZI temp_point2;
  // temp_point2.x = 0.1;
  // temp_point2.y = 0.2;
  // temp_point2.z = 0.3;

  // cout<<cell.points[grid_search(temp_point2)].x<<cell.points[grid_search(temp_point2)].y<<cell.points[grid_search(temp_point2)].z;


  // cellPTR = cell.makeShared();

  pub1 = n.advertise<sensor_msgs::PointCloud2>(sensor_model_publish_topic, 1);
  pub2 = n.advertise<sensor_msgs::PointCloud2>(map_publish_topic, 1);
  sub = n.subscribe(pcl_subscribe_topic, 1, &P_mapping::pclCallback, this);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "node");

  P_mapping nice;

  ros::spin();

  return 0;
}
