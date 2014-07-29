/**
 *  Count_characters.h
 *
 *  Built-in "|count_characters" modifier
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
class CountCharactersModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~CountCharactersModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // By default we don't include whitespaces
        bool include_whitespaces = false;

        // If we have parameters we have at least one, this being the toggle for whitespaces/no whitespaces
        if (params.size() >= 1) include_whitespaces = params[0].toBoolean();

        // If we include whitespaces we might as well just return the size
        if (include_whitespaces) return (long) input.size();

        // Let's just convert our input to a C string
        std::string str = input.toString();

        // Init our output value
        numeric_t output = 0;
        for (auto c : str) {
            // Are we not a whitespace?
            if (!std::isspace(c)) ++output;
        }

        // Return the output
        return output;
    }
};

/**
 *  End namespace
 */
}}