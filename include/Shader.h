#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader{
public:
    // the program ID
    GLuint ID;
    Shader();
    // ctor reads and builds the shader
    Shader(const char*, const char*);

    // activate the shader
    void use();
    // utility uniform functions
    void set_uniform(const string &name, bool value) const;
    void set_uniform(const string &name, int value) const;
    void set_uniform(const string &name, float value) const;
    void set_uniform(const string &name, glm::vec3 value) const;
    void set_uniform(const string &name, glm::vec4 value) const;
    void set_uniform(const string &name, glm::mat4 value) const;
};

