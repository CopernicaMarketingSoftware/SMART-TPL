/**
 *  Urlencode.h
 *
 *  Built-in "|urlencode" modifier
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
class UrlencodeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~UrlencodeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(const Variant &input, const SmartTpl::Parameters &params) override
    {
        // Get the url encoder
        const Escaper *escaper = Escaper::get("url");

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