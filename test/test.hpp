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

// TEST(UtilsTEST, FileGetLines)
// {
//     string path = "cfg/test.data";
//     fstream file(path, ios::in);
//     vector<string> lines;
//     ASSERT_NO_THROW(fgetl(file, lines));
//     ASSERT_EQ(lines[0], "classes= 80");
//     ASSERT_EQ(lines[1], "fuck1");
//     ASSERT_EQ(lines[2], "fuck2");
//     ASSERT_EQ(lines[3], "fuckfuck");
// }

#endif
