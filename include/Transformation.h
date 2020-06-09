#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VAO.h"
#include "Shader.h"
#include "Camera.h"

class Transformation{
public:
    Transformation();
    // Transformation(float, float);
    void update_clip(float, float, float, float);
    void normalize_object_position(glm::vec3);
    void set_model();
    void set_projection(Camera&);
    void set_view(Camera&);
    void run();


    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 matrix;
    glm::mat4 rotate_matrix;

    glm::vec3 position;
    float width, height;
    float clip, x, y, z;
};

// class Model{
// public:
//     Model();
//     Model(float, float);
//     void draw(Shader *, Camera);
//     void update();
//     void update_clip(float, float, float, float);
//     static void normalize(glm::vec3);
//     static glm::mat4 model;
//     static glm::mat4 view;
//     static glm::mat4 projection;
//     static float width, height;
//     static vector<VAO> vao;
//     static glm::vec3 position;
//     float clip, x, y, z;

// private:
//     glm::mat4 rotateMatrix;

// };
