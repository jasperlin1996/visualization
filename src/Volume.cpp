#include "Volume.h"

using namespace std;

Volume::Volume(){
    this->infFilename = "";
    this->rawFilename = "";
    this->sampleType  = TYPE::UNSIGNED_CHAR;
    this->endian      = ENDIAN::LITTLE;
    this->byteSize    = 1;
    this->resolution  = glm::ivec3(0, 0, 0);
    this->voxelSize   = glm::vec3(1.0f, 1.0f, 1.0f);

    this->min = 0.0f;
    this->max = 0.0f;
}
Volume::Volume(string infFilename, string rawFilename){
    this->infFilename = infFilename;
    this->rawFilename = rawFilename;
    this->sampleType  = TYPE::UNSIGNED_CHAR;
    this->endian      = ENDIAN::LITTLE;
    this->byteSize    = 1;
    this->resolution  = glm::ivec3(0, 0, 0);
    this->voxelSize   = glm::vec3(1.0f, 1.0f, 1.0f);

    this->min = 0.0f;
    this->max = 0.0f;
    this->min_gradient = 0.0f;
    this->max_gradient = 0.0f;

    readInfo(this->infFilename);
    if(sampleType == TYPE::UNSIGNED_CHAR){
        readData<unsigned char>(this->rawFilename);
    }
    else if(sampleType == TYPE::CHAR){
        readData<char>(this->rawFilename);
    }
    else if(sampleType == TYPE::UNSIGNED_SHORT){
        readData<unsigned short>(this->rawFilename);
    }
    else if(sampleType == TYPE::SHORT){
        readData<short>(this->rawFilename);
    }
    else if(sampleType == TYPE::UNSIGNED_INT){
        readData<unsigned int>(this->rawFilename);
    }
    if(sampleType == TYPE::INT){
        readData<int>(this->rawFilename);
    }
    if(sampleType == TYPE::FLOAT){
        readData<float>(this->rawFilename);
    }
}


Volume::~Volume(){

}

void Volume::readInfo(string infFilename){
    fstream fs;
    string line;
    fs.open(infFilename, fstream::in);

    regex resolution("(resolution)\\s(\\d+[:|x]?)+");
    regex voxelsize("(voxelsize|ratio)\\s(\\d*\\.?\\d*:?)+");
    regex sampletype("sampletype\\s[a-z]*(\\s[a-z]+)?");
    regex valuetype("valuetype\\s(ub|b|us|s|ui|i|f)");
    regex endian("(endian|indiantype)\\s(little|big|l|b)");

    smatch matched;

    char _[20], rhs[20];
    while(getline(fs, line)){
        // alphabet to lower case, no space and '-', '=' to space.
        string normalized = "";
        for(unsigned int i = 0; i < line.length(); i++){
            if(line[i] != ' ' && line[i] != '-'){
                if(line[i] == '=') normalized += ' ';
                else normalized += tolower(line[i]);
            }
        }
        
        line = normalized;

        if(regex_search(line, matched, resolution)){
            string pattern = "resolution %dx%dx%d";
            if(line.find(":") != string::npos) pattern[13] = pattern[16] = ':';
            sscanf(line.c_str(), pattern.c_str(), &(this->resolution.z), &(this->resolution.y), &(this->resolution.x));

            this->data.resize(this->resolution[0], vector<vector<float> >(this->resolution[1], vector<float>(this->resolution[2], 1)));
            this->gradient.resize(this->resolution[0], vector<vector<glm::vec3> >(this->resolution[1], vector<glm::vec3>(this->resolution[2])));

            cout << "resolution: ";
            for(int i = 0; i < this->resolution.length(); i++)
                cout << this->resolution[i] << ' ';
            cout << endl;
        }
        if(regex_search(line, matched, voxelsize)){
            string pattern = " %fx%fx%f";
            if(line.find(":") != string::npos) pattern[3] = pattern[6] = ':';
            if(line.find("voxelsize") != string::npos) pattern = "voxelsize" + pattern;
            else pattern = "ratio" + pattern;
            sscanf(line.c_str(), pattern.c_str(), &(this->voxelSize.z), &(this->voxelSize.y), &(this->voxelSize.x));

            cout << "voxel size: ";
            for(int i = 0; i < this->voxelSize.length(); i++)
                cout << this->voxelSize[i] << ' ';
            cout << endl;
        }
        if(regex_search(line, matched, sampletype) || regex_search(line, matched, valuetype)){
            if(line.find("=") != string::npos) line[line.find("=")] = ' ';

            sscanf(line.c_str(), "%s %s", _, rhs);

            string tmp = rhs;
            if(tmp == "unsignedchar" || tmp == "ub"){
                this->sampleType = TYPE::UNSIGNED_CHAR;
                this->byteSize = 1;
            }
            if(tmp == "char" || tmp == "b"){
                this->sampleType = TYPE::CHAR;
                this->byteSize = 1;
            }
            if(tmp == "unsignedshort" || tmp == "us"){
                this->sampleType = TYPE::UNSIGNED_SHORT;
                this->byteSize = 2;
            }
            if(tmp == "short" || tmp == "s"){
                this->sampleType = TYPE::SHORT;
                this->byteSize = 2;
            }
            if(tmp == "unsignedint" || tmp == "ui"){
                this->sampleType = TYPE::UNSIGNED_INT;
                this->byteSize = 4;
            }
            if(tmp == "int" || tmp == "i"){
                this->sampleType = TYPE::INT;
                this->byteSize = 4;
            }
            if(tmp == "float" || tmp == "f"){
                this->sampleType = TYPE::FLOAT;
                this->byteSize = 4;
            }
            cout << "sampleType: " << this->sampleType << endl;
        }
        if(regex_search(line, matched, endian)){
            sscanf(matched.str().c_str(), "%s %s", _, rhs);
            string tmp = rhs;
            if(tmp == "little" || tmp == "l") {
                this->endian = ENDIAN::LITTLE;
            }
            else{
                this->endian = ENDIAN::BIG;
            }
            cout << "endian: " << this->endian << endl;
        }
    }
    fs.close();
}

