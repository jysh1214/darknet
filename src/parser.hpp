#ifndef PARSER_H
#define PARSER_H

#include "utils.hpp"

#include <string>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

inline void checkFile(fstream& file, string& filepath)
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
