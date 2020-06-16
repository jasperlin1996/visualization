#include "IsoSurface.h"

#define ZERO 0.00001
// #define OUTPUT
using namespace std;

IsoSurface::IsoSurface(string inf_filename, string raw_filename)
    : super::Method(inf_filename, raw_filename){
    this->data_shape = super::data_shape;
    this->voxel_size = super::voxel_size;
}

IsoSurface::IsoSurface(string inf_filename, string raw_filename, int iso_value)
    : super::Method(inf_filename, raw_filename){
    this->data_shape = super::data_shape;
    this->voxel_size = super::voxel_size;
    this->set_iso_value(iso_value);
}

IsoSurface::~IsoSurface(){

}

void IsoSurface::set_iso_value(int iso_value){
    this->iso_value = iso_value;
}

glm::vec3 IsoSurface::vertex_interpolation(glm::vec3 p1, glm::vec3 p2, float v1, float v2){
    double mu;
    glm::vec3 intp_point; // interpolate point
    if(fabs(this->iso_value - v1) < ZERO) return p1;
    if(fabs(this->iso_value - v2) < ZERO) return p2;
    if(fabs(v1 - v2) < ZERO) return p1;
    mu = (this->iso_value - v1) / (v2 - v1);
    intp_point.x = p1.x + mu * (p2.x - p1.x);
    intp_point.y = p1.y + mu * (p2.y - p1.y);
    intp_point.z = p1.z + mu * (p2.z - p1.z);
    
    return intp_point;
}

pair<glm::vec3, glm::vec3> IsoSurface::gradient_interpolation(glm::vec3 p1, glm::vec3 p2, float v1, float v2, glm::vec3 g1, glm::vec3 g2){
    float mu;
    glm::vec3 intp_point, intp_gradient; // interpolate point
    p1 *= this->voxel_size;
    p2 *= this->voxel_size;
    g1 *= this->voxel_size;
    g2 *= this->voxel_size;

    if(fabs(this->iso_value - v1) < ZERO) return make_pair(p1, g1);
    if(fabs(this->iso_value - v2) < ZERO) return make_pair(p2, g2);
    if(fabs(v1 - v2) < ZERO) return make_pair(p1, g1);
    mu = (this->iso_value - v1) / (v2 - v1);

    intp_point = p1 + mu * (p2 - p1);
    intp_gradient = g1 + mu *(g2 - g1);
    
    return make_pair(intp_point, intp_gradient);
}

void IsoSurface::surface_intersection(pair<glm::vec3, glm::vec3> vertex_list[], glm::vec3 grid[], float grid_value[], glm::vec3 grid_gradient[], int edges){
    // glm::vec3 vertex_list[12];
    // pair<glm::vec3, glm::vec3> vertex_list[12];
    int target_bit = 1;
    int p1_table[] = {0,1,2,3,4,5,6,7,0,1,2,3};
    int p2_table[] = {1,2,3,0,5,6,7,4,4,5,6,7};
    for(int index = 0; index < 12; index++, target_bit <<= 1){
        if(edges & target_bit){
            // vertex_list[index] = vertex_interpolation(grid[p1_table[index]], grid[p2_table[index]], grid_value[p1_table[index]], grid_value[p2_table[index]]);
            vertex_list[index] = gradient_interpolation(grid[p1_table[index]],
                            grid[p2_table[index]],
                            grid_value[p1_table[index]],
                            grid_value[p2_table[index]],
                            grid_gradient[p1_table[index]],
                            grid_gradient[p2_table[index]]);
        }
    }
    // return vertex_list;
}
void IsoSurface::run(){
    cout << "Run Iso Surface\n";
    glm::vec3 grid[8];
    glm::vec3 grid_gradient[8];
    float grid_value[8];

    // clear vector data
    this->data.clear();
    // this->data.shrink_to_fit(); // real time needs speed, not space

    for(int x = 0; x < this->data_shape.x - 1; x++){
        for(int y = 1; y < this->data_shape.y; y++){
            for(int z = 0; z < this->data_shape.z - 1; z++){
                int cubeindex = 0, setter = 1;
                grid[0] = glm::vec3(x,y,z);
                grid[1] = glm::vec3(x,y,z+1);
                grid[2] = glm::vec3(x,y-1,z+1);
                grid[3] = glm::vec3(x,y-1,z);
                grid[4] = glm::vec3(x+1,y,z);
                grid[5] = glm::vec3(x+1,y,z+1);
                grid[6] = glm::vec3(x+1,y-1,z+1);
                grid[7] = glm::vec3(x+1,y-1,z);
                for(int index = 0; index < 8; index++, setter <<= 1){
                    grid_value[index] = super::volume(grid[index]);
                    grid_gradient[index] = super::volume.get_gradient(grid[index]); //
                    if(grid_value[index] < this->iso_value) cubeindex |= setter;
                }

                if (cubeindex == 0 || cubeindex == 0xff) continue;
                // search from edge table
                int edges = edgeTable[cubeindex];

                pair<glm::vec3, glm::vec3> vertex_list[12];
                surface_intersection(vertex_list, grid, grid_value, grid_gradient, edges);
                int vertex_count = 0, triangle_count = 0;
#ifdef OUTPUT
                cout << "cubeindex: " << hex << cubeindex << endl;
                cout << "edgetable: " << hex << edgeTable[cubeindex] << endl;
                cout << "tritable: ";
                for(unsigned int i = 0; i < 16; i++){
                    if(triTable[cubeindex][i] != -1) {
                        vertex_count += 1;
                        cout << dec << i << ": "<< triTable[cubeindex][i] << ( i == 15 ? '\n' : ' ');
                    }
                    else {
                        cout << endl;
                        break;
                    }
                }
#endif
                triangle_count = vertex_count/3;
                for(int i = 0; triTable[cubeindex][i] != -1; i += 3){
                    // cout << vertex_list[triTable[cubeindex][i]].first[0] << endl;
                    this->data.push_back(vertex_list[triTable[cubeindex][i]].first[0]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i]].first[1]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i]].first[2]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i]].second[0]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i]].second[1]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i]].second[2]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+1]].first[0]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+1]].first[1]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+1]].first[2]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+1]].second[0]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+1]].second[1]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+1]].second[2]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+2]].first[0]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+2]].first[1]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+2]].first[2]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+2]].second[0]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+2]].second[1]);
                    this->data.push_back(vertex_list[triTable[cubeindex][i+2]].second[2]);
                }
            }
        }
    }

    cout << "triangles size: " << this->data.size() << endl;
}

vector<float> IsoSurface::get_data(){
    cout << this->data.size() << endl;
    return this->data;
}

glm::ivec3 IsoSurface::get_shape(){
    return this->data_shape;
}

glm::vec3 IsoSurface::get_voxel_size(){
    return this->voxel_size;
}
