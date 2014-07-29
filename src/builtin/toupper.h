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
namespace SmartTpl { namespace Internal {

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
    VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // copy the entire string
        std::string output(input.toString());

        // convert all the characters to uppercase
        for (auto & c : output) c = std::toupper(c);

        // return it wrapped into a new StringValue
        return output;
    }
};

/**
 *  End namespace
 */
}}