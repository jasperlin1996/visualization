#pragma once

#include <iostream>
#include <cmath>
#include "Method.h"
#include "Volume.h"
#include "constants.h"
#define _USE_MATH_DEFINES

#define ZERO 0.00001
// #define OUTPUT
using namespace std;

class IsoSurface : public Method{
    using super = Method;
public:
    IsoSurface(string, string);
    IsoSurface(string, string, int); // set init iso_value
    ~IsoSurface();
    void set_iso_value(int);
    void run();
    vector<float> get_data();
    glm::ivec3 get_shape();
    glm::vec3 get_voxel_size();
    
private:
    int iso_value;
    string infFilename, rawFilename;
    glm::ivec3 data_shape;
    glm::vec3 voxel_size;

    vector<float> data;

    glm::vec3 vertex_interpolation(glm::vec3, glm::vec3, float, float);
    pair<glm::vec3, glm::vec3> gradient_interpolation(glm::vec3, glm::vec3, float, float, glm::vec3, glm::vec3);
    void surface_intersection(pair<glm::vec3, glm::vec3> [], glm::vec3 [], float [], glm::vec3 [],int);
};