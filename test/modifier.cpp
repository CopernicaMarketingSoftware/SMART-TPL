/**
 *  Modifier.cpp
 *
 *  Test the built-in modifiers
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

TEST(Modifier, ToUpper)
{
    string input("{$var|toupper}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("VARIABLE");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, ToLower)
{
    string input("{$var|tolower}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("variable");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, Cat)
{
    string input("{$var|cat:\" 1 2 3\"}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "Testing");

    string expectedOutput("Testing 1 2 3");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}

TEST(Modifier, CountCharacters)
{
    string input("{$var|count_characters}\n{$var|count_characters:true}");
    Buffer buffer(input);
    Template tpl(buffer);

    Data data;
    data.assign("var", "Cold Wave Linked to Temperatures.");

    string expectedOutput("29\n33");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    compile(tpl);
}