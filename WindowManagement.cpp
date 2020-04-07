#include "WindowManagement.h"

using namespace std;

WindowManagement::WindowManagement()
{

}
WindowManagement::~WindowManagement()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
bool WindowManagement::init(float w, float h, string window_name) {
    // glfw init
	GLuint err = glfwInit();
	if (err != GLFW_TRUE) {
		cout << err << endl;
		return false;
	}

    // window init
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow((int)w, (int)h, window_name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(this->window);
    if(this->window == NULL){
        cout << "Failed to create GLFW window" << endl;
        return false;
    }
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return false;
    }
    this->width = w;
    this->height = h;
    this->last_x = w/2;
    this->last_y = h/2;
    setCallbackFunciton();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Depth Test
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);


    cout << "Creating Shader...\n";
    this->myShader = new Shader("./shader.vert", "./shader.frag");
    cout << "Create Shader" << endl;

    // init Model
    this->myModel = Model(w, h);
    this->myCamera = Camera(w, h);
    return (this->window == NULL ? false : true);
}


void WindowManagement::setCallbackFunciton(){
    glfwSetWindowUserPointer(this->window, this);
    auto keyboardCb = [](GLFWwindow * w, int key, int scan, int act, int mod){
        static_cast<WindowManagement*>(glfwGetWindowUserPointer(w))->key_callback(w, key, scan, act, mod);
    };
    auto cursorPosCb = [](GLFWwindow * w, double x_pos, double y_pos){
        static_cast<WindowManagement*>(glfwGetWindowUserPointer(w))->mouse_callback(w, x_pos, y_pos);
    };
    auto scrollCb = [](GLFWwindow * w, double x_offset, double y_offset){
        static_cast<WindowManagement*>(glfwGetWindowUserPointer(w))->scroll_callback(w, x_offset, y_offset);
    };
    auto viewportCb = [](GLFWwindow * w, int width, int height){
        static_cast<WindowManagement*>(glfwGetWindowUserPointer(w))->framebuffer_callback(w, width, height);
    };
    
    // glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(this->window, keyboardCb);
    glfwSetCursorPosCallback(this->window, cursorPosCb);
    glfwSetScrollCallback(this->window, scrollCb);
    glfwSetFramebufferSizeCallback(this->window, viewportCb);
}

void WindowManagement::framebuffer_callback(GLFWwindow * w, int width, int height){
    glViewport(0, 0, width, height);
}

void WindowManagement::mainLoop(){
    while(!glfwWindowShouldClose(this->window)){

        glfwGetFramebufferSize(this->window, (int*)&(this->width), (int*)&(this->height));
        
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // 0.2f 0.3f 0.3f
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->myShader->use();

        // draw some shit
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        this->myModel.draw(this->myShader, this->myCamera);
        // check and call events and swap the buffers
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void WindowManagement::scroll_callback(GLFWwindow * w, double x_offset, double y_offset){
    this->myCamera.update_zoom(y_offset);
}

void WindowManagement::mouse_callback(GLFWwindow * window, double x_pos, double y_pos){
    float x_offset = x_pos - this->last_x;
    float y_offset = y_pos - this->last_y;
    this->last_x = x_pos;
    this->last_y = y_pos;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        this->myCamera.update_yaw(x_offset);
        this->myCamera.update_pitch(y_offset);
    }
}

void WindowManagement::error_callback(int error, const char * description){
	cout << "Error: " << description << endl;
}

void WindowManagement::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods){
    if (action == GLFW_RELEASE) return;
    switch(key){
        case GLFW_KEY_Q:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_KP_ADD:
            this->myCamera.update_far(10.0);
            break;
        case GLFW_KEY_KP_SUBTRACT:
            this->myCamera.update_far(-10.0);
            break;
        default:
            break;
    }
}

void WindowManagement::set_vao_data(vector<float> data){
    Model::vao.push_back(VAOManagement::generateVAO(data));
}


bool WindowManagement::init(int w, int h, string window_name, vector<PositionVec3> vertexData) {
    // glfw init
	GLuint err = glfwInit();
	if (err != GLFW_TRUE) {
		cout << err << endl;
		return false;
	}

    // window init
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow((int)w, (int)h, window_name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(this->window);
    if(this->window == NULL){
        cout << "Failed to create GLFW window" << endl;
        return false;
    }
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return false;
    }
    
    this->myModel = Model(w, h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Depth Test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    return (this->window == NULL ? false : true);
}