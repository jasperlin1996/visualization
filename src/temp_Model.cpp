#include "temp_Model.h"

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
            cout << "in iso surface" << '\n';

            // IsoSurface iso_surface(this->method->inf_filename, this->method->raw_filename, 80);

            IsoSurface *tmp = ((IsoSurface*)(this->method));

            // cout << "shape: " << iso_surface.get_shape().x << '\n';
            // glm::ivec3 tmp = ((IsoSurface *)this->method)->get_shape();
            // cout << tmp.x << ' ' << tmp.y << ' ' << tmp.z << endl;
            // cout << tmp->get_shape().x << '\n';
            // cout << tmp << '\n';
            
            vector<float> tmp_data = tmp->get_data();

            cout << "temp_data.size(): " << tmp_data.size() << '\n';
            // iso_surface.run();
            // cout << iso_surface.get_data().size() << '\n';

            // vector<float> triangle{
            //     0, 0, 0, 1, 1, 1,
            //     0, 0, 100, 1, 1, 1,
            //     0, 100, 0, 1, 1, 1
            // };
            // VAO temp_vao = VAOManagement::generateVAO(triangle);
            VAO temp_vao = VAOManagement::generateVAO(tmp_data);
            
            cout << temp_vao.vao << ' ' << temp_vao.count << endl;
            this->vao.push_back(temp_vao);
            cout << "vao size: " << this->vao.size() << endl;
            // (IsoSurface *)(this->mehtod)->get_data();
            break;
        }
        default:
            break;
    }
    // this->vao.push_back(VAOManagement::generateVAO(data));
}


METHODS Model::get_method_choice(){
    return this->method_choice;
}