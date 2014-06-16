/**
 *  Trim.h
 *
 *  Built-in "|trim:\"to_trim characters\"" modifier
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
class TrimModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~TrimModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // initialize our characters to trim
        std::string to_trim(" \t\n\r\0\x0B");
        if (params.size() >= 1) to_trim = params[0].toString();

        // initialize our output
        std::string output(input.toString());

        // First we trim the left side
        size_t i = output.find_first_not_of(to_trim);

        // If the output of find_first_not_of is 0 it really just means there is nothing to trim at this side
        if (i != 0)
        {
            if (i != std::string::npos) output.erase(0, i);
            else output.clear();
        }

        // Now let's trim the right side
        i = output.find_last_not_of(to_trim);

        if (i + 1 != output.length())
        {
            if (i != std::string::npos) output.erase(i + 1, std::string::npos);
            else output.clear();
        }

        // Return the output
        return output;
    }
};

/**
 *  End namespace
 */
}}