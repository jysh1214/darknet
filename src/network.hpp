#ifndef NETWORK_H
#define NETWORK_H

#include "node.hpp"
#include <string>
#include <vector>

using namespace std;

struct Network
{
    Network(string cfgfile, string weightfile);
    virtual ~Network();

    // Node 包含 layer type 和其參數
    vector<Node*> nodeList;

private:
    void parseNetwork(string cfgfile);
};

#endif
