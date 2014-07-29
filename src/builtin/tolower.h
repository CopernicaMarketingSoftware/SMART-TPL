/**
 *  ToLower.h
 *
 *  Built-in "|tolower" modifier
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
    VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // copy the entire string
        std::string output(input.toString());

        // convert all the characters to lowercase
        for (auto & c : output) c = std::tolower(c);

        // return it wrapped into a new StringValue
        return output;
    }
};

/**
 *  End namespace
 */
}}