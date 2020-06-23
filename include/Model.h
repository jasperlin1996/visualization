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
#include "VolumeRendering.h"
#include "StreamLine.h"
#include "SammonMapping.h"

class Model{
public:
    Model();
    Model(string, string, METHODS);
    Model(string, METHODS);
    ~Model();
    float clip, x, y, z;

    void draw();
    METHODS get_method_choice();
    void run();
    void set_vao_data();
    void update_vao_data();
    void init_texture(GLenum, int);
    void enable_textures(int);
    void set_texture(int);
    void free();
    Method* method;

private:
    bool use_texture;
    vector<Texture> textures;
    string inf_filename, raw_filename;
    METHODS method_choice;
    vector<VAO> vao;
};
