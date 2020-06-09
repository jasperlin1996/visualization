#include "Transformation.h"

Transformation::Transformation(){
    this->rotate_matrix = glm::mat4(1.0f);
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    
    this->view = glm::lookAt(glm::vec3(0.0f, 0.0f, 300.0f),
                            glm::vec3(0.0f, 0.0f, -1.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));
    this->model = glm::mat4(1.0f);
    this->projection = glm::mat4(1.0f);
}


Transformation::Transformation(float width, float height)
    : Transformation::Transformation() {
    this->width = width;
    this->height = height;
    this->projection = glm::perspective(
        glm::radians(45.0f),
        this->width/this->height,
        0.1f,
        500.0f
    );
}

void Transformation::normalize_object_position(glm::vec3 pos){
    this->position = pos;
}

// zoom in/out
void Transformation::set_projection(Camera& camera){
    // cout << camera.left << ' ' << camera.right << ' ' << camera.bottom << ' ' << camera.top << ' ' << camera.near << ' ' << camera.far << endl;
    this->projection = glm::ortho(
        camera.left, camera.right,
        camera.bottom, camera.top,
        camera.near, camera.far
    );
}

void Transformation::set_view(Camera& camera){
    this->view = glm::lookAt(camera.get_position(), camera.get_position() + camera.get_direction(), camera.get_up());
}

void Transformation::set_model(){
    this->model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime()*glm::radians(30.f)*0, glm::vec3(0.0f, 1.0f, 0.0f));
    this->model = this->model * glm::translate(glm::mat4(1.0f), this->position);
}

void Transformation::run(){
    this->matrix = this->projection * this->view * this->model;
}

void Transformation::update_clip(float clip, float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
    this->clip = clip;
}