#ifndef PARSER_H
#define PARSER_H

#include "utils.hpp"

#include <string>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

static void readData(string filepath, map<string, string>& list)
{
    fstream file(filepath.c_str(), ios::in);
    if (!file) {
        throw string("File: " + filepath + " don't exist.\n");
    }
    if (!file.is_open()) {
        throw string("Open " + filepath + " failed.\n");
    }

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

#endif