vector<vector<vector<float> > > Volume::getData(){
    return this->data;
}

float Volume::operator()(const int x, const int y, const int z){
    return this->data[x][y][z];
}

float Volume::operator()(glm::ivec3 point){
    return this->data[point.x][point.y][point.z];
}

glm::ivec3 Volume::get_shape(){
    return this->resolution;
}

void Volume::store_data(string filename){
    fstream output;
    output.open(filename, ios::out);

    for(size_t i = 0; i < this->data.size(); i++){
        for(size_t j = 0; j < this->data[0].size(); j++){
            for(size_t k = 0; k < this->data[0][0].size(); k++){
                output << this->data[i][j][k] << ' ';
            }
        }
    }
    output.close();
    cout << "Raw file stored to " << filename << endl;
}

glm::vec3 Volume::get_gradient(glm::vec3 index){
    return this->gradient[index.x][index.y][index.z];
}

glm::vec3 Volume::get_voxel_size(){
    return this->voxelSize;
}

vector<float> Volume::get_histogram(){
    vector<float> histogram(256, 0.0f);

    float resizer = 255.0;
    if (this->max - this->min >= 1e-6) resizer /= this->max - this->min;

    for(size_t i = 0; i < this->data.size(); i++){
        for(size_t j = 0; j < this->data[0].size(); j++){
            for(size_t k = 0; k < this->data[0][0].size(); k++){
                histogram[(int)(this->data[i][j][k] - this->min) * resizer]++;
            }
        }
    }

    return histogram;
}

vector<vector<float> > Volume::get_mk_table(){
    vector<vector<float> > mk_table(256, vector<float>(160, 0.0f));
    const float gMax = 256.0f; // 20 * log_2(256)
    // float gradient_range = this->max_gradient - this->min_gradient;
    float value_range = this->max - this->min;
    int max_mk_table = 0;
    int _m = 0, _k = 0;

    for(size_t i = 0; i < this->data.size(); i++){
        for(size_t j = 0; j < this->data[0].size(); j++){
            for(size_t k = 0; k < this->data[0][0].size(); k++){
                _m = ((this->data[i][j][k]-this->min)/value_range)*255;
                float l2norm = glm::l2Norm(this->gradient[i][j][k]);
                if (l2norm < 1.0f) l2norm = 1.0f;
                if (l2norm > gMax) l2norm = gMax;
                l2norm = 20 * log2(l2norm);
                // _k = ((glm::l2Norm(this->gradient[i][j][k])-this->min_gradient)/gradient_range)*159;
                _k = l2norm;
                if (_m > 255) _m = 255;
                if (_k > 159) _k = 159;
                mk_table[_m][_k] += 1.0f;
                if(mk_table[_m][_k] > max_mk_table) max_mk_table = mk_table[_m][_k];
            }
        }
    }

    for(size_t m = 0; m < mk_table.size(); m++){
        for(size_t k = 0; k < mk_table[0].size(); k++){
            mk_table[m][k] = 20 * log2(mk_table[m][k]);
        }
    }
    return mk_table;
}