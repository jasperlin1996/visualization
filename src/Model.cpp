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
            this->method = new VolumeRendering(this->inf_filename, this->raw_filename);
            break;
        case METHODS::STREAM_LINE:
            this->method = new StreamLine(this->inf_filename);
            break;
        default:
            break;
    }
    this->use_texture = false;
    this->textures.resize(0);
}

Model::Model(
    string filename,
    METHODS method_choice
) : inf_filename(filename),
    raw_filename(filename),
    method_choice(method_choice)
{
    switch (this->method_choice) {
        case METHODS::NONE:
            break;
        case METHODS::STREAM_LINE:
            this->method = new StreamLine(this->raw_filename);
            break;
        default:
            break;
    }
    this->use_texture = false;
    this->textures.resize(0);
}

Model::~Model(){
    // delete (this->method);
}

void Model::free(){
    delete this->method;
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
        case METHODS::STREAM_LINE:
            ((StreamLine *)(this->method))->run();
    }
}


void Model::draw(){
    switch (this->method_choice) {
        case METHODS::ISO_SURFACE:
            // VAOManagement::drawVAO(this->vao, GL_TRIANGLES, GL_FILL);
            VAOManagement::drawVAO(this->vao, this->use_texture, this->textures, GL_TRIANGLES, GL_FILL);
            break;
        case METHODS::VOLUME_RENDERING:
            VAOManagement::drawVAO(this->vao, this->use_texture, this->textures, GL_TRIANGLES, GL_FILL);
            break;
        case METHODS::STREAM_LINE:
            VAOManagement::drawVAO(this->vao, this->use_texture, this->textures, GL_POINTS, GL_FILL);
        default:
            break;
    }
}


void Model::set_vao_data(){
    switch (this->method_choice) {
        case (METHODS::ISO_SURFACE): {
            vector<int> vao_setting{3, 3};
            this->vao.push_back(VAOManagement::generateVAO(((IsoSurface *)(this->method))->get_data(), vao_setting));
            break;
        }
        case (METHODS::VOLUME_RENDERING): {
            vector<int> vao_setting{3, 3};
            this->vao.push_back(VAOManagement::generateVAO(((VolumeRendering *)(this->method))->get_data(), vao_setting));
            break;
        }
        case (METHODS::STREAM_LINE): {
            vector<int> vao_setting{2, 4, 1};
            this->vao.push_back(VAOManagement::generateVAO(((StreamLine *)(this->method))->get_data(), vao_setting));
            break;
        }
        default:
            break;
    }
}

void Model::update_vao_data(){
    switch (this->method_choice) {
        case (METHODS::ISO_SURFACE): {
            vector<int> vao_setting{3, 3};
            this->vao.clear();
            this->vao.push_back(VAOManagement::generateVAO(((IsoSurface *)(this->method))->get_data(), vao_setting));
            break;
        }
        case (METHODS::VOLUME_RENDERING): {
            vector<int> vao_setting{3, 3};
            this->vao.clear();
            this->vao.push_back(VAOManagement::generateVAO(((VolumeRendering *)(this->method))->get_data(), vao_setting));
            break;
        }
        default:
            break;
    }
}

METHODS Model::get_method_choice(){
    return this->method_choice;
}

void Model::enable_textures(int size){
    this->use_texture = true;
    this->textures.resize(size);

    for(int i = 0; i < size; i++){
        glGenTextures(1, &(this->textures[i].textures));
    }
}


// GLenum target = {GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D}
// int index = texture_id
void Model::init_texture(GLenum target, int index){
    if (this->use_texture == false) return;
    
    this->textures[index].target = target;

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(target, this->textures[index].textures);

    switch (target) {
        case GL_TEXTURE_3D:
            glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        case GL_TEXTURE_2D:
            glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        case GL_TEXTURE_1D:
            glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        default:
            break;
    }

    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Model::set_texture(int index){
    if (this->use_texture == false) return;
    // TODO: How to get texture data/shape from VolumeRendering without hardcore casting

    glActiveTexture(GL_TEXTURE0 + index);

    switch (this->method_choice) {
        case METHODS::NONE:
            break;
        case METHODS::ISO_SURFACE:
            break;
        case METHODS::VOLUME_RENDERING:
            ((VolumeRendering *)(this->method))->set_texture(index, this->textures[index].target);
        default:
            break;
    }

    glBindTexture(this->textures[index].target, 0);
}