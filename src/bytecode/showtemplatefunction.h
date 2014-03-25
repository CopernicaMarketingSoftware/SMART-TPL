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


    /**
     *  Get the type of the function
     *  @return FunctionType*
     */
    llvm::FunctionType *type(llvm::Module *module) const
    {
        // retrieve the void type, because that is the function return type
        auto *voidType = llvm::Type::getVoidTy(module->getContext());
        
        // construct a vector that holds the parameter information
        std::vector<llvm::Type*> args;
        
        // it has one argument, a void-pointer, for a reason I don't get the example
        // used a integer-type pointer, so we copy that here
        args.push_back(llvm::PointerType::get(llvm::IntegerType::get(module->getContext(), 8), 0));
        
        // create the function (the third parameter says that this is _not_ a vararg function
        return llvm::FunctionType::get(voidType, args, false);
    }

public:
    /**
     *  Constructor
     *  @param  module
     */
    ShowTemplateFunction(llvm::Module *module)
    {
        // we are going to create the function
        _function = llvm::Function::Create(type(module), llvm::GlobalValue::ExternalLinkage, "show_template", module);
        
        // set the calling convention to a normal C function
        _function->setCallingConv(llvm::CallingConv::C);
        
#if 0

        // attributes for parameter 1, and for the return value
        llvm::AttrBuilder p1Attr;
        llvm::AttrBuilder funcAttr;
        
        // set the attributes for param 1
        p1Attr.addAttribute(llvm::Attribute::ReadNone);
        p1Attr.addAttribute(llvm::Attribute::NoCapture);
        
        // set the parameters for the entire function (or for the return value?? 
        // not sure as this is copy-pasted code)
        funcAttr.addAttribute(llvm::Attribute::NoUnwind);
        funcAttr.addAttribute(llvm::Attribute::UWTable);

        // create a vector for all the attributes
        llvm::SmallVector<llvm::AttributeSet,4> attributes;
        
        // append the attributes
        attributes.push_back(llvm::AttributeSet::get(module->getContext(),  1U, p1Attr));
        attributes.push_back(llvm::AttributeSet::get(module->getContext(), ~0U, funcAttr));
        
        // set the attributes for the function
        _function->setAttributes(llvm::AttributeSet::get(module->getContext(), attributes));

#endif

//  
//
//   AttributeSet func_show_template_PAL;
//   {
//    SmallVector<AttributeSet, 4> Attrs;
//    AttributeSet PAS;
//     {
//      AttrBuilder B;
//      B.addAttribute(Attribute::ReadNone);
//      B.addAttribute(Attribute::NoCapture);
//      PAS = AttributeSet::get(mod->getContext(), 1U, B);
//     }
//    
//    Attrs.push_back(PAS);
//    {
//     AttrBuilder B;
//     B.addAttribute(Attribute::NoUnwind);
//     B.addAttribute(Attribute::UWTable);
//     PAS = AttributeSet::get(mod->getContext(), ~0U, B);
//    }
//   
//   Attrs.push_back(PAS);
//   func_show_template_PAL = AttributeSet::get(mod->getContext(), Attrs);
//   
//  }
//  func_show_template->setAttributes(func_show_template_PAL);
//


//
//        // vector of attributes that we're going to add to the function
//        llvm::SmallVector<llvm::AttributeSet, 4> attributes;
//
//        // we are going to build the attributes with the attribute builder
//        llvm::AttrBuilder builder;
//        
//        // append first attribute
//        attributes.push_back(llvm::AttributeSet::get(module->getContext(), ~0U, builder));
//        
//        // set the function attributes
//        _function->setAttributes(llvm::AttributeSet::get(module->getContext(), attributes));
//        
        

//    AttributeSet func_smarttpl_write_PAL;
//    {
//        SmallVector<AttributeSet, 4> Attrs;
//        AttributeSet PAS;
//        {
//            AttrBuilder B;
//            PAS = AttributeSet::get(mod->getContext(), ~0U, B);
//        }
// 
//        Attrs.push_back(PAS);
//        func_smarttpl_write_PAL = AttributeSet::get(mod->getContext(), Attrs);
//    }
//    func_smarttpl_write->setAttributes(func_smarttpl_write_PAL);


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
}

