#pragma once

#include <map>

#include "Shader.h"
#include "VAO.h"
#include "Model.h"
#include "IsoSurface.h"
#include "VolumeRendering.h"
#include "Transformation.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "implot/implot.h"

#include <dirent.h>

class WindowManagement{
public:
    WindowManagement();
    ~WindowManagement();
    bool init(float, float, string);
    void generate_combo();
    void gui();
    void load(string, METHODS, bool);
    void show();
    void draw();
    void mainLoop();
    void set_callback_function();
    void set_vao_data(vector<float>);
    static void error_callback(int, const char *);
    void key_callback(GLFWwindow *, int, int, int, int);
    void mouse_callback(GLFWwindow *, double, double);
    void scroll_callback(GLFWwindow *, double, double);
    void framebuffer_callback(GLFWwindow *, int, int);
    void load_model();

private:
    float width, height, last_x, last_y;
    float clip, x, y, z;
    string selected_method, selected_filename;
    Transformation transformation;
    Camera myCamera;
    map<METHODS, Shader> shaders;
    vector<Model> models;
    map<string, METHODS> methods;
    vector<string> filenames;
    GLFWwindow * window;
};
