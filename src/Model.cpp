#include "Model.h"

using namespace std;

float Model::width  = 800.0;
float Model::height = 600.0;
glm::mat4 Model::model = glm::mat4(1.0f);
glm::mat4 Model::view  = glm::mat4(1.0f);
glm::mat4 Model::projection = glm::mat4(1.0f);
vector<VAO> Model::vao;
glm::vec3 Model::position = glm::vec3(0.0f);

Model::Model(){
    Model::projection = glm::perspective(glm::radians(45.0f), Model::width/Model::height, 0.1f, 500.0f);
    Model::view = glm::lookAt(glm::vec3(0.0f, 0.0f, 300.0f),
                            glm::vec3(0.0f, 0.0f, -1.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));
    
    this->rotateMatrix = glm::mat4(1.0f);
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Model::Model(float width, float height) : Model::Model() {
    Model::width  = width;
    Model::height = height;
    this->rotateMatrix = glm::mat4(1.0f);
    this->rotateMatrix = glm::rotate(this->rotateMatrix, (float)glfwGetTime()*glm::radians(1.f), glm::vec3(0.0f, 100.0f, 0.0f));
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);

    // Model::projection = glm::perspective(glm::radians(45.0f), Model::width/Model::height, 0.1f, 800.0f);
    Model::projection = glm::ortho(0.0f-width/1, width/1, 0.0f-height/1, height/1, 0.1f, 400.0f);
    Model::view = glm::lookAt(glm::vec3(0.0f, 0.0f, 300.0f),
                            glm::vec3(0.0f, 0.0f, -1.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));

    this->clip = 0.0f;
    this->x = -1.0f;
    this->y = -1.0f;
    this->z = -1.0f;
}

void Model::update(){

}

void Model::normalize(glm::vec3 pos){
    // Model::model = glm::translate(Model::model, pos);
    Model::position = pos;
}

void Model::draw(Shader *myShader, Camera myCamera){
    Model::model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime()*glm::radians(30.f)*0, glm::vec3(0.0f, 1.0f, 0.0f));
    Model::model = Model::model * glm::translate(glm::mat4(1.0f), Model::position);

    // zoom in/out
    Model::projection = glm::ortho(myCamera.left, myCamera.right, myCamera.bottom, myCamera.top, myCamera.near, myCamera.far);

    // up down
    Model::view = glm::lookAt(myCamera.get_position(), myCamera.get_position() + myCamera.get_direction(), myCamera.get_up());
    // if material, put material here
    
    // glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(Model::view));
    // glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(Model::projection));
    glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(Model::model));
    
    glm::mat4 matrix = Model::projection * Model::view * Model::model;
    
    glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
    // glUniform3fv(glGetUniformLocation(myShader->ID, "light_pos"), 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, -300.0f)));
    glUniform3fv(glGetUniformLocation(myShader->ID, "light_pos"), 1, glm::value_ptr(-myCamera.get_position()));
    glUniform3fv(glGetUniformLocation(myShader->ID, "view_pos"), 1, glm::value_ptr(myCamera.get_position()));
    glUniform3fv(glGetUniformLocation(myShader->ID, "light_color"), 1, glm::value_ptr(glm::vec3(1.0f)));

    glUniform4fv(glGetUniformLocation(myShader->ID, "ClipPlane"), 1, glm::value_ptr(glm::vec4(this->x, this->y, this->z, this->clip)));
    VAOManagement::drawVAO(vao, myShader);
}

void Model::update_clip(float clip, float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
    this->clip = clip;
}