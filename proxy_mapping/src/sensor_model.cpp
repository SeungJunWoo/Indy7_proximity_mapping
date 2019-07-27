#include "../include/proxy_mapping.h"

float P_mapping::step(float t){
    float value;
    if(t<1){
        value = -1;
    }
    else{
        value = 1;
    }
    return value;
}