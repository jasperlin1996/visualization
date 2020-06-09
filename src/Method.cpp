#include "Method.h"

using namespace std;

Method::Method(){

}

Method::Method(string inf_filename, string raw_filename){
    this->inf_filename = inf_filename;
    this->raw_filename = raw_filename;

    this->volume = Volume(this->inf_filename, this->raw_filename);

    this->data_shape = volume.get_shape();
    this->voxel_size = volume.get_voxel_size();
    for(int i = 0; i < 3; i++){
        cout << data_shape[i] << (i==2 ? '\n' : ' ');
    }
}

Method::~Method(){

}