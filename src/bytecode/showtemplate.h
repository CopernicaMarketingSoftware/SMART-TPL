/**
 *  ShowTemplateFunction.h
 *
 *  Class that is used for generating the 'show_template()' function in LLVM
 *  byte code.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { 

/**
 *  Class definition
 */
class ShowTemplateFunction
{
private:



public:
    /**
     *  Constructor
     *  @param  module
     */
    ShowTemplateFunction(llvm::Module *module);
    
    /**
     *  Destructor
     */
    virtual ~ShowTemplateFunction();
};

/**
 *  End namespace
 */
}}

