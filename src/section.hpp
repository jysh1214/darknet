#ifndef SECTION_H
#define SECTION_H

#include "../include/layer_type.hpp"
#include "parser.hpp"
#include "layer.hpp"
#include <map>
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

    void assignValue()
    {
        switch (type) {
            case NETWORK:
                break;
            case CONVOLUTIONAL:
                layer = parseConvolutional(params);
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
