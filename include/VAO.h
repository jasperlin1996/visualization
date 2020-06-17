#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include <vector>
#include <iostream>

typedef glm::vec3 PositionVec3;
typedef glm::vec3 NormalVec3;

using namespace std;

typedef struct Texture {
    // GL_TEXTURE_3D ...
    GLenum target;
    // glGenTextures(1, &(this->texture[i].textures));
    GLuint textures;
} Texture;

class VAO{
public:
    GLuint vao;
    int count = 0;
};

class VAOManagement{
public:
    static VAO generateVAO(vector<float> vertexData, vector<int> vao_setting);
    // static void drawVAO(vector<VAO>, Shader *); // Version 1
    // static void drawVAO(vector<VAO>&, GLenum, GLenum); // Version 2
    static void drawVAO(vector<VAO>&, bool, vector<Texture>&, GLenum, GLenum); // Version 3
};