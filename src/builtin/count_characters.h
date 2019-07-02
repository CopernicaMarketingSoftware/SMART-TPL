/**
 *  Count_characters.h
 *
 *  Built-in "|count_characters" modifier
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
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // If we include whitespaces we might as well just return the size
        if (params.size() >= 1 && params[0].toBoolean()) return (int64_t) input.toString().size();

        // Let's just convert our input to a C string
        std::string str = input.toString();

        // Init our output value
        integer_t output = 0;
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
