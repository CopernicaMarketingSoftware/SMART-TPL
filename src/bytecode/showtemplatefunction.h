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
    /**
     *  The actual LLVM function
     *  @var    llvm::Function
     */
    llvm::Function *_function;

public:
    /**
     *  Constructor
     *  @param  module
     */
    ShowTemplateFunction(llvm::Module *module) : _function = module->getFunction("show_template")
    {
        // do we already have the function?
        if (!_function)
        {
            // we are going to create the function
        //    _function = llvm::Function::create(_type, GlobalValue::ExternalLinkage, "show_template", module);
            
            // set the calling convention to a normal C function
        //    _function->setCallingConv(llvm::CallingConv::C);
        }
    }
    
    /**
     *  Destructor
     */
    virtual ~ShowTemplateFunction()
    {
        
    }
};

/**
 *  End namespace
 */
}}

