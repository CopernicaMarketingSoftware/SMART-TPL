/**
 *  Callbacks.cpp
 *
 *  Callback related unit tests
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <smarttpl.h>

using namespace SmartTpl;
using namespace std;

TEST(Callbacks, SimpleCallback)
{
    string input("{$name}");
    Template tpl((Buffer(input)));

    Data data;
    data.callback("name",[](){ return "Name"; });

    string expectedOutput("Name");
    EXPECT_EQ(expectedOutput, tpl.process(data));
}

TEST(Callbacks, CallbackCaching)
{
    string input("{$name} {$name}");
    Template tpl((Buffer(input)));

    int counter = 0;
    Data data;
    data.callback("name", [&counter](){
        counter++;
        return "Name";
      }, true);

    string expectedOutput("Name Name");
    EXPECT_EQ(expectedOutput, tpl.process(data));
    EXPECT_EQ(counter, 1);
}