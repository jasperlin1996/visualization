#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"

#include "Method.h"

#include <iostream>
#include <fstream>

class StreamLine: public Method{
    using super = Method;
public:
    StreamLine();
    ~StreamLine();
    StreamLine(string);
    void load_data(string);
    vector<float> get_data();
    void run();
    
    bool is_inside(glm::vec2);
    glm::vec2 vector_interpolation(glm::vec2);
    glm::vec2 rk2(glm::vec2, float);
    glm::vec3 transfer_function(float);

    void generate_table();
    void generate_streamline();
    void generate_streamline_grid();
private:
    glm::ivec2 data_shape;
    vector<vector<bool> > grid_table;
    vector<vector<glm::vec2> > data;
    vector<vector<glm::vec2> > streamlines;
    float min_vector_magnitude, max_vector_magnitude;
    int total_point_size;
};