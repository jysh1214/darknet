#ifndef SECTION_H
#define SECTION_H

#include "../include/layer_type.hpp"
#include "../include/size_params.hpp"
#include "conv_layer.hpp"
#include "parser.hpp"
#include <map>
#include <string>
#include <iostream>

using namespace std;

/**
 * 包含 Layer 和其參數
 */
struct Section
{
    Section(const LAYER_TYPE _type): type(_type) {}
    const LAYER_TYPE type;

    Layer layer;
    map<string, string> params;

    void assignValue(sizeParams size_params)
    {
        switch (type) {
            case NETWORK:
                break;
            case CONVOLUTIONAL:
                try {
                    layer = ConvLayer(params, size_params);
                }
                catch (const string error) {
                    cout << error;
                }
                break;
            case YOLO:
                // layer = parseYOLO(params);
                break;
            case SHORTCUT:
                // layer = parseShortcut(params);
                break;
            default:
                break;
        }
    }
};

#endif
