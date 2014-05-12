/**
 *  Truncate.h
 *
 *  Built-in "|truncate:80:"..."" modifier
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
 *  @todo Add support for break_words and middle just like smarty has
 *  https://code.google.com/p/smarty-php/source/browse/branches/Smarty2Dev/libs/plugins/modifier.truncate.php
 */
class TruncateModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~TruncateModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // init our default settings
        int length = 80;
        std::string etc("...");

        // Let's parse our parameters
        if (params.size() >= 1)
        {
            // Turn the first parameter into a numeric value
            length = params[0].toNumeric();

            // If they requested a length of 0 the output will be "" no matter what
            if (length == 0) return "";

            // Turn the second parameter into the etc field
            if (params.size() >= 2) etc = std::string(params[1].toString(), params[1].size());
        }

        // initialize our output
        std::string output(input.toString(), input.size());

        // If our input string is longer than our requested output we need to truncate it
        if (output.length() > length)
        {
            // Reduce the length by the length of etc, or itself whatever is shorter
            length -= (length < etc.size()) ? length : etc.size();

            // Return a substring of length, append etc and return it
            return output.substr(0, length) + etc;
        }
        else
        {
            // if it isn't we can just return it like this
            return output;
        }
    }
};

/**
 *  End namespace
 */
}}