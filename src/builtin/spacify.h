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
    VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // By default we use one space as a seperator
        std::string seperator(" ");

        // If we have parameters we have at least one, then this is our custom seperator
        if (params.size() >= 1) seperator = params[0].toString();

        // some of these methods can throw quite hard, which very likely just means there's something wrong with the input
        try
        {
            // Let's just convert our input to a C string
            std::string str(input.toString());

            // Init our output value
            std::string output;

            // Reserve the amount of space we'll need which is the original length * (length of seperator + 1)
            output.reserve(str.size() * (seperator.length() + 1));

            for (auto c : str)
            {
                output += c;

                // append the seperator
                output.append(seperator);
            }

            // Simply erase the last seperator
            output.erase(output.size() - seperator.size());

            // Return the output
            return output;
        }
        catch (...)
        {
            // if we failed we simply return the original input
            return input;
        }
    }
};

/**
 *  End namespace
 */
}}