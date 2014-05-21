/**
 *  Callbacks.cpp
 *
 *  Callback related unit tests
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <../smarttpl.h>

#include "ccode.h"

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

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        EXPECT_EQ(expectedOutput, library.process(data));
    }
}

TEST(Callbacks, CallbackCaching)
{
    string input("{$name} {$name} {$nocache} {$nocache}");
    Template tpl((Buffer(input)));

    {
        int counter = 0;
        int nocache = 0;
        Data data;
        data.callback("name", [&counter]() {
            counter++;
            return "Name";
        }, true)
        .callback("nocache", [&nocache]() {
            nocache++;
            return "NoCache";
        });

        string expectedOutput("Name Name NoCache NoCache");
        EXPECT_EQ(expectedOutput, tpl.process(data));
        EXPECT_EQ(counter, 1);
        EXPECT_EQ(nocache, 2); // Should be called twice, as it is printed twice. This essentially tests if size() is cached
    }

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        int counter = 0;
        int nocache = 0;
        Data data;
        data.callback("name", [&counter]() {
            counter++;
            return "Name";
        }, true)
        .callback("nocache", [&nocache]() {
            nocache++;
            return "NoCache";
        });

        string expectedOutput("Name Name NoCache NoCache");
        EXPECT_EQ(expectedOutput, library.process(data));
        EXPECT_EQ(counter, 1);
        EXPECT_EQ(nocache, 2); // Should be called twice, as it is printed twice. This essentially tests if size() is cached
    }
}

TEST(Callbacks, Counter)
{
    string input("{$i} {$i} {$i} {$i} {$i}");
    Template tpl((Buffer(input)));

    int counter = 0;
    Data data;
    data.callback("i", [&counter]() {
        return ++counter;
    });

    string expectedOutput("1 2 3 4 5");
    EXPECT_EQ(expectedOutput, tpl.process(data));
    EXPECT_EQ(5, counter);

    if (compile(tpl)) // This will compile the Template into a shared library
    {
        Template library(File(SHARED_LIBRARY)); // Here we load that shared library
        counter = 0; // Reset our counter

        EXPECT_EQ(expectedOutput, library.process(data));
        EXPECT_EQ(5, counter);
    }
}