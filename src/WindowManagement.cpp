#include "WindowManagement.h"

#ifdef __APPLE__
    #define GLFW_MINOR_VERSION 1
#else
    #define GLFW_MINOR_VERSION 3
#endif

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

void APIENTRY debug_callback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar *message,
    const void *userParam
)
{
    // ignore non-significant error / warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    cout << "Debug message (" << id << "): " << message << '\n';

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            cout << "Source: API" << '\n';
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            cout << "Source: Window System" << '\n';
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            cout << "Source: Shader Compiler" << '\n';
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            cout << "Source: Third Party" << '\n';
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            cout << "Source: Application" << '\n';
            break;
        case GL_DEBUG_SOURCE_OTHER:
            cout << "Source: Other" << '\n';
            break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            cout << "Type: Error" << '\n';
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            cout << "Type: Deprecated Behaviour" << '\n';
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            cout << "Type: Undefined Behaviour" << '\n';
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            cout << "Type: Portability" << '\n';
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            cout << "Type: Performance" << '\n';
            break;
        case GL_DEBUG_TYPE_MARKER:
            cout << "Type: Marker" << '\n';
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            cout << "Type: Push Group" << '\n';
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            cout << "Type: Pop Group" << '\b';
            break;
        case GL_DEBUG_TYPE_OTHER:
            cout << "Type: Other" << '\n';
            break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            cout << "Severity: high" << '\n';
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            cout << "Severity: medium" << '\n';
            break;
        case GL_DEBUG_SEVERITY_LOW:
            cout << "Severity: low" << '\n';
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            cout << "Severity: notification" << '\n';
            break;
    }
}

bool WindowManagement::init(float w, float h, string window_name) {
    glfwSetErrorCallback(WindowManagement::error_callback);

    // generate data files' list & methods' list
    this->generate_combo();
    // init clip plane
    this->clip = 0.0f;
    this->x = -1.0f;
    this->y = -1.0f;
    this->z = -1.0f;
    // glfw init
	GLuint err = glfwInit();
	if (err != GLFW_TRUE) {
		cout << err << endl;
		return false;
	}

    // window init
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef __APPLE__
    // dedug context
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    this->window = glfwCreateWindow((int)w, (int)h, window_name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(this->window);

    // FPS
    glfwSwapInterval(1);

    if(this->window == NULL){
        cout << "Failed to create GLFW window" << endl;
        return false;
    }
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return false;
    }

    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
#ifdef __APPLE__
    ImGui_ImplOpenGL3_Init("#version 410");
#else
    ImGui_ImplOpenGL3_Init("#version 430");
#endif
    //
    this->width = w;
    this->height = h;
    this->last_x = w/2;
    this->last_y = h/2;
    set_callback_function();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifndef __APPLE__
    // debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debug_callback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
    // Depth Test
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);

    // Blend (alpha)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable point size flexibility
    glEnable(GL_PROGRAM_POINT_SIZE);

    // cout << "Creating Shader...\n";
    // this->myShader = new Shader("./shader.vert", "./shader.frag");
    // cout << "Create Shader" << endl;

    // // init Model
    // this->myModel = Model(w, h);
    this->transformation = Transformation((float)w, (float)h);
    cout << "Createing Shader...\n";
    this->shaders[METHODS::ISO_SURFACE] = Shader("./src/shader/iso_surface/shader.vert", "./src/shader/iso_surface/shader.frag");
    this->shaders[METHODS::VOLUME_RENDERING] = Shader("./src/shader/slicing/shader.vert", "./src/shader/slicing/shader.frag");
    cout << "Shader ID: " << this->shaders[METHODS::ISO_SURFACE].ID << endl;
    cout << "Shader ID: " << this->shaders[METHODS::VOLUME_RENDERING].ID << endl;
    cout << "Shader Created!\n";

    this->myCamera = Camera(w, h);
    return (this->window == NULL ? false : true);
}


void WindowManagement::set_callback_function(){
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
    // glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(this->window, keyboardCb);
    glfwSetCursorPosCallback(this->window, cursorPosCb);
    glfwSetScrollCallback(this->window, scrollCb);
    glfwSetFramebufferSizeCallback(this->window, viewportCb);
}


void WindowManagement::framebuffer_callback(GLFWwindow * w, int width, int height){
    glViewport(0, 0, width, height);
}


void WindowManagement::generate_combo(){
    // generate methods combo
    this->methods["Iso Surface"] = METHODS::ISO_SURFACE;
    this->methods["Slicing"] = METHODS::VOLUME_RENDERING;

    // generate filenames combo
    DIR *dp;
    dirent *dirp;

    if((dp = opendir("./Data/Scalar/")) != NULL){
        while((dirp = readdir(dp)) != NULL){
            string temp = dirp->d_name;
            size_t index = temp.find(".inf");

            if(index != string::npos) this->filenames.push_back(temp.substr(0, index));
        }
    }

    sort(this->filenames.begin(), this->filenames.end());
}


