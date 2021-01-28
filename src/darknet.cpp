#include "darknet.hpp"
#include "detector.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Usage: Darknet <function>\n";
        return 0;
    }

    string cfgfile = "cfg/yolov3-tiny.cfg";
    string datafile = "cfg/coco.data";
    string weightsfile = "";

    if (std::string(argv[1]) == "predict") {
        detector(cfgfile, datafile, weightsfile, "data/dog.jpg", 0.5);
    }

    return 0;
}
