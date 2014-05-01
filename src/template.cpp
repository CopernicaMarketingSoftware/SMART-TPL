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
 *  @param  source        Source of the template to load
 */
Template::Template(const Source& source)
{
    // prevent exceptions
    try 
    {
        // is the source a shared library?
        if (source.library())
        {
            // hey that's cool, we can create create a shard library
            _executor = new Library(source.name());
        }
        else
        {
            // it was not a shared library, we're going to compile it into bytecode ourselves
            _executor = new Bytecode(source);
        }
    } 
    catch (const std::runtime_error &error) 
    {
        // @todo is this necessary?
        
        // an error occured
        _executor = nullptr;
        throw;
    }
}

/**
 *  Destructor
 */
Template::~Template()
{
    // we no longer need the executor
    if (_executor) delete _executor;
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

