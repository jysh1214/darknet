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
    fstream file(filepath, ios::in);
    if (!file) {
        string error =  "File: " + filepath + " don't exist.\n";
        throw string(error);
    }
    if (!file.is_open()) {
        string error =  "Open " + filepath + " failed.\n";
        throw string(error);
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
                    string error =  "Could not parse: " + line + "\n";
                    throw error;
                }
                break;
        }
    }
    file.close();
}

#endif
