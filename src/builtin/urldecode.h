/**
 *  Urldecode.h
 *
 *  Built-in "|urldecode" modifier
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
class UrldecodeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~UrldecodeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // Get the url encoder
        const Escaper *escaper = Escaper::get("url");

        // Turn our input into a string
        std::string output(input.toString());

        // Call encode and return the output
        return escaper->decode(output);
    }
};

/**
 *  End namespace
 */
}}