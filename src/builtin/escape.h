/**
 *  Escape.h
 *
 *  Built-in "|escape:"html"" modifier
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
class EscapeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~EscapeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(Value *input, const SmartTpl::Parameters *params) override
    {
        // We default to the html encoder
        std::string encoder("html");

        // But if we have at least 1 parameter the first argument is our encoding
        if (params) encoder = params->get(0).toString();

        const Escaper *escaper = Escaper::get(encoder);

        // Turn our input into a string
        std::string output(input->toString(), input->size());

        // Call encode and return the output
        return escaper->encode(output);
    }
};

/**
 *  End namespace
 */
}}