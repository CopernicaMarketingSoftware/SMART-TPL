/**
 *  Stress.cpp
 *
 *  Stress tests, these are purely here to test the limits of the SMART-TPL library
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <../smarttpl.h>

#include "ccode.h"

using namespace SmartTpl;
using namespace std;

/**
 *  This test will attempt to compile about 1000 chained modifiers, which should
 *  succeed just fine. It can go higher just fine (without causing stack overflow)
 *  but that increases the time of this time by quite a bit.
 */
TEST(Stress, ChainedModifiers)
{
    string input("{$var");
    for (int i = 0; i < 500; ++i) input.append("|upper|lower");
    input.append("}");
    Template tpl((Buffer(input)));

    Data data;
    data.assign("var", "VaRiAbLe");

    string expectedOutput("variable");
    EXPECT_EQ(expectedOutput, tpl.process(data));

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

/**
 *  The following tests should cause stack overflows
 */
TEST(Stress, ElseIfStatements)
{
    string input("{if true}echo");
    for (int i = 0; i < 10000; ++i) input.append("{elseif true}");
    input.append("{/if}");
    EXPECT_THROW(Template tpl((Buffer(input))), std::runtime_error);
}

TEST(Stress, InnerForEachLoops)
{
    string input;
    for (int i = 0; i < 10000; ++i) input.append("{foreach $map as $key => $value}");
    for (int i = 0; i < 10000; ++i) input.append("{/foreach}");
    EXPECT_THROW(Template tpl((Buffer(input))), std::runtime_error);
}