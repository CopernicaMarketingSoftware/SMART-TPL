/**
 *  Base64decode.h
 *
 *  Built-in "|base64_decode" modifier
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
class Base64DecodeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Base64DecodeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // Get the base64 encoder
        const Escaper *escaper = Escaper::get("base64");

        // Turn our input into a string
        std::string output(input.toString());

        // Call decode and return the output
        return escaper->decode(output);
    }
};

/**
 *  End namespace
 */
}}