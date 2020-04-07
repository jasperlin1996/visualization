#pragma once

#include "glm/glm.hpp"
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
                    
                    // cout << partial.x << ' ';
                }
            }
        }
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


