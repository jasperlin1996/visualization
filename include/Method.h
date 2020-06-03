#pragma once

#include "Volume.h"

class Method{
public:
    Method();
    Method(string, string);
    virtual ~Method();

    Volume volume;
    glm::ivec3 data_shape;
    glm::vec3 voxel_size;

    string inf_filename;
    string raw_filename;

    vector<float> gradient;
};