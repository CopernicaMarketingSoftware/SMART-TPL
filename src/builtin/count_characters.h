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
    virtual Variant modify(Value *input, const SmartTpl::Parameters *params) override
    {
        // By default we don't include whitespaces
        bool include_whitespaces = false;

        // If we have parameters we have at least one, this being the toggle for whitespaces/no whitespaces
        if (params) include_whitespaces = params->get(0).toBoolean();

        // Let's just convert our input to a C string
        const char *str = input->toString();
        size_t len = input->size();

        // Init our output value
        numeric_t output = 0;
        for (size_t i = 0; i < len; ++i)
        {
            // Are we a whitespace?
            if (std::isspace(str[i]))
            {
                // Yes we are, should we include whitespaces?
                if (include_whitespaces) ++output;
            }
            else
            {
                ++output;
            }
        }

        // Return the output
        return output;
    }
};

/**
 *  End namespace
 */
}}