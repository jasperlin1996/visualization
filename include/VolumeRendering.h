#pragma once

#include <iostream>
#include <cmath>
#include "Method.h"
#include "Volume.h"
#include "constants.h"

using namespace std;

class VolumeRendering: public Method{
public:
    VolumeRendering();
    VolumeRendering(string, string);
    void gen_texture_3d();
    void gen_texture_1d();
    void gen_slicing_clip();
private:
    string inf_filename, raw_filename;
    vector<float> texture_1d;
    vector<float> texture_3d;
    vector<vector<float> > texture_vertex;
    vector<vector<float> > axis_template;
};

