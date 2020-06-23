#include "SammonMapping.h"

using namespace std;

SammonMapping::SammonMapping() {
    this->data = vector<vector<float>>{
        { 5.1, 3.5, 1.4, 0.2 },
        { 4.9, 3.0, 1.4, 0.2 },
        { 4.7, 3.2, 1.3, 0.2 },
        { 4.6, 3.1, 1.5, 0.2 },
        { 5.0, 3.6, 1.4, 0.2 },
        { 5.4, 3.9, 1.7, 0.4 },
        { 4.6, 3.4, 1.4, 0.3 },
        { 5.0, 3.4, 1.5, 0.2 },
        { 4.4, 2.9, 1.4, 0.2 },
        { 4.9, 3.1, 1.5, 0.1 },
        { 5.4, 3.7, 1.5, 0.2 },
        { 4.8, 3.4, 1.6, 0.2 },
        { 4.8, 3.0, 1.4, 0.1 },
        { 4.3, 3.0, 1.1, 0.1 },
        { 5.8, 4.0, 1.2, 0.2 },
        { 5.7, 4.4, 1.5, 0.4 },
        { 5.4, 3.9, 1.3, 0.4 },
        { 5.1, 3.5, 1.4, 0.3 },
        { 5.7, 3.8, 1.7, 0.3 },
        { 5.1, 3.8, 1.5, 0.3 },
        { 5.4, 3.4, 1.7, 0.2 },
        { 5.1, 3.7, 1.5, 0.4 },
        { 4.6, 3.6, 1.0, 0.2 },
        { 5.1, 3.3, 1.7, 0.5 },
        { 4.8, 3.4, 1.9, 0.2 },
        { 5.0, 3.0, 1.6, 0.2 },
        { 5.0, 3.4, 1.6, 0.4 },
        { 5.2, 3.5, 1.5, 0.2 },
        { 5.2, 3.4, 1.4, 0.2 },
        { 4.7, 3.2, 1.6, 0.2 },
        { 4.8, 3.1, 1.6, 0.2 },
        { 5.4, 3.4, 1.5, 0.4 },
        { 5.2, 4.1, 1.5, 0.1 },
        { 5.5, 4.2, 1.4, 0.2 },
        { 4.9, 3.1, 1.5, 0.1 },
        { 5.0, 3.2, 1.2, 0.2 },
        { 5.5, 3.5, 1.3, 0.2 },
        { 4.9, 3.1, 1.5, 0.1 },
        { 4.4, 3.0, 1.3, 0.2 },
        { 5.1, 3.4, 1.5, 0.2 },
        { 5.0, 3.5, 1.3, 0.3 },
        { 4.5, 2.3, 1.3, 0.3 },
        { 4.4, 3.2, 1.3, 0.2 },
        { 5.0, 3.5, 1.6, 0.6 },
        { 5.1, 3.8, 1.9, 0.4 },
        { 4.8, 3.0, 1.4, 0.3 },
        { 5.1, 3.8, 1.6, 0.2 },
        { 4.6, 3.2, 1.4, 0.2 },
        { 5.3, 3.7, 1.5, 0.2 },
        { 5.0, 3.3, 1.4, 0.2 },
        { 7.0, 3.2, 4.7, 1.4 },
        { 6.4, 3.2, 4.5, 1.5 },
        { 6.9, 3.1, 4.9, 1.5 },
        { 5.5, 2.3, 4.0, 1.3 },
        { 6.5, 2.8, 4.6, 1.5 },
        { 5.7, 2.8, 4.5, 1.3 },
        { 6.3, 3.3, 4.7, 1.6 },
        { 4.9, 2.4, 3.3, 1.0 },
        { 6.6, 2.9, 4.6, 1.3 },
        { 5.2, 2.7, 3.9, 1.4 },
        { 5.0, 2.0, 3.5, 1.0 },
        { 5.9, 3.0, 4.2, 1.5 },
        { 6.0, 2.2, 4.0, 1.0 },
        { 6.1, 2.9, 4.7, 1.4 },
        { 5.6, 2.9, 3.6, 1.3 },
        { 6.7, 3.1, 4.4, 1.4 },
        { 5.6, 3.0, 4.5, 1.5 },
        { 5.8, 2.7, 4.1, 1.0 },
        { 6.2, 2.2, 4.5, 1.5 },
        { 5.6, 2.5, 3.9, 1.1 },
        { 5.9, 3.2, 4.8, 1.8 },
        { 6.1, 2.8, 4.0, 1.3 },
        { 6.3, 2.5, 4.9, 1.5 },
        { 6.1, 2.8, 4.7, 1.2 },
        { 6.4, 2.9, 4.3, 1.3 },
        { 6.6, 3.0, 4.4, 1.4 },
        { 6.8, 2.8, 4.8, 1.4 },
        { 6.7, 3.0, 5.0, 1.7 },
        { 6.0, 2.9, 4.5, 1.5 },
        { 5.7, 2.6, 3.5, 1.0 },
        { 5.5, 2.4, 3.8, 1.1 },
        { 5.5, 2.4, 3.7, 1.0 },
        { 5.8, 2.7, 3.9, 1.2 },
        { 6.0, 2.7, 5.1, 1.6 },
        { 5.4, 3.0, 4.5, 1.5 },
        { 6.0, 3.4, 4.5, 1.6 },
        { 6.7, 3.1, 4.7, 1.5 },
        { 6.3, 2.3, 4.4, 1.3 },
        { 5.6, 3.0, 4.1, 1.3 },
        { 5.5, 2.5, 4.0, 1.3 },
        { 5.5, 2.6, 4.4, 1.2 },
        { 6.1, 3.0, 4.6, 1.4 },
        { 5.8, 2.6, 4.0, 1.2 },
        { 5.0, 2.3, 3.3, 1.0 },
        { 5.6, 2.7, 4.2, 1.3 },
        { 5.7, 3.0, 4.2, 1.2 },
        { 5.7, 2.9, 4.2, 1.3 },
        { 6.2, 2.9, 4.3, 1.3 },
        { 5.1, 2.5, 3.0, 1.1 },
        { 5.7, 2.8, 4.1, 1.3 },
        { 6.3, 3.3, 6.0, 2.5 },
        { 5.8, 2.7, 5.1, 1.9 },
        { 7.1, 3.0, 5.9, 2.1 },
        { 6.3, 2.9, 5.6, 1.8 },
        { 6.5, 3.0, 5.8, 2.2 },
        { 7.6, 3.0, 6.6, 2.1 },
        { 4.9, 2.5, 4.5, 1.7 },
        { 7.3, 2.9, 6.3, 1.8 },
        { 6.7, 2.5, 5.8, 1.8 },
        { 7.2, 3.6, 6.1, 2.5 },
        { 6.5, 3.2, 5.1, 2.0 },
        { 6.4, 2.7, 5.3, 1.9 },
        { 6.8, 3.0, 5.5, 2.1 },
        { 5.7, 2.5, 5.0, 2.0 },
        { 5.8, 2.8, 5.1, 2.4 },
        { 6.4, 3.2, 5.3, 2.3 },
        { 6.5, 3.0, 5.5, 1.8 },
        { 7.7, 3.8, 6.7, 2.2 },
        { 7.7, 2.6, 6.9, 2.3 },
        { 6.0, 2.2, 5.0, 1.5 },
        { 6.9, 3.2, 5.7, 2.3 },
        { 5.6, 2.8, 4.9, 2.0 },
        { 7.7, 2.8, 6.7, 2.0 },
        { 6.3, 2.7, 4.9, 1.8 },
        { 6.7, 3.3, 5.7, 2.1 },
        { 7.2, 3.2, 6.0, 1.8 },
        { 6.2, 2.8, 4.8, 1.8 },
        { 6.1, 3.0, 4.9, 1.8 },
        { 6.4, 2.8, 5.6, 2.1 },
        { 7.2, 3.0, 5.8, 1.6 },
        { 7.4, 2.8, 6.1, 1.9 },
        { 7.9, 3.8, 6.4, 2.0 },
        { 6.4, 2.8, 5.6, 2.2 },
        { 6.3, 2.8, 5.1, 1.5 },
        { 6.1, 2.6, 5.6, 1.4 },
        { 7.7, 3.0, 6.1, 2.3 },
        { 6.3, 3.4, 5.6, 2.4 },
        { 6.4, 3.1, 5.5, 1.8 },
        { 6.0, 3.0, 4.8, 1.8 },
        { 6.9, 3.1, 5.4, 2.1 },
        { 6.7, 3.1, 5.6, 2.4 },
        { 6.9, 3.1, 5.1, 2.3 },
        { 5.8, 2.7, 5.1, 1.9 },
        { 6.8, 3.2, 5.9, 2.3 },
        { 6.7, 3.3, 5.7, 2.5 },
        { 6.7, 3.0, 5.2, 2.3 },
        { 6.3, 2.5, 5.0, 1.9 },
        { 6.5, 3.0, 5.2, 2.0 },
        { 6.2, 3.4, 5.4, 2.3 },
        { 5.9, 3.0, 5.1, 1.8 }
    };

    this->label = vector<int>{
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    };

}

