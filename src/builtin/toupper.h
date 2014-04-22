/**
 *  ToUpper.h
 *
 *  Built-in "|toupper" modifier
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class ToUpperModifier : public Modifier {
public:
    /**
     *  Destructor
     */
    virtual ~ToUpperModifier() {};
    
    /**
     *  Modify a value object
     *  @param  input
     *  @return Value
     */
    virtual Value* modify(Value* input) override 
    {
        // copy the entire string
        std::string output(input->toString(), input->size());
        
        // convert each character in it to upper case
        for (auto & c : output) c = toupper(c);
        
        // return it, wrapped in a new string object
        // @todo where is this deallocated?
        return new StringValue(output);
    };

    /**
     *  Modify a numeric value, and convert it into a variable value
     * 
     *  @param  input       Numeric value
     *  @return Value       Pointer to a new value object
     */
    virtual Value *modify(int value) override
    {
        // @todo implementation
        return nullptr;
    }
    
    /**
     *  Modify a string value, and convert it into a variable object
     * 
     *  @param  input       String input
     *  @param  size        Size of the string
     *  @return Value       Pointer to a new value object
     */
    virtual Value *modify(const char *input, size_t size) override
    {
        // @todo implementation
        return nullptr;
    }
};

/**
 *  End namespace
 */
}

