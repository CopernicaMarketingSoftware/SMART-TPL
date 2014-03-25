/**
 *  ExternalFunctions.h
 *
 *  The llvm function pointers to functions that are defined outside the
 *  module. These are functions that are already defined in the SmartTpl
 *  library, and that are used to call back to the template library.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class ExternalFunctions
{
private:
    /**
     *  Function to generate output
     *  @var    SmartTplWriteFunction
     */
    WriteFunction _write;
    
public:
    /**
     *  Constructor
     *  @param  module
     */
    ExternalFunctions(llvm::Module *module) :
        _write(module) {}
    
    /**
     *  Destructor
     */
    virtual ~ExternalFunctions() {}
};

/**
 *  End namespace
 */
}
