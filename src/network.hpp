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



private:
    void parseNetwork(string cfgfile);
};

#endif
