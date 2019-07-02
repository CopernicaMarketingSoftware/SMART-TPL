/**
 *  Substr.h
 *
 *  Built-in "|substr:5:5" modifier
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class SubStrModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~SubStrModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        if (params.size() >= 1)
        {
            // initialize our output
            std::string output(input.toString());

            // Turn the second parameter into the substr len parameter
            size_t len = std::string::npos;
            if (params.size() >= 2) len = params[1].toInteger();

            try
            {
                // Execute the substr method on output and return the output of it
                return output.substr(params[0].toInteger(), len);
            }
            catch (const std::out_of_range &error)
            {
                // In case this happens just fall through so we end up returning the input
            }
        }

        // Return the input as we can't do substr without parameters
        throw NoModification();
    }
};

/**
 *  End namespace
 */
}}
