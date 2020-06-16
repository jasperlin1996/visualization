#define _USE_MATH_DEFINES

#include "VolumeRendering.h"

using namespace std;

VolumeRendering::VolumeRendering(string inf_filename, string raw_filename)
    : super::Method(inf_filename, raw_filename){     // ctor

    this->inf_filename = inf_filename;
    this->raw_filename = raw_filename;

    this->axis_index = -1;

    this->axis_template = {
        {
            -1, 0, 0,
            -1, 1, 0,
            -1, 1, 1,
            -1, 0, 0,
            -1, 1, 1,
            -1, 0, 1
        },
        {
            0, -1, 0,
            1, -1, 0,
            1, -1, 1,
            0, -1, 0,
            1, -1, 1,
            0, -1, 1
        },
        {
            0, 0, -1,
            1, 0, -1,
            1, 1, -1,
            0, 0, -1,
            1, 1, -1,
            0, 1, -1
        }
    };

    this->gen_texture_1d();
    this->gen_texture_3d();

    this->texture_vertex.resize(6);
    this->gen_slicing_clip();
}

void VolumeRendering::gen_texture_1d(){
    this->texture_1d.resize(256 * 4, 0);
    for(size_t i = 70*4; i < 90*4; i+=4){
        this->texture_1d[i + 0] = 0;
        this->texture_1d[i + 1] = 1;
        this->texture_1d[i + 2] = 0;
        this->texture_1d[i + 3] = 0.03;
    }
    
    for (size_t i = 193*4; i < 199 * 4; i += 4) {
        this->texture_1d[i + 0] = 1;
        this->texture_1d[i + 1] = 0;
        this->texture_1d[i + 2] = 0;
        this->texture_1d[i + 3] = 0.1;
    }

    for (size_t i = 200 * 4; i < 256 * 4; i += 4) {
        this->texture_1d[i + 0] = 0;
        this->texture_1d[i + 1] = 0;
        this->texture_1d[i + 2] = 1;
        this->texture_1d[i + 3] = 0.007;
    }

    // for (size_t i = 0; i < this->texture_1d.size(); i += 4) {
    //     cout << i / 4 << ": ";
    //     for (int j = 0; j < 4; j++) {
    //         cout << this->texture_1d[i + j] << ' ';
    //     }
    //     cout << '\n';
    // }

}

void VolumeRendering::gen_texture_3d(){
    glm::ivec3 data_shape = super::data_shape;

    float min = super::Method::volume.min, max = super::Method::volume.max;

    this->texture_3d.resize(data_shape.x * data_shape.y * data_shape.z * 4);
    for(int x = 0; x < data_shape.x - 1; x++){
        for(int y = 0; y < data_shape.y - 1; y++){
            for(int z = 0; z < data_shape.z - 1; z++){
                int index = (z * data_shape.x * data_shape.y + y * data_shape.x + x) * 4;
    
                // without normalization, should be done in shader
                glm::vec3 normal = super::Method::volume.get_gradient(glm::vec3(x, y, z));
                float value = (super::Method::volume(x, y, z) - min) / max;
                glm::vec4 voxel = glm::vec4(normal, value);

                for(int offset = 0; offset < 4; offset++){
                    this->texture_3d[index + offset] = voxel[offset];
                }
            }
        }
    }
}

bool VolumeRendering::axis_aligned(glm::vec3 direction){
    int max_index = this->compare(direction);
    int temp = max_index * 2 + (direction[max_index] < 0.0f);

    if (this->axis_index == -1 || this->axis_index != temp) {
        this->axis_index = temp;
        return true; // if changing
    }
    return false;
}

int VolumeRendering::compare(glm::vec3 direction){
    glm::vec3 temp(fabs(direction.x), fabs(direction.y), fabs(direction.z));

    if (temp[0] >= temp[1] && temp[0] >= temp[2]) return 0;
    if (temp[1] > temp[0] && temp[1] >= temp[2]) return 1;
    if (temp[2] > temp[0] && temp[2] > temp[1]) return 2;

    return -1;
}

// max      +/-     i       index
// |x|      +       0       0
// |x|      -       1       0
// |y|      +       2       1
// |y|      -       3       1
// |z|      +       4       2
// |z|      -       5       2

void VolumeRendering::gen_slicing_clip(){
    glm::ivec3 data_shape = Method::data_shape;
    glm::vec3 plane_position = glm::vec3(data_shape) * Method::voxel_size;
    cout << "voxel_size: " << voxel_size.x << ' ' << voxel_size.y << ' ' << voxel_size.z << endl;
    double step = 0.1; // slicing step

    for(size_t i = 0; i < this->texture_vertex.size(); i++){
        int index = i / 2;
        double start = (i % 2 ? 0.0 : data_shape[index]);
        double delta = (i % 2 ? step : -step);

        for(int j = 0; j < (data_shape[index] / step) + 1; j++, start += delta){
            for(size_t k = 0; k < this->axis_template[index].size(); k += 3){
                glm::vec3 texture_position = glm::vec3(
                    this->axis_template[index][k + 0],
                    this->axis_template[index][k + 1],
                    this->axis_template[index][k + 2]
                );

                glm::vec3 plane = texture_position * plane_position;
                plane[index] = start * Method::voxel_size[index];
                texture_position[index] = start / data_shape[index];

                // push (plane position, texture position) to vertex
                for(int temp = 0; temp < 3; temp++){
                    this->texture_vertex[i].push_back(plane[temp]);
                }
                for(int temp = 0; temp < 3; temp++){
                    this->texture_vertex[i].push_back(texture_position[temp]);
                }
            }
        }
    }
}

vector<float>& VolumeRendering::get_data(){
    cout << "VolumeRendering::get_data() this->axis_index: " << this->axis_index << endl;
    return this->texture_vertex[this->axis_index];
}

double gaussian(double mu, double sigma, double value){
    double coefficient = sigma * sqrt(2 * M_PI);
    double temp = exp(-1 * (value - mu) * (value - mu) / (2 * sigma * sigma));

    return temp / coefficient;
}

vector<float>& VolumeRendering::get_texture_1d(){
    return this->texture_1d;
}

vector<float>& VolumeRendering::get_textrue_3d(){
    return this->texture_3d;
}

void VolumeRendering::set_texture(int index, GLenum target){
    // glActivateTexture(GL_TEXTURE0 + index); @ Model

    switch (target) {
        case GL_TEXTURE_1D:
            glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, this->texture_1d.size()/4, 0, GL_RGBA, GL_FLOAT, this->texture_1d.data());
            glGenerateMipmap(GL_TEXTURE_1D);
            break;
        case GL_TEXTURE_2D:
            // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, /*,shapes*/, 0, GL_RGBA, GL_FLOAT, /*,data*/);
            // glGenerateMipmap(GL_TEXTURE_2D);
            break;
        case GL_TEXTURE_3D: {
            glm::ivec3 data_shape = super::data_shape;
            glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, data_shape.x, data_shape.y, data_shape.z, 0, GL_RGBA, GL_FLOAT, this->texture_3d.data());
            glGenerateMipmap(GL_TEXTURE_3D);
            break;
        }
        default:
            break;
    }

    // glBindTexture(this->textures[index].target, 0); @ Model
}

