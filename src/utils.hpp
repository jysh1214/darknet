#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <memory>

using namespace std;

static void fgetl(fstream& file, vector<string>& lines)
{
    std::string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    int p = 0;
    string::size_type it = 0;
    for (; it <= content.size(); ++it) {
        if (content[it] == '\n' || content[it] == '\t') {
            lines.push_back(content.substr(p, it - p));
            p = it + 1;
        }
    }
}

static void removeSpace(string& str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

static unique_ptr<string[]> split(string str, const char split_char)
{
    unique_ptr<string[]> two_part(new string[2]());
    string::size_type i = 0;
    for (; i <= str.size(); ++i) {
        if (str[i] == split_char) {
            two_part[0] = str.substr(0, i);
            two_part[1] = str.substr(i + 1, str.size() - i - 1);
            return two_part;
        }
    }

    return nullptr;
}

static bool readOption(string& str, map<string, string>& list)
{
    auto key_val = split(str, '=');
    if (key_val != nullptr) {
        removeSpace(key_val[0]);
        removeSpace(key_val[1]);
        list.insert({key_val[0], key_val[1]});
        return true;
    }

    return false;
}

#endif
