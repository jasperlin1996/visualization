#include "StreamLine.h"

using namespace std;

StreamLine::StreamLine()
    :super::Method()
{

}

StreamLine::~StreamLine() {

}

StreamLine::StreamLine(string filename)
    :StreamLine()
{
    this->load_data(filename);
}

void StreamLine::load_data(string filename) {
    int x, y;

    fstream f;
    f.open(filename, ios::in);
    f >> x >> y;

    cout << "vector size: " << x << ", " << y << endl;

    this->data.resize(x, vector<glm::vec2>(y, glm::vec2(0.0)));
    for (size_t i = 0; i < this->data.size(); i++) {
        for (size_t j = 0; j < this->data[i].size(); j++) {
            f >> this->data[i][j].x >> this->data[i][j].y;

            float length = glm::length(this->data[i][j]);
            if (i == 0 && j == 0) {
                this->min_vector_magnitude = length;
                this->max_vector_magnitude = length;
            }

            if (this->min_vector_magnitude > length) this->min_vector_magnitude = length;
            if (this->max_vector_magnitude < length) this->max_vector_magnitude = length;
        }
    }
    f.close();
    super::data_shape = glm::ivec3(x, y, 0);
    super::voxel_size = glm::vec3(1.0f, 1.0f, 1.0f);
}

void StreamLine::run(){
    this->generate_streamline();   
}

bool StreamLine::is_inside(glm::vec2 position){
    return (position.x >= 0.0 &&
            position.y >= 0.0 &&
            position.x < this->data.size() &&
            position.y < this->data[0].size());
}

// return the vector on the position
glm::vec2 StreamLine::vector_interpolation(glm::vec2 position){
    if (!is_inside(position)) return glm::vec2(0.0);
    
    size_t x = position.x, y = position.y;

    glm::vec2 lb = this->data[x][y];
    glm::vec2 lt = this->data[x][min(this->data[0].size() - 1, y + 1)];
    glm::vec2 rb = this->data[min(this->data.size() - 1, x + 1)][y];
    glm::vec2 rt = this->data[min(this->data.size() - 1, x + 1)][min(this->data.size() -1, y + 1)];

    glm::vec2 mu(position.x - x, position.y - y);

    glm::vec2 temp_1 = (1.0f - mu.x) * lb + mu.x * rb;
    glm::vec2 temp_2 = (1.0f - mu.x) * lt + mu.x * rt;

    glm::vec2 result = (1.0f - mu.y) * temp_1 + mu.y * temp_2;
    
    return result;
}

glm::vec2 StreamLine::rk2(glm::vec2 position, float h){
    glm::vec2 u_0 = vector_interpolation(position);
    glm::vec2 p_1 = position + h*u_0;

    glm::vec2 u_1 = vector_interpolation(p_1);

    glm::vec2 result = position + h*(u_0 + u_1) / 2.0f;

    return result;
}

void StreamLine::generate_streamline(){ // based on data_points, non-bidirectional
    const float threashold = 0.00001f, h = 0.1f;
    const int iterations_limit = 100;
    this->total_point_size = 0;

    for (size_t i = 0; i < this->data.size(); i++) {
        for (size_t j = 0; j < this->data[i].size(); j++) {
            glm::vec2 point(i, j);
            this->streamlines.push_back(vector<glm::vec2>(0));
            for (int k = 0; k < iterations_limit; k++) {
                glm::vec2 point_2 = rk2(point, h);
                this->streamlines.back().push_back(point_2);
                if (glm::distance(point, point_2) < threashold) {
                    break;
                }
                point = point_2;
            }
            this->total_point_size += this->streamlines.back().size();
        }
    }
}

// void StreamLine::generate_streamline(){

// }

vector<float> StreamLine::get_data(){
    vector<float> temp(this->total_point_size * (2 + 4 + 1));
    int vertex_counter = 0;
    for (size_t i = 0; i < this->streamlines.size(); i++) {
        float point_size = 3.0f;
        float point_delta = (point_size - 1.0f)/this->streamlines[i].size();
        for(size_t j = 0; j < this->streamlines[i].size(); j++, vertex_counter += 7, point_size -= point_delta) {
            float magnitude = glm::length(this->vector_interpolation(this->streamlines[i][j]));
            glm::vec3 color = this->transfer_function((magnitude - this->min_vector_magnitude)/(this->max_vector_magnitude - this->min_vector_magnitude));
            temp[vertex_counter + 0] = this->streamlines[i][j].x;
            temp[vertex_counter + 1] = this->streamlines[i][j].y;
            temp[vertex_counter + 2] = color.r;
            temp[vertex_counter + 3] = color.g;
            temp[vertex_counter + 4] = color.b;
            temp[vertex_counter + 5] = 1.0f;
            temp[vertex_counter + 6] = point_size;
        }
    }

    return temp;
}

glm::vec3 StreamLine::transfer_function(float magnitude){
    return glm::vec3(1.0f, min(1.0f, 1.0f - magnitude), min(1.0f, 1.0f - magnitude));
}