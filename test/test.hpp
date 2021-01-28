#ifndef TEST_H
#define TEST_H

#include "../include/layer_type.hpp"

#include "../src/darknet.hpp"
#include "../src/detector.hpp"
#include "../src/network.hpp"
#include "../src/section.hpp"
#include "../src/parser.hpp"
#include "../src/utils.hpp"

#include <string>
#include <map>

using namespace std;

TEST(ParserTEST, readValidDataFile)
{
    string path = "cfg/coco.data";
    map<string, string> m;
    ASSERT_NO_THROW(readData(path, m));
}

TEST(ParserTEST, readInValidDataFile)
{
    string path = "fuck.data";
    map<string, string> m;
    ASSERT_ANY_THROW(readData(path, m));
}

TEST(UtilsTEST, FileGetLines)
{
    string path = "cfg/test.data";
    fstream file(path, ios::in);
    vector<string> lines;
    ASSERT_NO_THROW(fgetl(file, lines));
}

TEST(SplitTEST, SplitString)
{
    string str = "sex = fuck";
    unique_ptr<string[]> s = split(str, '=');
    ASSERT_EQ(s[0], "sex ");
    ASSERT_EQ(s[1], " fuck");
}

TEST(SplitTEST, RemoveSpace)
{
    string str = "sex = fuck";
    unique_ptr<string[]> s = split(str, '=');
    removeSpace(s[0]);
    removeSpace(s[1]);
    ASSERT_EQ(s[0], "sex");
    ASSERT_EQ(s[1], "fuck");
}

TEST(OptionTEST, ReadOption)
{
    string path = "cfg/coco.data";
    map<string, string> m;
    ASSERT_NO_THROW(readData(path, m));
    ASSERT_EQ(m["train"], "/home/pjreddie/data/coco/trainvalno5k.txt");
    ASSERT_EQ(m["valid"], "coco_testdev");
    ASSERT_EQ(m["names"], "data/coco.names");
    ASSERT_EQ(m["backup"], "/home/pjreddie/backup/");
    ASSERT_EQ(m["eval"], "coco");
}

TEST(GetLabelsTEST, GetLabels)
{
    string path = "data/coco.names";
    vector<string> labels;
    ASSERT_NO_THROW(getLabels(path, labels));
    ASSERT_EQ(labels.size(), 80);
    ASSERT_EQ(labels[0], "person");
    ASSERT_EQ(labels[1], "bicycle");
    ASSERT_EQ(labels[2], "car");
}

TEST(PaerserNetworkTEST, GetLayerType)
{
    string cfgfile = "cfg/yolov3-tiny.cfg";
    string weightfile = "";
    Network* net = new Network(cfgfile, weightfile);

    ASSERT_EQ(net->sectionList[0]->type, NETWORK);
    ASSERT_EQ(net->sectionList[1]->type, CONVOLUTIONAL);

    delete net;
}

TEST(PaerserNetworkTEST, GetLayerParams)
{
    string cfgfile = "cfg/yolov3-tiny.cfg";
    string weightfile = "";
    Network* net = new Network(cfgfile, weightfile);

    Section* net_section = net->sectionList[0];
    ASSERT_EQ(net_section->type, NETWORK);
    ASSERT_EQ(net_section->params["batch"], "1");
    ASSERT_EQ(net_section->params["decay"], "0.0005");

    Section* conv_section = net->sectionList[1];
    ASSERT_EQ(conv_section->type, CONVOLUTIONAL);
    ASSERT_EQ(conv_section->params["filters"], "16");
    ASSERT_EQ(conv_section->params["activation"], "leaky");

    delete net;
}

TEST(SetBatchTEST, CheckBatch)
{
    string cfgfile = "cfg/yolov3-tiny.cfg";
    string weightfile = "";
    Network* net = new Network(cfgfile, weightfile);
    net->setBatch(1);

    for (auto section: net->sectionList) {
        ASSERT_EQ(section->params["batch"], "1");
    }

    delete net;
}

TEST(CheckFileTEST, CheckFile)
{
    string filename = "data/dog.jpg";
    fstream file(filename.c_str(), ios::in);
    ASSERT_NO_THROW(checkFile(file, filename));
}

TEST(CheckNetOptionTEST, CheckNet)
{
    string cfgfile = "cfg/yolov3-tiny.cfg";
    string weightfile = "";
    Network* net = new Network(cfgfile, weightfile);
    net->setBatch(1);

    ASSERT_NEAR(net->momentum , 0.9, 0.0001);
    ASSERT_NEAR(net->decay , 0.0005, 0.0001);
}

#endif
