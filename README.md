# Parameter

proxy_mapping/launch/proxy_mapping.launch

![image](https://user-images.githubusercontent.com/35325906/71657935-4208e180-2d85-11ea-849a-ec1121aef589.png)

  <topics>
map_publish_topic           : name of map representation topic <Pointcloud>
sensor_model_publish_topic  : name of sensor model visualization topic <Pointcloud>, It represents the updating points
pcl_subscribe_topic         : name of the subscribing topic that published from the distance sensor

	<map>
map_resolution 		          : Map resolution in meter
x_min 			                : mapping range in meter, x minimum
x_max 			                : mapping range in meter, x maximum
y_min 			                : mapping range in meter, y minimum
y_max 			                : mapping range in meter, y maximum
z_min 			                : mapping range in meter, z minimum
z_max 			                : mapping range in meter, z maximum

resolution_ratio	          : a number of updating points on the line between the sensor and the detected point.

leaf_size			              : filter grid size for voxel filter, updating points are filtered before they update each grid cells to increase the accuracy.

max_clamping		            : clamping value for dynamic adoptation (option), check the octomap paper
min_clamping		            : clamping value for dynamic adoptation (option), check the octomap paper

	<pointcloud>
sensor_frame       	        : name of the sensor frame in the tf-tree
base_frame       		        : name of the global frame in the tf-tree
