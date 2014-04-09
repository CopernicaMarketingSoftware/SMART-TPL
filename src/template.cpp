/**
 *  Template.cpp
 * 
 *  Implementation of the Template class
 * 
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Constructor
 *  @param  filename        Name of the template to load
 */
Template::Template(const char *filename)
{
    // is this a *.so file?
    char *extension = strrchr(filename, '.');
    if (extension && strcasecmp(extension, ".so") == 0)
    {
        // this is a shared library
        _executor = new Library(filename);
    }
    else
    {
        // this is a raw template file, convert it into byte-code
        _executor = new Bytecode(filename);
    }
}

/**
 *  Destructor
 */
Template::~Template()
{
    // we no longer need the executor
    delete _executor;
}

/**
 *  Get the template representation in C that can be compiled into a shared 
 *  object. This method only works for templates that were not already a 
 *  shared library.
 * 
 *  @return std::string
 */
std::string Template::compile() const
{
    return _executor->compile();
}

/**
 *  Process the template, given a certain data source
 * 
 *  The data object that needs to be passed to this method is an object 
 *  that contains the values of all variables that can be user inside the
 *  template.
 * 
 *  @param  data        Data source
 *  @return std::string
 */
std::string Template::process(const Data &data) const
{
    // we need a handler object
    Handler handler(&data);
    
    // ask the executor to display the template
    _executor->process(handler);
    
    // return the generated output string
    return handler.output();
}
    
/**
 *  End namespace
 */
}

