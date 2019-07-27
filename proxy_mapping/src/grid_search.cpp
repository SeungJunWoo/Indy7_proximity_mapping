#include "../include/proxy_mapping.h"

int P_mapping::grid_search(pcl::PointXYZI point){
    float x = point.x;
    float y = point.y;
    float z = point.z;
    
    int xn = round((x-x_min)/map_resolution);
    int yn = round((y-y_min)/map_resolution);
    int zn = round((z-z_min)/map_resolution);

    int k = ((b*c)*(xn-1)) + (c*(yn-1)) + zn-1;

    return k;
}