SammonMapping::~SammonMapping() {

}

SammonMapping::SammonMapping(string inf_filename, string raw_filename)
    : SammonMapping::SammonMapping()
{
    // TODO
}

float SammonMapping::distance(vector<float> a, vector<float> b) {
    float result = 0.0f;
    if (a.size() == b.size()) {
        for (size_t i = 0; i < a.size(); i++) {
            result += (b[i] - a[i]) * (b[i] - a[i]);
        }
        result = sqrt(result);
        return result;
    }
    else return 0.0f;
}

void SammonMapping::run() {
    int iterations_limit = 10000;
    const float epsilon = 1e-6;

    random_device rd;
    mt19937 gen = mt19937(rd());
    uniform_real_distribution<float> dis(-1, 1);

    auto randfun = bind(dis, gen);

    // normalize features first
    this->feature_normalize();

    // Compute d'ij
    this->original_distances.resize(this->data.size(), vector<float>(this->data.size(), 0.0f));
    for (size_t i = 0; i < this->original_distances.size(); i++) {
        for (size_t j = 0; j < this->original_distances[0].size(); j++) {
            this->original_distances[i][j] = this->distance(this->data[i], this->data[j]);
        }
    }
    // Initialize Qi
    this->Q.resize(this->data.size());
    for (size_t i = 0; i < this->data.size(); i++) {
        this->Q[i].x = randfun();
        this->Q[i].y = randfun();
    }

    float lambda = 0.3, alpha = 0.3; // magic number by adkevin3307
    while(iterations_limit--) {
        for (size_t i = 0; i < this->Q.size(); i++) {
            for (size_t j = 0; j < this->Q.size(); j++) {
                if (j == i) continue;

                // Compute dij
                float dij = glm::distance(this->Q[i], this->Q[j]);
                if (dij == 0.0) dij = epsilon;

                // Compute delta Qi & delta Qj
                glm::vec2 delta_Qi = lambda * ((this->original_distances[i][j] - dij)/dij) * (this->Q[i] - this->Q[j]);
                glm::vec2 delta_Qj = -delta_Qi;

                if (glm::length(delta_Qi) < epsilon) break;

                this->Q[i] = this->Q[i] + delta_Qi;
                this->Q[j] = this->Q[j] + delta_Qj;
            }
        }
        lambda = alpha * lambda;
    }
    cout << "run\n";
}