void WindowManagement::gui(){
    static METHODS current_method = METHODS::ISO_SURFACE;
    static string selected_method = "Iso Surface";
    static string selected_filename = "engine";
    static int iso_value = 80, min_iso_value = 80, max_iso_value = 80, last_iso_value = iso_value;

    static bool is_load = false, is_show = false;
    // IMGUI
    // ImGui_ImplOpenGL3_NewFrame();
    // ImGui_ImplGlfw_NewFrame();
    // ImGui::NewFrame();

    // UI Design
    // set Controller position and size
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(this->width / 3, this->height / 2), ImGuiCond_Once);


    ImGui::Begin("Setting");
    ImGui::Text("Select Model");
    // Combos
    if (ImGui::BeginCombo("Method", selected_method.c_str())) {
        for (auto it = methods.begin(); it != methods.end(); it++) {
            bool selected = (this->selected_method == it->first);
            
            if (ImGui::Selectable(it->first.c_str(), selected)) {
                selected_method = it->first;
                is_load = false;
                is_show = false;
            }
            if (selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (ImGui::BeginCombo("Filename", selected_filename.c_str())) {
        for (size_t i = 0; i < this->filenames.size(); i++) {
            bool selected = (selected_method == this->filenames[i]);
            
            if (ImGui::Selectable(this->filenames[i].c_str(), selected)) {
                selected_filename = this->filenames[i];
                is_load = false;
                is_show = false;
            }
            if (selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (!is_load && ImGui::Button("Load")) {
        // this->load_model();
        this->load(selected_filename, this->methods[selected_method], false);
        is_load = true;
        if (current_method == METHODS::ISO_SURFACE) {
            min_iso_value = (int)(this->models.back().method->volume.min);
            max_iso_value = (int)(this->models.back().method->volume.max);

            cout << "load: ";
            cout << min_iso_value << ' ' << max_iso_value << '\n';
        }
        ImGui::SameLine();
    }

    if (!is_show && is_load && ImGui::Button("Show")) {
        is_show = true;
        this->show();
        ImGui::SameLine();
    }
    if (ImGui::Button("Clear")) {
        // manually free memory
        for (size_t i = 0; i < this->models.size(); i++) {
            this->models[i].free();
        }
        this->models.clear();
        is_load = false;
        is_show = false;
    }
    if (is_show) {
        this->draw();
    }
    if (this->methods[selected_method] == METHODS::ISO_SURFACE) {
        ImGui::SliderInt("iso value", &iso_value, min_iso_value, max_iso_value);
        if(last_iso_value != iso_value) {
            last_iso_value = iso_value;
            ((IsoSurface *)(this->models.back().method))->set_iso_value(iso_value);
            ((IsoSurface *)(this->models.back().method))->run();
            this->models.back().update_vao_data();
        }
    }
    ImGui::Text("Slicing Plane");


    ImGui::SliderFloat("x", &(this->x), -1.0f, 1.0f);
    ImGui::SliderFloat("y", &(this->y), -1.0f, 1.0f);
    ImGui::SliderFloat("z", &(this->z), -1.0f, 1.0f);
    ImGui::SliderFloat("clip", &(this->clip), -100.0f, 100.0f);
    {
        float length = sqrt(this->x*this->x+this->y*this->y+this->z*this->z);
        if (length <= 0.01) length = 0.01;
        this->x /= length;
        this->y /= length;
        this->z /= length;
        // this->myModel.update_clip(clip, x, y, z);
        // this->transformation.update_clip(clip, x, y, z);
    }
    ImGui::End();
    //

}


void WindowManagement::mainLoop(){
    while(!glfwWindowShouldClose(this->window)){
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // 0.2f 0.3f 0.3f
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // IMGUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // gui and draw
        this->gui();

        glfwGetFramebufferSize(this->window, (int*)&(this->width), (int*)&(this->height));

        // check and call events and swap the buffers

        // IMGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}


void WindowManagement::scroll_callback(GLFWwindow * w, double x_offset, double y_offset){
    this->myCamera.update_zoom(y_offset);
}


void WindowManagement::mouse_callback(GLFWwindow * window, double x_pos, double y_pos){
    if(ImGui::IsAnyMouseDown() && ImGui::IsAnyWindowFocused()) return;

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
        // case GLFW_KEY_C:
        //     this->myModel.update_clip(10.0, this->myModel.x, this->myModel.y, this->myModel.z);
        //     break;
        // case GLFW_KEY_V:
        //     this->myModel.update_clip(-10.0, this->myModel.x, this->myModel.y, this->myModel.z);
        //     break;
        default:
            break;
    }
}


// void WindowManagement::set_vao_data(vector<float> data){
//     Model::vao.push_back(VAOManagement::generateVAO(data));
// }


// void WindowManagement::load_model(){
//     string model_name = "./Data/Scalar/engine.inf";
//     IsoSurface iso("./Data/Scalar/engine.inf", "./Data/Scalar/engine.raw", 80);
//     iso.run();

//     glm::vec3 data_shape = iso.get_shape();
//     data_shape = -data_shape/2.0f;
//     data_shape *= iso.get_voxel_size();

//     Model::normalize(data_shape);

//     this->set_vao_data(iso.get_data());
// }


void WindowManagement::draw(){
    // TODO:
    //   Enable/disable Model(s) by their METHODS
    //   Different METHODS have different Shader

    METHODS last_method = this->models.back().get_method_choice();
    this->shaders[last_method].use();

    for (size_t i = 0; i < this->models.size(); i++) {
        // Transformation temp_transformation;
        // this->shaders[METHODS::ISO_SURFACE].use();
        glm::vec3 data_shape = ((this->models[i]).method)->data_shape;
        data_shape = -data_shape/2.0f;
        data_shape *= ((this->models[i]).method)->voxel_size;

        this->transformation.normalize_object_position(data_shape);
        this->transformation.set_model();
        this->transformation.set_view(this->myCamera);
        this->transformation.set_projection(this->myCamera);
        this->transformation.run();

        if (last_method == METHODS::ISO_SURFACE) {
            // this->shaders[METHODS::ISO_SURFACE].use();
            this->shaders[METHODS::ISO_SURFACE].set_uniform("color", glm::vec3(0.3f, 0.5f, 0.3f));
        
            this->shaders[METHODS::ISO_SURFACE].set_uniform("model", this->transformation.model);
            this->shaders[METHODS::ISO_SURFACE].set_uniform("matrix", this->transformation.matrix);
            this->shaders[METHODS::ISO_SURFACE].set_uniform("clip_plane", glm::vec4(this->x, this->y, this->z, this->clip));
            this->shaders[METHODS::ISO_SURFACE].set_uniform("light_pos", -this->myCamera.get_position());
            this->shaders[METHODS::ISO_SURFACE].set_uniform("view_pos", this->myCamera.get_position());
            this->shaders[METHODS::ISO_SURFACE].set_uniform("light_color", glm::vec3(1.0f));
        }
        else if (last_method == METHODS::VOLUME_RENDERING) {
            // TODO VOLUME_RENDERING Shader
            this->shaders[METHODS::VOLUME_RENDERING].set_uniform("model", this->transformation.model);
            this->shaders[METHODS::VOLUME_RENDERING].set_uniform("matrix", this->transformation.matrix);
            this->shaders[METHODS::VOLUME_RENDERING].set_uniform("clip_plane", glm::vec4(this->x, this->y, this->z, this->clip));
            this->shaders[METHODS::VOLUME_RENDERING].set_uniform("light_pos", -this->myCamera.get_position());
            this->shaders[METHODS::VOLUME_RENDERING].set_uniform("light_color", this->myCamera.get_position());
            this->shaders[METHODS::VOLUME_RENDERING].set_uniform("view_pos", glm::vec3(1.0f));

            if (((VolumeRendering *)(this->models[i].method))->axis_aligned(this->myCamera.get_direction())) {
                this->models[i].update_vao_data();
            }
        }
        // Only enable models with same method with the last model
        if (this->models[i].get_method_choice() == last_method) {
            this->models[i].draw();
        }
    }
}


void WindowManagement::show(){
    // only choice the last loaded method's shader
    METHODS temp_method = this->models.back().get_method_choice();

    // use this shader
    this->shaders[temp_method].use();
    
    // TODO set_vao_data
    this->models.back().set_vao_data();
    cout << "set vao data\n";
    
}


void WindowManagement::load(string filename, METHODS method, bool update){
    string data_dir = "./Data";

    // this->shaders[method].use(); // TODO might not needed

    switch(method) {
        case (METHODS::NONE): 
            break;
        case (METHODS::ISO_SURFACE): {
            cout << "Method: Iso Surface\n";

            filename = data_dir + "/Scalar/" + filename;
            cout << filename << endl;
            Model temp_model(filename + ".inf", filename + ".raw", method);
            ((IsoSurface *)temp_model.method)->set_iso_value(80);
            temp_model.run();

            this->models.push_back(temp_model);
            break;
        }
        case (METHODS::VOLUME_RENDERING): {
            cout << "Method: Volume Rendering (Slicing method)\n";

            filename = data_dir + "/Scalar/" + filename;

            Model temp_model(filename + ".inf", filename + ".raw", method);
            ((VolumeRendering *)temp_model.method)->axis_aligned(this->myCamera.get_direction());
            // temp_model.run();

            temp_model.enable_textures(2);
            temp_model.init_texture(GL_TEXTURE_1D, 0);
            temp_model.init_texture(GL_TEXTURE_3D, 1);
            temp_model.set_texture(0);
            temp_model.set_texture(1);

            this->models.push_back(temp_model);
            break;
        }
        default:
            break;
    }
}
