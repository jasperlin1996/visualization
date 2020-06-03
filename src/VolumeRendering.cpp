#define _USE_MATH_DEFINES

#include "VolumeRendering.h"

using namespace std;

VolumeRendering::VolumeRendering(string inf_filename, string raw_filename)
    : Method::Method(inf_filename, raw_filename){     // ctor

    this->inf_filename = inf_filename;
    this->raw_filename = raw_filename;

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

    this->texture_vertex.resize(6);
}

void VolumeRendering::gen_texture_1d(){
    // TODO
}

void VolumeRendering::gen_texture_3d(){
    glm::ivec3 data_shape = Method::data_shape;
    glm::vec3 voxel_size = Method::voxel_size;

    float min = Method::volume.min, max = Method::volume.max;

    this->texture_3d.resize(data_shape.x * data_shape.y * data_shape.z * 4);
    for(int x = 0; x < data_shape.x - 1; x++){
        for(int y = 0; y < data_shape.y - 1; y++){
            for(int z = 0; z < data_shape.z - 1; z++){
                int index = (z * data_shape.z * data_shape.y + y * data_shape.x + x) * 4;
    
                // without normalization, should be done in shader
                glm::vec3 normal = Method::volume.get_gradient(glm::vec3(x, y, z));
                float value = (Method::volume(x, y, z) - min) / max;

                glm::vec4 voxel = glm::vec4(normal, value);
                for(int offset = 0; offset < 4; offset++){
                    this->texture_3d[index + offset] = voxel[offset];
                }
            }
        }
    }
}

void VolumeRendering::gen_slicing_clip(){
    glm::ivec3 data_shape = Method::data_shape;
    glm::vec3 plane_position = glm::vec3(data_shape) * Method::voxel_size;

    double step = 0.5; // slicing step

    for(size_t i = 0; i < this->texture_vertex.size(); i++){
        int index = i / 2;
        double start = (i % 2 ? 0.0 : data_shape[index]);
        double delta = (i & 2 ? step : -step);

        for(int j = 0; j < (data_shape[index] / step) + 1; j++, start += delta){
            for(size_t k = 0; k < this->axis_template[index].size(); k += 3){
                glm::vec3 texture_position = glm::vec3(
                    this->axis_template[index][k + 0],
                    this->axis_template[index][k + 1],
                    this->axis_template[index][k + 2]
                );

                glm::vec3 plane = texture_position * plane_position;
                plane[index] = start;
                texture_position[index] = start / data_shape[index];

                // push (plane position, texture position) to vertex
                for(int temp = 0; temp < 3; temp++){
                    this->texture_vertex[index].push_back(plane[temp]);
                }
                for(int temp = 0; temp < 3; temp++){
                    this->texture_vertex[index].push_back(texture_position[temp]);
                }
            }
        }
    }
}

double gaussian(double mu, double sigma, double value){
    double coefficient = sigma * sqrt(2 * M_PI);
    double temp = exp(-1 * (value - mu) * (value - mu) / (2 * sigma * sigma));

    return temp / coefficient;
}