#pragma once

#include "Shader.h"
#include "VAO.h"
#include "Model.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class WindowManagement{
public:
    WindowManagement();
    ~WindowManagement();
    bool init(float, float, string);
    bool init(int, int, string, vector<PositionVec3>);
    void setCallbackFunciton();
    void mainLoop();
    void set_vao_data(vector<float>);
    static void error_callback(int, const char *);
    void key_callback(GLFWwindow *, int, int, int, int);
    void mouse_callback(GLFWwindow *, double, double);
    void scroll_callback(GLFWwindow *, double, double);
    void framebuffer_callback(GLFWwindow *, int, int);

private:
    float width, height, last_x, last_y;
    Shader * myShader;
    Model myModel;
    GLFWwindow * window;
    Camera myCamera;
};