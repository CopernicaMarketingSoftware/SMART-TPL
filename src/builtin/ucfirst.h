/**
 *  Ucfirst.h
 *
 *  Built-in "|ucfirst" modifier
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
class UcFirstModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~UcFirstModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // initialize our output
        std::string output(input.toString(), input.size());

        // Turn the first character into the uppercase form
        output[0] = std::toupper(output[0]);

        // Replace the new lines with <br /> and return
        return output;
    }
};

/**
 *  End namespace
 */
}}