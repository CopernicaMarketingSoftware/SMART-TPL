/**
 *  Ccode.cpp
 *
 *  Implementation file for the Ccode class
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
 *  @param  tree        The abstract syntax tree of the template
 */
CCode::CCode(const SyntaxTree &tree)
{
    // include headers
    _out << "#include <smarttpl/shared.h>" << std::endl;
    
    // create function header
    _out << "void show_template(smarttpl_callbacks_t *callbacks) {" << std::endl;
    
    // generate the statements
    tree.generate(this);
    
    // end of the function
    _out << "}" << std::endl;
}

/**
 *  Output raw data
 *  @param  buffer      buffer to output
 *  @param  size        buffer size
 */
void CCode::raw(const char *data, size_t size) 
{
    // quote newlines, null characters, etc in the string so that it can
    // be picked up by the compiler
    QuotedString quoted(data, size);
    
    // output the data
    _out << "callbacks->write(\"" << quoted << "\", " << size << ");" << std::endl;
}

/**
 *  End of namespace
 */
}

