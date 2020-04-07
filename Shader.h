#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
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
    void setBool(const string &, bool) const;
    void setInt(const string &, int) const;
    void setFloat(const string &, float) const;
};

