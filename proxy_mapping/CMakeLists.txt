cmake_minimum_required(VERSION 2.8.3)
project(proxy_mapping)


find_package(catkin REQUIRED COMPONENTS
  pcl_conversions
  pcl_ros
  roscpp
  sensor_msgs

)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES fourlegs
  CATKIN_DEPENDS pcl_conversions pcl_ros roscpp sensor_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(proxy_mapping src/main.cpp
			     src/pcl_reciver.cpp 
			     src/sensor_model.cpp
			     src/grid_search.cpp
			     include/proxy_mapping.h)
target_link_libraries(proxy_mapping ${catkin_LIBRARIES})
add_dependencies(proxy_mapping ${catkin_EXPORTED_TARGETS})

