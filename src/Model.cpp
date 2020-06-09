#include "Model.h"

Model::Model(){

}

Model::Model(
    string inf_filename,
    string raw_filename,
    METHODS method_choice
) : inf_filename(inf_filename),
    raw_filename(raw_filename),
    method_choice(method_choice)
{
    switch (this->method_choice) {
        case METHODS::NONE:
            break;
        case METHODS::ISO_SURFACE:
            // TODO: not sure if iso_value is needed
            this->method = new IsoSurface(this->inf_filename, this->raw_filename);
            break;
        case METHODS::VOLUME_RENDERING:
            break;
    }
}

Model::~Model(){
    // delete (this->method);
}

void Model::run(){
    switch(this->method_choice){
        case METHODS::NONE:
            break;
        case METHODS::ISO_SURFACE:
            ((IsoSurface *)(this->method))->run();
            break;
        case METHODS::VOLUME_RENDERING:
            // (VolumeRendering *)(this->method)->run();
            break;
    }
}


void Model::draw(/*Shader& myShader, Camera& myCamera, */Transformation& tf){
    // tf.set_uniform();
    VAOManagement::drawVAO(this->vao, GL_TRIANGLES, GL_FILL);
}


void Model::set_vao_data(){
    switch (this->method_choice) {
        case (METHODS::ISO_SURFACE): {
            this->vao.push_back(VAOManagement::generateVAO(((IsoSurface *)(this->method))->get_data()));
            break;
        }
        default:
            break;
    }
}


METHODS Model::get_method_choice(){
    return this->method_choice;
}
