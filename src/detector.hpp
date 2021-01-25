#ifndef DETECTOR_H
#define DETECTOR_H

#include "parser.hpp"
#include <string>

using namespace std;

static void detector(std::string cfgfile, std::string datacfg, std::string weightfile, std::string filename, float thresh)
{
    // list* options = read_data_cfg(datacfg);
    map<string, string> options;
    readData(datacfg, options);
}

#endif
