#ifndef SECTION_H
#define SECTION_H

#include "../include/layer_type.hpp"
#include <map>
#include <iostream>

using namespace std;

/**
 * 包含 Layer 和其參數
 */
struct Section
{
    Section(const LAYER_TYPE _type): type(_type){}
    const LAYER_TYPE type;
    map<string, string> params;
};

#endif
