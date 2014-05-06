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
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(Value *input, const Parameters *params) override
    {
        // copy the entire string
        std::string output(input->toString(), input->size());

        // convert all the characters to lowercase
        for (auto & c : output) c = tolower(c);

        // return it wrapped into a new StringValue
        return output;
    }
};

/**
 *  End namespace
 */
}

