/**
 *  Main.cpp
 *
 *  Main startup function to compile a template *.tpl file into a *.so
 *  shared library.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2017 Copernica BV
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

#include "src/includes.h"

static const struct option opts[] = {
    { "help",              no_argument, 0, 'h' },
    { 0, 0, 0, 0 }
};

/**
 *  Helper function to compile a template
 *  @param  base        base filename (without extension)
 *  @return bool
 */
static bool compile(const std::string &base)
{
    // create the input and output files
    std::string input = base + ".tpl";
    std::string so_output = base + ".so";

    // We directly use the internal classes here to skip the byte compile part
    try
    {
        // construct the file
        SmartTpl::File file(input);
        
        // create template
        SmartTpl::Internal::CCode code(file);

        // the command to compile the C file into a *.so file
        // important to note here is the - on the end, which really just says that
        // we will give the compiler input on stdin instead of through a file
        std::ostringstream command;
        const char* compiler = getenv("CC");
        const char* cflags = getenv("CFLAGS");
        command << (compiler ? compiler : "gcc") << " -x c -fPIC -shared "
                << (cflags ? cflags : "-O3 -nostdlib") << " -o " << so_output << " -";

        // start the actual command and start writing into it if we started it correctly
        FILE *shell = popen(command.str().c_str(), "w");
        if (shell == nullptr) throw std::runtime_error("There was some error while executing popen() " + std::string(strerror(errno)));
        fprintf(shell, "%s", code.asString().c_str());
        int status = pclose(shell);
        if (WEXITSTATUS(status) != 0) throw std::runtime_error("Failed to compile");
    }
    catch (const std::runtime_error &error)
    {
        // report error
        std::cerr << "Failure: " << input << " (" << error.what() << ")" << std::endl;

        // report error
        return false;
    }

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
              << "--help, -h      This help information." << std::endl;
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
    while ((arg = getopt_long(argc, argv, "h", opts, &argc)) != -1) {
        switch (arg) {
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
