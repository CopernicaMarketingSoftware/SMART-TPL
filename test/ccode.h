/**
 *  CCode.h
 *
 *  Contains a method to not only generate the C code, but also attempt to
 *  compile it.
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#pragma once

#define SHARED_LIBRARY "/tmp/test.so"

#include <gtest/gtest.h>
#include <smarttpl.h>

using namespace SmartTpl;
using namespace std;

// @todo Add an option to disable this on runtime
inline void compile(const Template &tpl, bool assert = false)
{
    FILE *gccshell = popen("gcc -x c -Wall -Werror -fPIC -shared -o " SHARED_LIBRARY " -", "w");
    if (assert)
    {
        ASSERT_TRUE(gccshell != NULL);
    }
    else
    {
        EXPECT_TRUE(gccshell != NULL);
    }
    if (gccshell)
    {
        fprintf(gccshell, "%s", tpl.compile().c_str());
        if (assert)
        {
            ASSERT_EQ(0, pclose(gccshell)) << "gcc failed to compile this template";
        }
        else
        {
            EXPECT_EQ(0, pclose(gccshell)) << "gcc failed to compile this template";
        }
    }

    FILE *clangshell = popen("clang -x c -Wall -Werror -fPIC -shared -o " SHARED_LIBRARY " -", "w");
    if (assert)
    {
        ASSERT_TRUE(clangshell != NULL);
    }
    else
    {
        EXPECT_TRUE(clangshell != NULL);
    }
    if (clangshell)
    {
        fprintf(clangshell, "%s", tpl.compile().c_str());
        if (assert)
        {
            ASSERT_EQ(0, pclose(clangshell)) << "clang failed to compile this template";
        }
        else
        {
            EXPECT_EQ(0, pclose(clangshell)) << "clang failed to compile this template";
        }
    }
}