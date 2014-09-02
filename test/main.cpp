/**
 *  Main.cpp
 *
 *  Start point of the unit tests
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

#include <gtest/gtest.h>
#include <getopt.h>

#include "ccode.h"

bool no_clang = false;
bool no_gcc = false;

static const struct option opts[] = {
    { "help",              no_argument, 0, 'h' }, // Print a basic help
    { "no-clang",          no_argument, 0, 'c' }, // Don't compile tests with clang
    { "no-gcc",            no_argument, 0, 'g' }, // Don't compile tests with gcc
    { "no-compile",        no_argument, 0, 'C' }, // Don't compile tests at all
    { 0, 0, 0, 0 }
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::FLAGS_gtest_shuffle = true;
    int arg, optindex;
    while ((arg = getopt_long(argc, argv, "gcCh", opts, &optindex)) != -1)
    {
        switch (arg) {
            case 'c':
                no_clang = true;
                break;
            case 'g':
                no_gcc = true;
                break;
            case 'C':
                no_clang = true;
                no_gcc = true;
                break;
            case 'h':
            default:
                std::cout << "  --no-clang           Don't compile tests with clang" << std::endl
                          << "  --no-gcc             Don't compile tests with gcc" << std::endl
                          << "  --no-compile         Don't try to compile tests at all" << std::endl;
                return EXIT_FAILURE;
        }
    }
    if (no_gcc == false) {
        int gcc = system("gcc --version");
        no_gcc = (!WEXITSTATUS(gcc) == 0);
    }
    if (no_clang == false) {
        int clang = system("clang --version");
        no_clang = (!WEXITSTATUS(clang) == 0);
    }
    return RUN_ALL_TESTS();
};