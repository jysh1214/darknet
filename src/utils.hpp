#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

static void fgetl(fstream& file, vector<string>& lines)
{
    std::string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    int p = 0;
    string::size_type it = 0;
    for (; it <= content.size(); ++it) {
        if (content[it] == '\n') {
            lines.push_back(content.substr(p, it - p));
            p = it + 1;
        }
    }
}

#endif
