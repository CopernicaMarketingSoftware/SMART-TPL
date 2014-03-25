/**
 *  Bytecode.cpp
 *
 *  Implementation file of the LLVM code generator.
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
 *  @param  name        Name of the template (this will also be the module identifier)
 *  @param  tree        The syntax tree that is turned into LLVM
 */
Bytecode::Bytecode(const char *name, const SyntaxTree &tree)
{
    // construct a LLVM module
    _module = new llvm::Module(name, _context);

    // create the external function definitions
    _externalFunctions = new ExternalFunctions(_module);
    
    // create the startup function
    _showTemplate = new ShowTemplateFunction(_module);
    
    // generate the LLVM code
    tree.generate(this);
}

/**
 *  Destructor
 */
Bytecode::~Bytecode()
{
    // destruct the startup function
    delete _showTemplate;
    
    // destruct the external functions
    delete _externalFunctions;
    
    // get rid of the module
    delete _module;
}

/**
 *  End namespace
 */
}

