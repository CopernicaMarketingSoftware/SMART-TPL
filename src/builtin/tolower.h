/**
 *  ToLower.h
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
class ToLowerModifier : public Modifier 
{
public:
    /**
     *  Destructor
     */
    virtual ~ToLowerModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @return Value
     */
    virtual Value *modify(Value *input) override 
    {
        // Simply call the toString() and the related size() method of Value
        // and pass them to the modify(const char*, size_t);
        return modify(input->toString(), input->size());
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
        // copy the entire string
        std::string output(input, size);

        // convert all the characters to lowercase
        for (auto & c : output) c = tolower(c);

        // return it wrapped into a new StringValue
        return new StringValue(output);
    }

    /**
     *  Clean up the values you created
     *  @param value        The value to clean up
     */
    virtual void cleanup(Value* value) override
    {
        delete value;
    }
};

/**
 *  End namespace
 */
}