vector<float> SammonMapping::get_data() {
    vector<float> result(this->Q.size() * (2 + 3));

    for (size_t i = 0; i < this->Q.size(); i++) {
        result[i * 5 + 0] = this->Q[i].x;
        result[i * 5 + 1] = this->Q[i].y;
        result[i * 5 + 2] = (this->label[i] == 0);
        result[i * 5 + 3] = (this->label[i] == 1);
        result[i * 5 + 4] = (this->label[i] == 2);
    }

    return result;
}

// Assume data is a 2D vector which 1st dimension is the size of data,
// and the 2nd is the size of feature.
// 0-1 normalization, clustering is preserved.
void SammonMapping::feature_normalize() {
    // if data is empty
    if (this->data.size() < 1) return;

    glm::ivec2 data_shape(this->data.size(), this->data[0].size());
    
    for (int features = 0; features < data_shape[1]; features++) {
        float min_value = this->data[0][features], max_value = this->data[0][features];
        for (size_t i = 0; i < this->data.size(); i++) {
            if (min_value > this->data[i][features]) min_value = this->data[i][features];
            if (max_value < this->data[i][features]) max_value = this->data[i][features];
        }
        for (size_t i = 0; i < this->data.size(); i++) {
            // 0-1 normalize
            this->data[i][features] = (this->data[i][features] - min_value)/(max_value - min_value);
        }
    }
}