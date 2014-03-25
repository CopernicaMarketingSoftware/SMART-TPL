/**
 *  WriteFunction.h
 *
 *  Class that is used for representing the extern smarttpl_write() function.
 *
 *  This is a function with the C signature:
 * 
 *      extern void smarttpl_write(const char *, unsigned int size);
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
class WriteFunction
{
private:
    /**
     *  The actual function
     *  @var    llvm::Function
     */
    llvm::Function *_function;

    /**
     *  The type of the function
     *  @return llvm::Type
     */
    llvm::FunctionType *type(llvm::Module *module) const
    {
        // the return value is void
        auto *voidType = llvm::Type::getVoidTy(module->getContext());
        
        // create vector with arguments
        std::vector<llvm::Type*> args;
        
        // there are two arguments, a const-char*, and an int
        // @todo why "32" ?????????
        args.push_back(llvm::PointerType::get(llvm::IntegerType::get(module->getContext(), 8), 0));
        args.push_back(llvm::IntegerType::get(module->getContext(), 32));
        
        // create the type (third parameter
        return llvm::FunctionType::get(voidType, args, false);
    }

public:
    /**
     *  Constructor
     *  @param  module
     */
    WriteFunction(llvm::Module *module)
    {
        // create the function
        _function = llvm::Function::Create(type(module), llvm::GlobalValue::ExternalLinkage, "smarttpl_write", module);

        // C calling convention
        _function->setCallingConv(llvm::CallingConv::C);

#if 0

        // we are going to build the attributes for the entire function
        llvm::AttrBuilder funcAttr;
        
        // the vector of all attributes
        llvm::SmallVector<llvm::AttributeSet,4> attributes;
        
        // set the attributes for the entire function
        attributes.push_back(llvm::AttributeSet::get(module->getContext(), ~0U, funcAttr));
        
        // set the attributes
        _function->setAttributes(llvm::AttributeSet::get(module->getContext(), attributes));
        
#endif
    }

    /**
     *  Destructor
     */
    virtual ~WriteFunction() {}


//AttributeSet func_smarttpl_write_PAL;
//{
// SmallVector<AttributeSet, 4> Attrs;
// AttributeSet PAS;
//  {
//   AttrBuilder B;
//   PAS = AttributeSet::get(mod->getContext(), ~0U, B);
//  }
// 
// Attrs.push_back(PAS);
// func_smarttpl_write_PAL = AttributeSet::get(mod->getContext(), Attrs);
// 
//}
//func_smarttpl_write->setAttributes(func_smarttpl_write_PAL);
    
    
};     
    
    
/**
 *  End namespace
 */
}

