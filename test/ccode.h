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

#include <gtest/gtest.h>
#include <smarttpl.h>

using namespace SmartTpl;
using namespace std;

// @todo Add an option to disable this on runtime
inline void compile(const Template &tpl) {
    FILE *gccshell = popen("gcc -x c -c -Wall -Werror -o /tmp/.o -", "w");
    ASSERT_TRUE(gccshell != NULL);
    fprintf(gccshell, "%s", tpl.compile().c_str());
    EXPECT_EQ(0, pclose(gccshell)) << "gcc failed to compile this template";

    FILE *clangshell = popen("clang -x c -c -Wall -Werror -o /tmp/.o -", "w");
    ASSERT_TRUE(clangshell != NULL);
    fprintf(clangshell, "%s", tpl.compile().c_str());
    EXPECT_EQ(0, pclose(clangshell)) << "clang failed to compile this template";
};