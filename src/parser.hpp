#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

static void readData(string filepath, map<string, string>& list)
{
    fstream file(filepath, ios::in);
    if (!file) {
        string error =  "File: " + filepath + "don't exist.\n";
        throw string(error);
    }

    file.close();
}

#endif
