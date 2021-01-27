#ifndef NODE_H
#define NODE_H

#include "../include/layer_type.hpp"
#include <map>
#include <iostream>

using namespace std;

struct Node
{
    Node(const LAYER_TYPE _type): type(_type){}
    const LAYER_TYPE type;
    map<string, string> params;
};

#endif
