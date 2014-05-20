/**
 *  Base64encode.h
 *
 *  Built-in "|base64_encode" modifier
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
class Base64EncodeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Base64EncodeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(const Variant &input, const SmartTpl::Parameters &params) override
    {
        // Get the base64 encoder
        const Escaper *escaper = Escaper::get("base64");

        // Turn our input into a string
        std::string output(input.toString(), input.size());

        // Call encode and return the output
        return escaper->encode(output);
    }
};

/**
 *  End namespace
 */
}}