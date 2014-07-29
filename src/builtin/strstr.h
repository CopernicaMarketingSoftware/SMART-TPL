/**
 *  Strstr.h
 *
 *  Built-in "|strstr:\"needle\":true" modifier
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
class StrStrModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~StrStrModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        if (params.size() >= 1)
        {
            // initialize the needle and the before_needle flag
            std::string needle(params[0].toString());
            bool before_needle = false;
            if (params.size() >= 2) before_needle = params[1].toBoolean();

            // initialize our haystack
            std::string haystack(input.toString());

            // Look for the needle in our haystack
            size_t pos = haystack.find_first_of(needle);

            // Return nothing (empty value) if we were unable to find the needle
            if (pos == std::string::npos) return nullptr;

            if (before_needle) return haystack.substr(0, pos);
            else return haystack.substr(pos);
        }

        // Return the input as we can't do strstr without at least a needle
        return input;
    }
};

/**
 *  End namespace
 */
}}