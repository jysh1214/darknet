#ifndef PARSER_H
#define PARSER_H

#include "utils.hpp"
#include "../include/layer_type.hpp"

#include <string>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

static int geti(string s, int i)
{
    if (s == "") return i;
    else return stoi(s);
}

static float getf(string s, float f)
{
    if (s == "") return f;
    else return stof(s);
}

Layer parseConvolutional(map<string, string>& params)
{

}

static LAYER_TYPE str2LayerType(string type)
{
    if (type == "shortcut") return SHORTCUT;
    if (type == "crop") return CROP;
    if (type == "cost") return COST;
    if (type == "detection") return DETECTION;
    if (type == "region") return REGION;
    if (type == "yolo") return YOLO;
    if (type == "iseg") return ISEG;
    if (type == "local") return LOCAL;
    if (type == "conv" || type == "convolutional") return CONVOLUTIONAL;
    if (type == "deconv" || type == "deconvolutional") return DECONVOLUTIONAL;
    if (type == "activation") return ACTIVE;
    if (type == "logistic") return LOGXENT;
    if (type == "l2norm") return L2NORM;
    if (type == "net" || type == "network") return NETWORK;
    if (type == "crnn") return CRNN;
    if (type == "gru") return GRU;
    if (type == "lstm") return LSTM;
    if (type == "rnn") return RNN;
    if (type == "conn" || type == "connected") return CONNECTED;
    if (type == "max" || type == "maxpool") return MAXPOOL;
    if (type == "reorg") return REORG;
    if (type == "avg" || type == "avgpool") return AVGPOOL;
    if (type == "dropout") return DROPOUT;
    if (type == "lrn" || type == "normalization") return NORMALIZATION;
    if (type == "batchnorm") return BATCHNORM;
    if (type == "soft" || type == "softmax") return SOFTMAX;
    if (type == "route") return ROUTE;
    if (type == "upsample") return UPSAMPLE;
    return BLANK;
}

static void checkFile(fstream& file, string& filepath)
{
    if (!file) {
        throw string("File: " + filepath + " don't exist.\n");
    }
    if (!file.is_open()) {
        throw string("Open " + filepath + " failed.\n");
    }
}

static void readData(string filepath, map<string, string>& list)
{
    fstream file(filepath.c_str(), ios::in);
    checkFile(file, filepath);

    vector<string> lines;
    fgetl(file, lines);

    for (string line: lines) {
        switch (line[0]) {
            case '\0':
            case '#':
            case ';':
                break;
            default:
                if (!readOption(line, list)) {
                    throw string("Could not parse: " + line + "\n");
                }
                break;
        }
    }
    file.close();
}

static void getLabels(string namepath, vector<string>& classes)
{
    fstream file(namepath.c_str(), ios::in);
    checkFile(file, namepath);
    // 一行一個 label
    fgetl(file, classes);
}

#endif
