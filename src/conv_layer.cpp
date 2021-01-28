#include "conv_layer.hpp"

ConvLayer::ConvLayer(std::map<string, string>& params, sizeParams size_params)
{
    int n = geti(params["filters"], 1);
    int size = geti(params["size"], 1);
    int stride = geti(params["stride"], 1);
    int pad = geti(params["pad"], 0);
    int padding = geti(params["padding"], 0);
    int groups = geti(params["groups"], 1);
    if (pad > 0) padding = size/2;
    string activation_s = gets(params["activation"], "logistic");
    ACTIVATION activation = getActivation(activation_s);
    int batch, h, w, c;
    h = size_params.h;
    w = size_params.w;
    c = size_params.c;
    batch=size_params.batch;

    if (!(h && w && c)) throw string("Parse Conv Layer failed.");
    int batch_normalize = geti(params["batch_normalize"], 0);
    int binary = geti(params["binary"], 0);
    int xnor = geti(params["xnor"], 0);

    this->type = CONVOLUTIONAL;
    this->groups = groups;
    this->h = h;
    this->w = w;
    // l.c = c;
    this->c = c;
    // l.n = n;
    this->n = n;
    // l.binary = binary;
    this->binary = binary;
    // l.xnor = xnor;
    this->xnor = xnor;
    // l.batch = batch;
    this->batch = batch;
    // l.stride = stride;
    this->stride = stride;
    // l.size = size;
    this->size = size;
    // l.pad = padding;
    this->pad = padding;
    // l.batch_normalize = batch_normalize;
    this->batch_normalize = batch_normalize;

}

ConvLayer::~ConvLayer()
{

}
