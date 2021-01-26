#ifndef TEST_H
#define TEST_H

#include "../src/darknet.hpp"
#include "../src/detector.hpp"
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
}

#endif
