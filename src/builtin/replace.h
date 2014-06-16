/**
 *  Replace.h
 *
 *  Built-in "|replace:"\n":"<br />"" modifier
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
class ReplaceModifier : public Modifier
{
protected:
    /**
     *  Helper method to find and replace strings in the input buffer
     *  @param  input       The input string in which to search and replace
     *  @param  oldStr      The string to find and replace
     *  @param  newStr      The replacement string
     *  @return std::string It will return the modified input
     */
    std::string &replace(std::string &input, const std::string &oldStr, const std::string &newStr) const
    {
        size_t pos = 0;
        // As long as find doesn't return std::string::npos we found what we were looking for
        while ((pos = input.find(oldStr, pos)) != std::string::npos)
        {
            // Replace that what we were looking for with newStr
            input.replace(pos, oldStr.size(), newStr);
            pos += newStr.size();
        }
        return input;
    }

public:
    /**
     *  Destructor
     */
    virtual ~ReplaceModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // initialize our output
        std::string output(input.toString());

        // Check if we have at least 2 parameters
        if (params.size() >= 2)
        {
            // If we do use them to execute the replace
            output = replace(output, params[0].toString(), params[1].toString());

            // Return the modified output
            return output;
        }

        // Simply return the input
        return input;
    }
};

/**
 *  End namespace
 */
}}