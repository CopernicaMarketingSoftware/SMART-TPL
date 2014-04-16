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
#include <include/smarttpl.h>
#include <unistd.h>

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
        unlink(c_output.c_str());
        
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
    unlink(c_output.c_str());
    
    // done
    return true;
}

/**
 *  Main procedure
 *  @param  argc
 *  @param  argv
 */
int main(int argc, const char *argv[])
{
    // check number of arguments
    if (argc < 2)
    {
        // we need at least one template file
        std::cerr << "Usage: " << argv[0] << " <yourtemplate.tpl>" << std::endl;
        return -1;
    }
    
    // number of files compiled
    int success = 0;
    
    // loop through the arguments
    for (int i=1; i<argc; i++)
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
    return success == (argc - 1) ? 0 : -1;
}
