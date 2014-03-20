/**
 *  SyntaxTree.cpp
 *
 *  Implementation of the syntax tree
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
 *  Generate the source code
 *  @param  out     output stream
 */
void SyntaxTree::generate(std::ostream &out) const
{
    // include headers
    out << "#include <smarttpl/shared.h>" << std::endl;
    
    // create function header
    out << "void show_template(smarttpl_callbacks_t *callbacks) {" << std::endl;
    
    // generate the statements
    _statements->generate(out);
    
    // end of the function
    out << "}" << std::endl;
}


/**
 *  End namespace
 */
}

