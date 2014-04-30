/**
 *  Main.cpp
 *
 *  Main startup function to compile a template *.tpl file into a *.so
 *  shared library.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <cstring>
#include <memory>
#include <map>
#include <unistd.h>
#include <getopt.h>

#include "smarttpl.h"

static const struct option opts[] = {
    { "help",              no_argument, 0, 'h' },
    { "keep-file",         no_argument, 0, 'k' },
    { 0, 0, 0, 0 }
};

bool keepfile = false;

/**
 *  Helper function to compile a template
 *  @param  base        base filename (without extension)
 *  @return bool
 */
static bool compile(const std::string &base)
{
    // create the input and output files
    std::string input = base + ".tpl";
    std::string c_output = base + ".c";
    std::string so_output = base + ".so";

    // store that in the C file
    std::ofstream cstream(c_output);

    // must be open
    if (!cstream.is_open())
    {
        // report error
        std::cerr << "Failure: " << input << " (" << c_output << " " << strerror(errno) << ")" << std::endl;

        // report error
        return false;
    }

    // when the template object is created, exceptions may pop-up describing
    // syntax error or other problems
    try
    {
        SmartTpl::File file(input);
        // create template
        SmartTpl::Template tpl(file);

        // convert into C code
        cstream << tpl.compile();

        // close the c-stream
        cstream.close();
    }
    catch (const std::runtime_error &error)
    {
        // report error
        std::cerr << "Failure: " << input << " (" << error.what() << ")" << std::endl;

        // unlink our failed C file
        if (!keepfile) unlink(c_output.c_str());

        // report error
        return false;
    }

    // the command to compile the C file into a *.so file
    std::ostringstream command;
    const char* compiler = getenv("CC");
    const char* cflags = getenv("CFLAGS");
    command << (compiler ? compiler : "gcc") << " " << c_output << " -fPIC -shared "
            << (cflags ? cflags : "-O3") << " -o " << so_output;

    // run the command
    int status = system(command.str().c_str());

    // if we ran into an error, we keep the C source file intact
    if (WEXITSTATUS(status) != 0) return false;

    // unlink intermediate C file
    if (!keepfile) unlink(c_output.c_str());

    // done
    return true;
}

/**
 *  Help printer
 *  @param program   The program name
 *  @param exit_code With what exit code should we exit the program afterwards
 */
void print_help(const char *program, int exit_code)
{
    std::cerr << "Usage: " << program << " [options] <yourtemplate.tpl>..." << std::endl
              << "--help, -h      This help information." << std::endl
              << "--keep-file, -k Keep the generated C file." << std::endl;
    exit(exit_code);
}

/**
 *  Main procedure
 *  @param  argc
 *  @param  argv
 */
int main(int argc, char *argv[])
{
    // check number of arguments
    if (argc < 2)
    {
        print_help(argv[0], EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    int arg;
    while ((arg = getopt_long(argc, argv, "kh", opts, &argc)) != -1) {
        switch (arg) {
        case 'k':
            keepfile = true;
            break;
        case 'h':
            print_help(argv[0], EXIT_SUCCESS);
            return EXIT_SUCCESS;
        }
    }

    // number of files compiled
    int success = 0;

    // loop through the arguments
    for (int i=optind; i<argc; i++)
    {
        // name of the template
        const char *filename = argv[i];

        // find the extension
        const char *extension = strrchr(filename, '.');
        if (extension && strcmp(extension, ".tpl") == 0)
        {
            // this is valid extension
            if (compile(std::string(filename, extension - filename))) success++;
        }
        else
        {
            // report an error
            std::cerr << "Failure: " << filename << " (not a *.tpl file)" << std::endl;
        }
    }

    // done
    return success == (argc - optind) ? EXIT_SUCCESS : EXIT_FAILURE;
}
