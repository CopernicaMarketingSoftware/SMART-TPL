/**
 *  Truncate.h
 *
 *  Built-in "|truncate:80:"..."" modifier
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
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // init our default settings
        int length = 80;
        std::string etc("...");
        bool break_words = false;

        // Let's parse our parameters
        if (params.size() >= 1)
        {
            // Turn the first parameter into a numeric value
            length = params[0].toInteger();

            // If they requested a length of 0 the output will be "" no matter what
            if (length == 0) return "";

            // Turn the second parameter into the etc field
            if (params.size() >= 2) etc = params[1].toString();

            // Turns the third parameter into the break_words flag
            if (params.size() >= 3) break_words = params[2].toBoolean();
        }

        // initialize our output
        std::string output(input.toString());

        // If our input string is longer than our requested output we need to truncate it
        if (output.length() > length)
        {
            // Reduce the length by the length of etc, or itself whatever is shorter
            length -= (length < etc.size()) ? length : etc.size();

            if (!break_words)
            {
                // As we are not allowed to break words apply some regex magic
                // just like smarty does
                // https://code.google.com/p/smarty-php/source/browse/branches/Smarty2Dev/libs/plugins/modifier.truncate.php
                output = output.substr(0, length + 1);
                std::ostringstream stream;
                boost::regex_replace(std::ostream_iterator<char>(stream), output.begin(), output.end(), boost::regex("\\s+?(\\S+)?$"), "");
                output = stream.str();
            }

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
