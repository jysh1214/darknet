#include "network.hpp"
#include "parser.hpp"
#include <iostream>
#include <fstream>

using namespace std;

Network::Network(string cfgfile, string weightfile)
{
    try {
        parseNetwork(cfgfile);
    }
    catch (const string error) {
        cout << error;
    }
}

Network::~Network()
{
    for (auto node: nodeList) {
        if (node) delete node;
    }
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
                Node* node = new Node(type);
                nodeList.push_back(node);
            }
            case '\0':
            case '#':
            case ';':
                break;
            default:
                // 選永遠最後一個 node
                if (!readOption(line, (*(nodeList.end()-1))->params)) {
                    throw string("Could not parse: " + line + "\n");
                }
                break;
        }
    }

    file.close();
}
