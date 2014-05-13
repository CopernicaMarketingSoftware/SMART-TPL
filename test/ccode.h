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

/**
 *  Tries to compile a template to a shared library
 *  It will compile the template with both gcc and clang, in both cases it'll
 *  compile it with "-Wall -Werror", so no warnings allowed! If it succesfully
 *  compiled you can load the shared library by loading the file SHARED_LIBRARY.
 *  If you want to run the unittests without compiling the templates into shared
 *  libraries simply run with NO_COMPILE in your enviroment variables
 *  @todo Maybe add a flag for no compile later on
 *  @todo Add options to only compile with gcc, or only compile with clang
 *  @param  tpl The template to actually compile
 *  @return true if succesfully compiled, false otherwise
 */
inline bool compile(const Template &tpl)
{
    if (getenv("NO_COMPILE")) return false;

    int gccret = -1;
    int clangret = -1;

    FILE *gccshell = popen("gcc -x c -pipe -Wall -Werror -fPIC -shared -o " SHARED_LIBRARY " -", "w");
    EXPECT_TRUE(gccshell != NULL) << strerror(errno);
    if (gccshell)
    {
        fprintf(gccshell, "%s", tpl.compile().c_str());
        gccret = pclose(gccshell);
        EXPECT_EQ(0, gccret) << "gcc failed to compile this template";
    }

    FILE *clangshell = popen("clang -x c -pipe -Wall -Werror -fPIC -shared -o " SHARED_LIBRARY " -", "w");
    EXPECT_TRUE(clangshell != NULL) << strerror(errno);
    if (clangshell)
    {
        fprintf(clangshell, "%s", tpl.compile().c_str());
        clangret = pclose(clangshell);
        EXPECT_EQ(0, clangret) << "clang failed to compile this template";
    }

    return gccret == 0 || clangret == 0;
}