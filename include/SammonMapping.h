#pragma once

#include "Method.h"

#include <cmath>
#include <vector>
#include <random>
#include <functional>

using namespace std;

class SammonMapping : public Method{
    using super = Method;
public:
    SammonMapping();
    ~SammonMapping();
    SammonMapping(string, string);
    float distance(vector<float>, vector<float>);
    void run();
    vector<float> get_data();
    void feature_normalize();
private:
    string inf_filename, raw_fliename;
    vector<vector<float> > data;
    vector<int> label;
    vector<vector<float> > original_distances;
    vector<glm::vec2> Q;
};