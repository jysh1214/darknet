#ifndef DETECTOR_H
#define DETECTOR_H

#include "imgproc.hpp"
#include "parser.hpp"
#include "network.hpp"
#include <string>
#include <iostream>

using namespace std;

static void detector(string cfgfile, string datacfg, string weightfile, string filename, float thresh)
{
    map<string, string> options;

    try {
        readData(datacfg, options);
    } // 檔案不存在，無法開啟，或是格式不對
    catch (const string error) {
        cout << error;
        return;
    }

    vector<string> classes;
    string namePath = options["names"];
    getLabels(namePath, classes);

    // image **alphabet = load_alphabet();
    Network* net = new Network(cfgfile, weightfile);
    net->setBatch(1);
    float nms=.45;

    fstream file(filename.c_str(), ios::in);
    checkFile(file, filename);
    Image image = readImage(filename);

    net->predict();
}

#endif
