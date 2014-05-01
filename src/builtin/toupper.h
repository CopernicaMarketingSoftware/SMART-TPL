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
     *  @return Variant
     */
    virtual Variant modify(Value* input) override
    {
        // Simply call the toString() and the related size() method of Value
        // and pass them to the modify(const char*, size_t);
        return modify(input->toString(), input->size());
    };

    /**
     *  Modify a numeric value, and convert it into a variable value
     * 
     *  @param  input       Numeric value
     *  @return Variant     A new value object
     */
    virtual Variant modify(int value) override
    {
        // @todo implementation
        return nullptr;
    }

    /**
     *  Modify a string value, and convert it into a variable object
     * 
     *  @param  input       String input
     *  @param  size        Size of the string
     *  @return Variant     A new value object
     */
    virtual Variant modify(const char *input, size_t size) override
    {
        // copy the entire string
        std::string output(input, size);

        // convert each character in it to upper case
        for (auto & c : output) c = toupper(c);

        // return it wraped in a new StringValue
        return output;
    }
};

/**
 *  End namespace
 */
}

