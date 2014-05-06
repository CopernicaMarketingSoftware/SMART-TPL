/**
 *  Jit.cpp
 *
 *  Jit related tests, these will obivously be executing templates
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <smarttpl.h>

using namespace SmartTpl;
using namespace std;

TEST(Jit, ForEach)
{
    string input("{foreach $item in $list}item: {$item}\n{/foreach}");
    Buffer buffer(input);
    Template tpl(buffer);

    ListValue list;
    for (int i = 0; i < 5; ++i) list.add(i);

    Data data;
    data.assign("list", &list);

    string expectedOutput("item: 0\nitem: 1\nitem: 2\nitem: 3\nitem: 4\n");
    EXPECT_EQ(tpl.process(data), expectedOutput);
}

TEST(Jit, ForEachWithKeys)
{
    string input("{foreach $map as $key => $value}key: {$key}\nvalue: {$value}{/foreach}");
    Buffer buffer(input);
    Template tpl(buffer);

    MapValue map;
    map.assign("1", 1)
       .assign("2", 2)
       .assign("3", 3)
       .assign("4", 4)
       .assign("5", 5);
    Data data;
    data.assign("map", &map);

    string expectedOutput("key: 1\nvalue: 1key: 2\nvalue: 2key: 3\nvalue: 3key: 4\nvalue: 4key: 5\nvalue: 5");
    EXPECT_EQ(tpl.process(data), expectedOutput);
}

TEST(Jit, If)
{
    string input("{if true}true{else}false{/if}");
    Buffer buffer(input);
    Template tpl(buffer);

    string expectedOutput("true");
    EXPECT_EQ(tpl.process(), expectedOutput);
}

TEST(Jit, StringComparisonEquals)
{
    string input("{if \"string1\" == \"string2\"}true{else}false{/if}");
    Buffer buffer(input);
    Template tpl(buffer);

    string expectedOutput("false");
    EXPECT_EQ(tpl.process(), expectedOutput);
}

TEST(Jit, StringComparisonNotEquals)
{
    string input("{if \"string1\" != \"string2\"}true{else}false{/if}");
    Buffer buffer(input);
    Template tpl(buffer);

    string expectedOutput("true");
    EXPECT_EQ(tpl.process(), expectedOutput);
}