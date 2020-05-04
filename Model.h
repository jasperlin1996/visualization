#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VAO.h"
#include "Shader.h"
#include "Camera.h"

class Model{
public:
    Model();
    Model(float, float);
    void draw(Shader *, Camera);
    void update();
    void update_clip(float, float, float, float);
    static void normalize(glm::vec3);
    static glm::mat4 model;
    static glm::mat4 view;
    static glm::mat4 projection;
    static float width, height;
    static vector<VAO> vao;
    static glm::vec3 position;
    float clip, x, y, z;

private:
    glm::mat4 rotateMatrix;

};
