#pragma once

#include <iostream>
#include <cmath>
#include "Volume.h"
#include "constants.h"
#define _USE_MATH_DEFINES
// #define isovalue 80
// #define isolevel 80
#define ZERO 0.00001
// #define OUTPUT
using namespace std;

class IsoSurface{
public:
    IsoSurface(string, string, int);
    void run();
    vector<float> get_data();
    glm::ivec3 get_shape();
    glm::vec3 get_voxel_size();
    
private:
    vector<float> data;
    Volume *volume;
    glm::ivec3 data_shape;
    glm::vec3 voxel_size;
    string infFilename, rawFilename;
    int isovalue;
    glm::vec3 vertex_interpolation(glm::vec3, glm::vec3, float, float);
    pair<glm::vec3, glm::vec3> gradient_interpolation(glm::vec3, glm::vec3, float, float, glm::vec3, glm::vec3);
    void surface_intersection(pair<glm::vec3, glm::vec3> [], glm::vec3 [], float [], glm::vec3 [],int);
};