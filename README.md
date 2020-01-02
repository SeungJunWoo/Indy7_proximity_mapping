# Occupancy-Grid Mapping

![image](https://user-images.githubusercontent.com/35325906/71663271-d67c3f80-2d97-11ea-9d56-ea544e9eee86.png)

## Installation

### Dependencies

This software is built on the Robotic Operating System ([ROS]), which needs to be [installed](http://wiki.ros.org) first. Additionally, it depends on following software:

- [Point Cloud Library (PCL)](http://pointclouds.org/) (point cloud processing).

### Building

In order to install the Robot-Centric Elevation Mapping, clone the latest version from this repository into your catkin workspace and compile the package using ROS.

    cd catkin_workspace/src
    git clone https://github.com/anybotics/elevation_mapping.git
    cd ../
    catkin_make

## Parameter

proxy_mapping/launch/proxy_mapping.launch

![image](https://user-images.githubusercontent.com/35325906/71657935-4208e180-2d85-11ea-849a-ec1121aef589.png)

#### Pointcloud topic name

- **`map_publish_topic`**           

name of map representation topic <Pointcloud>

- **`sensor_model_publish_topic`**  

name of sensor model visualization topic <Pointcloud>, It represents the updating points, red points from the figure above

- **`pcl_subscribe_topic`**         

name of the subscribing topic that published from the distance sensor

#### Map setting

- **`map_resolution`** 		          

Map resolution in meter

- **`x_min`** 			                

mapping range in meter, x minimum

- **`x_max`** 			                

mapping range in meter, x maximum

- **`y_min`** 			                

mapping range in meter, y minimum

- **`y_max`** 			                

mapping range in meter, y maximum

- **`z_min`** 			                

mapping range in meter, z minimum

- **`z_max`** 			                

mapping range in meter, z maximum

- **`resolution_ratio`**	          

a number of updating points on the line between the sensor and the detected point.

- **`leaf_size`**			              

filter grid size for voxel filter, updating points are filtered before they update each grid cells to increase the accuracy.

- **`max_clamping`**		            

clamping value for dynamic adoptation (option), check the octomap paper

- **`min_clamping`**		            

clamping value for dynamic adoptation (option), check the octomap paper

#### Frame name

- **`sensor_frame`**       	        

name of the sensor frame in the tf-tree

- **`base_frame`**       		        

name of the global frame in the tf-tree


## Sensor model

you can customize your own sensor model in **proxy_mapping/src/sensor_model.cpp**.

input: t, the point between the sensor and an object (t=0, sensor position),(t=1, object position)

output: log-odd update value
