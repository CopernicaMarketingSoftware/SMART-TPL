/**
 *  Spacify.h
 *
 *  Built-in "|spacify" modifier
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
class SpacifyModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~SpacifyModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(Value *input, const SmartTpl::Parameters *params) override
    {
        // By default we use one space as a seperator
        std::string seperator(" ");

        // If we have parameters we have at least one, then this is our custom seperator
        if (params) seperator = std::string(params->get(0).toString(), params->get(0).size());

        // Let's just convert our input to a C string
        const char *str = input->toString();
        size_t len = input->size();

        // Init our output value
        std::string output;

        // Reserve the amount of space we'll need which is the original length * (length of seperator + 1)
        output.reserve(len * (seperator.length() + 1));
        for (size_t i = 0; i < len; ++i)
        {
            output += str[i];
            if (i != (len - 1)) output.append(seperator);
        }

        // Return the output
        return output;
    }
};

/**
 *  End namespace
 */
}}