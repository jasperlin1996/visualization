#pragma once

#include "glad/glad.h"

#include <iostream>
#include <cmath>
#include "Method.h"
#include "Volume.h"
#include "constants.h"

using namespace std;

class VolumeRendering: public Method{
    using super = Method;
public:
    VolumeRendering();
    VolumeRendering(string, string);

    int axis_index;

    void gen_texture_3d();
    void gen_texture_1d();
    void gen_slicing_clip();
    bool axis_aligned(glm::vec3);

    vector<float>& get_data();
    vector<float>& get_texture_1d();
    vector<float>& get_textrue_3d();

    void set_texture(int, GLenum);
private:
    string inf_filename, raw_filename;
    vector<float> texture_1d;
    vector<float> texture_3d;
    vector<vector<float> > texture_vertex;
    vector<vector<float> > axis_template;

    int compare(glm::vec3);
};

