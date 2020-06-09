#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VAO.h"
#include "Shader.h"
#include "Camera.h"
#include "Transformation.h"
#include "constants.h"
#include "Method.h"
#include "IsoSurface.h"
//#include "VolumeRendering.h"

class Model{
public:
    Model();
    Model(string, string, METHODS);
    ~Model();
    float clip, x, y, z;
    //
    void draw(Transformation&);
    METHODS get_method_choice();
    void run();
    void set_vao_data();
    Method* method;
private:
    glm::mat4 rotate_matrix;
    //
    string inf_filename, raw_filename;
    METHODS method_choice;
    vector<VAO> vao;
};
