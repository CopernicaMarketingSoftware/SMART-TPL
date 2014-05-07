/**
 *  ToUpper.h
 *
 *  Built-in "|toupper" modifier
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
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
     *  @param  params      Parameters used for this modification
     *  @return Variant
     */
    virtual Variant modify(Value *input, const Parameters *params) override
    {
        // copy the entire string
        std::string output(input->toString(), input->size());

        // convert all the characters to uppercase
        for (auto & c : output) c = toupper(c);

        // return it wrapped into a new StringValue
        return output;
    }
};

/**
 *  End namespace
 */
}

