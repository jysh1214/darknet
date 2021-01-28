#include "../include/size_params.hpp"
#include "layer.hpp"
#include "network.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

Network::Network(string cfgfile, string weightfile)
{
    try {
        parseNetwork(cfgfile);
        loadWeights(weightfile);
    }
    catch (const string error) {
        cout << error;
    }
}

Network::~Network()
{
    for (auto section: sectionList) {
        if (section) delete section;
    }
}

void Network::setBatch(size_t i)
{
    for (auto section: sectionList) {
        stringstream temp;
        temp << i;
        section->params["batch"] = temp.str();
    }
}

void Network::predict()
{

}

void Network::parseNetwork(string cfgfile)
{
    fstream file(cfgfile.c_str(), ios::in);
    checkFile(file, cfgfile);

    vector<string> lines;
    fgetl(file, lines);

    for (string line: lines) {
        switch (line[0]) {
            case '[': {
                int p = 1;
                while (line[p] != ']') ++p;
                LAYER_TYPE type = str2LayerType(line.substr(1, p-1));
                Section* section = new Section(type);
                sectionList.push_back(section);
            }
            case '\0':
            case '#':
            case ';':
                break;
            default:
                if (!readOption(line, (*(sectionList.end()-1))->params)) {
                    throw string("Could not parse: " + line + "\n");
                }
                break;
        }
    }
    file.close();
    // assign 第一層 network 的參數
    #define NET_SECTION sectionList[0]->params
    this->momentum = getf(NET_SECTION["momentum"], 0.9);
    this->decay = getf(NET_SECTION["decay"], 0.001);
    int subdivs = geti(NET_SECTION["subdivisions"], 1);
    this->time_steps = geti(NET_SECTION["time_steps"], 1);
    this->notruth = geti(NET_SECTION["notruth"], 0);
    this->batch /= subdivs;
    this->batch *= this->time_steps;
    this->subdivisions = subdivs;
    this->random = geti(NET_SECTION["random"], 0);
    this->h = geti(NET_SECTION["height"], 0);
    this->w = geti(NET_SECTION["width"], 0);
    this->c = geti(NET_SECTION["channels"], 0);
    this->inputs = geti(NET_SECTION["inputs"], this->h * this->w * this->c);
    this->max_crop = geti(NET_SECTION["max_crop"], this->w*2);
    this->min_crop = geti(NET_SECTION["min_crop"], this->w);
    this->max_ratio = getf(NET_SECTION["max_ratio"], (float) this->max_crop / this->w);
    this->min_ratio = getf(NET_SECTION["min_ratio"], (float) this->min_crop / this->w);
    this->center = geti(NET_SECTION["center"], 0);
    this->clip = geti(NET_SECTION["clip"], 0);
    #undef NET_SECTION

    sizeParams params;
    params.h = this->h;
    params.w = this->w;
    params.c = this->c;
    params.inputs = this->inputs;
    params.batch = this->batch;
    params.time_steps = this->time_steps;

    // 剩下每個 Section 已經讀到所有參數, 現在 assign 到 layer
    for (auto section: sectionList) {
        section->assignValue(params);
    }
}

void Network::loadWeights(string weightfile)
{
    FILE *fp = fopen("yolov3.weights", "wb");
    int major = 0;
    int minor = 2;
    int revision = 0;
    fwrite(&major, sizeof(int), 1, fp);
    fwrite(&minor, sizeof(int), 1, fp);
    fwrite(&revision, sizeof(int), 1, fp);

    if ((major*10 + minor) >= 2 && major < 1000 && minor < 1000) {
        fread(this->seen, sizeof(size_t), 1, fp);
    } else {
        int iseen = 0;
        fread(&iseen, sizeof(int), 1, fp);
        *(this->seen) = iseen;
    }
    int transpose = (major > 1000) || (minor > 1000);

    for (auto section: sectionList){

    }

    fclose(fp);
}
