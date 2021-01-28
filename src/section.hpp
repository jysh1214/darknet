#ifndef SECTION_H
#define SECTION_H

#include "../include/layer_type.hpp"
#include <map>
#include <iostream>

using namespace std;

// OpenCV 已經有 Node, 所以用 Section 命名
struct Section
{
    Section(const LAYER_TYPE _type): type(_type){}
    const LAYER_TYPE type;
    map<string, string> params;
};

#endif
