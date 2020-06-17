#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <regex>
#include <cctype>
#include <iomanip>

using namespace std;

enum TYPE{
    UNSIGNED_CHAR, CHAR, UNSIGNED_SHORT, SHORT, UNSIGNED_INT, INT, FLOAT
};

enum ENDIAN{
    LITTLE, BIG
};

class Volume{
public:
    Volume();
    Volume(string, string);
    ~Volume();
    vector<vector<vector<float> > > getData();
    float operator()(const int, const int, const int);
    float operator()(glm::ivec3);
    glm::ivec3 get_shape();
    void readInfo(string);
    void store_data(string);
    glm::vec3 get_gradient(glm::vec3);
    glm::vec3 get_voxel_size();
    vector<float> get_histogram();
    // vector<vector<float> > mk_table;
    vector<vector<float> > get_mk_table();
    float min, max; // not good
    float min_gradient, max_gradient;

    template <typename T> void readData(string rawFilename){
        fstream fs;
        fs.open(rawFilename, ios::in | ios::binary);
        int elements = this->resolution.x * this->resolution.y * this->resolution.z;
        char *buffer = new char[this->byteSize * elements];
        fs.read(buffer, this->byteSize * elements);
        fs.close();

        for(int x = 0; x < this->resolution.x; x++){
            for(int y = 0; y < this->resolution.y; y++){
                for(int z = 0; z < this->resolution.z; z++){
                    int index = x * this->resolution.y * this->resolution.z +
                                y * this->resolution.z +
                                z;
                    index *= this->byteSize;
                    if(this->endian == ENDIAN::BIG){
                        reverse(buffer + index, buffer + index + this->byteSize);
                    }
                    T typeBridge;
                    memcpy(&typeBridge, buffer + index, this->byteSize);
                    this->data[x][y][z] = (float)typeBridge;
                    if(x == 0 && y == 0 && z == 0) {
                        this->min = this->data[x][y][z];
                        this->max = this->data[x][y][z];
                    }
                    if(this->data[x][y][z] < this->min) this->min = this->data[x][y][z];
                    if(this->data[x][y][z] > this->max) this->max = this->data[x][y][z];
                }
            }
        }

        int x_edge = this->resolution.x - 1, y_edge = this->resolution.y - 1, z_edge = this->resolution.z - 1;

        for(int x = 0; x < this->resolution.x; x++){
            for(int y = 0; y < this->resolution.y; y++){
                for(int z = 0; z < this->resolution.z; z++){
                    glm::vec3 partial;
                    partial.x = (data[x + (x < x_edge)][y][z]-data[x - (x != 0)][y][z]);
                    partial.y = (data[x][y + (y < y_edge)][z]-data[x][y - (y != 0)][z]);
                    partial.z = (data[x][y][z + (z < z_edge)]-data[x][y][z - (z != 0)]);
                    
                    partial.x /= (float)(this->voxelSize.x * (2-(x==0 || x==x_edge)));
                    partial.y /= (float)(this->voxelSize.y * (2-(y==0 || y==y_edge)));
                    partial.z /= (float)(this->voxelSize.z * (2-(z==0 || z==z_edge)));

                    this->gradient[x][y][z] = partial;
                    float l2norm_tmp = glm::l2Norm(this->gradient[x][y][z]);
                    if(x == 0 && y == 0 && z == 0) {
                        this->min_gradient = l2norm_tmp;
                        this->max_gradient = l2norm_tmp;
                    }
                    if(l2norm_tmp < this->min_gradient) this->min_gradient = l2norm_tmp;
                    if(l2norm_tmp > this->max_gradient) this->max_gradient = l2norm_tmp;
                    
                }
            }
        }
        cout << "max_gradient: " << this->max_gradient << ", min_gradient: " << this->min_gradient << endl;
        // for(int x = 0; x < this->resolution.x; x++){
        //     for(int y = 0; y < this->resolution.y; y++){
        //         for(int z = 0; z < this->resolution.z; z++){
        //             // cout << data[x][y][z] << ' ';
        //         }
        //         // cout << endl;
        //     }
        //     // cout << endl;
        // }
#ifdef HISTOGRAM
        store_data("histogram.txt");
#endif
        delete [] buffer; 
    }
    
private:
    string infFilename, rawFilename;
    glm::ivec3 resolution;
    glm::vec3 voxelSize;
    TYPE sampleType;
    ENDIAN endian;
    int byteSize;

    vector<vector<vector<float> > > data;
    vector<vector<vector<glm::vec3> > > gradient;
};


