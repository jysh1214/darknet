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
                // 永遠選最後一個 node
                if (!readOption(line, (*(sectionList.end()-1))->params)) {
                    throw string("Could not parse: " + line + "\n");
                }
                break;
        }
    }

    file.close();
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
