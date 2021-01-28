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

    // 看到的圖片數量
    size_t* seen;

private:
    void parseNetwork(string cfgfile);
    void loadWeights(string weightfile);
};

#endif
