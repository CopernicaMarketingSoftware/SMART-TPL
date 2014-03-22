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
    // we should first check the cache if we already have a compiled version
    // of the template, if we do not have it, we should compile it first. For
    // now we just create the syntax tree (which is the first step in the
    // compilation process)
    SyntaxTree tree(filename);
    
    // generate the source code
//    tree.generate(std::cout);


    CCode code(tree);
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
    // @todo this implementation could be better
    return "";
}
    
    
/**
 *  End namespace
 */
}

