#ifndef NETWORK_H
#define NETWORK_H

#include "section.hpp"
#include <string>
#include <vector>

using namespace std;

struct Network
{
    Network(string cfgfile, string weightfile);
    virtual ~Network();

    void setBatch(size_t i);
    void predict();

    // Node 包含 layer type 和其參數
    vector<Section*> sectionList;


    int n;
    int batch;
    // 看到的圖片數量
    size_t* seen;
    int* t;
    float epoch;
    int subdivisions;
    Layer* layers;
    float* output;

    float momentum;
    float decay;
    float gamma;
    float scale;
    float power;
    int time_steps;
    int step;
    int max_batches;
    float* scales;
    int* steps;
    int num_steps;
    int burn_in;

    // int adam;
    // float B1;
    // float B2;
    // float eps;

    int inputs;
    int outputs;
    int truths;
    int notruth;
    int h, w, c;
    int max_crop;
    int min_crop;
    float max_ratio;
    float min_ratio;
    int center;
    float angle;
    float aspect;
    float exposure;
    float saturation;
    float hue;
    int random;


    float *input;
    float *truth;
    float *delta;
    float *workspace;
    int train;
    int index;
    float *cost;
    float clip;

private:
    void parseNetwork(string cfgfile);
    void loadWeights(string weightfile);
};

struct size_params
{
    int batch;
    int inputs;
    int h;
    int w;
    int c;
    int index;
    int time_steps;
    Network* net;
};

#endif
