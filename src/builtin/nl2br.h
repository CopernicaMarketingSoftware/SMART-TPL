/**
 *  Nl2br.h
 *
 *  Built-in "|nl2br" modifier
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
class Nl2brModifier : public ReplaceModifier
{
public:
    /**
     *  Destructor
     */
    virtual ~Nl2brModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // initialize our output
        std::string output(input.toString());

        // Replace the new lines with <br /> and return
        return replace(output, "\n", "<br />");
    }
};

/**
 *  End namespace
 */
}}