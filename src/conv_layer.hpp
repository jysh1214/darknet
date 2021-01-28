#ifndef CONV_LAYER_HPP
#define CONV_LAYER_HPP

#include "../include/activation.hpp"
#include "../include/layer_type.hpp"
#include "../include/size_params.hpp"
#include "layer.hpp"
#include "parser.hpp"
#include <map>
#include <string>

using namespace std;

struct ConvLayer: public Layer
{
    ConvLayer(std::map<string, string>& params, sizeParams size_params);
    virtual ~ConvLayer();
};

#endif
