#include "Camera.h"

using namespace std;

Camera::Camera(){
    this->zoom = 4.0f;
    this->yaw = 0.0f;
    this->pitch = 90.0f;
}

Camera::Camera(float width, float height) : Camera::Camera() {
    this->left = -width/zoom;
    this->right = width/zoom;
    this->bottom = -height/zoom;
    this->top = height/zoom;
    this->near = 0.1f;
    this->far = 400.0f;
    this->camera_radius = 300.0f;
    this->center = glm::vec3(0.0f, 0.0f, 0.0f);
    // this->position = glm::vec3(0.0f, 0.0f, this->camera_radius);
    this->direction = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::update_far(float far){
    this->far += far;
}

glm::vec3 Camera::get_position(){
    return this->center - (this->direction * this->camera_radius);
}

glm::vec3 Camera::get_direction(){
    return this->direction;
}

glm::vec3 Camera::get_up(){
    return this->up;
}

void Camera::shift_pos(glm::vec4 pos){
    // left += pos[0];
    // right += pos[1];
    // bottom += pos[2];
    // top += pos[3];
}

// None linear : (
void Camera::update_zoom(float ratio){
    this->left *= this->zoom;
    this->right *= this->zoom;
    this->bottom *= this->zoom;
    this->top *= this->zoom;
    this->zoom += ratio;
    if(this->zoom < 1.0) this->zoom = 1.0;
    this->left /= this->zoom;
    this->right /= this->zoom;
    this->bottom /= this->zoom;
    this->top /= this->zoom;
}

void Camera::update_camera_direction(){
    this->direction.x = -sin(glm::radians(this->pitch)) * sin(glm::radians(this->yaw));
    this->direction.y = -cos(glm::radians(this->pitch));
    this->direction.z = -sin(glm::radians(this->pitch)) * cos(glm::radians(this->yaw));
    this->direction = glm::normalize(this->direction);

    glm::vec3 right = glm::normalize(glm::cross(this->direction, glm::vec3(0.0f, 1.0f, 0.0f))); // member consider
    this->up = glm::normalize(glm::cross(right, this->direction));
}

void Camera::update_yaw(float yaw){
    const float sensitivity = 0.2f;

    this->yaw -= yaw * sensitivity;
    this->update_camera_direction();
}

void Camera::update_pitch(float pitch){
    const float sensitivity = 0.2f;

    this->pitch -= pitch * sensitivity;
    if(this->pitch > 179.0f) this->pitch = 179.0f;
    if(this->pitch < 1.0f) this->pitch = 1.0f;
    this->update_camera_direction();
}

