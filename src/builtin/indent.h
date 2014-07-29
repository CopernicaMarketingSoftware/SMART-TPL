/**
 *  Indent.h
 *
 *  Built-in "|indent:1:"\t"" modifier
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
class IndentModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~IndentModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // Initialize the default settings
        int indents = 4;
        std::string character = " ";

        // if we have any parameters start parsing them
        if (params.size() >= 1)
        {
            indents = params[0].toNumeric();

            // If we have at least 2 parameters use the second one as well
            if (params.size() >= 2) character = params[1].toString();
        }

        // initialize our output
        std::string output;

        std::string str = input.toString();
        output.reserve(str.size());

        // Build our final ident
        std::string indent;
        indent.reserve(indents * character.size());
        for (int i = 0; i < indents; ++i) indent.append(character);

        // prepend the indent to the output
        output.append(indent);

        // Loop through all the characters of our input
        for (auto c : str)
        {
            output += c;

            // everytime we hit a new line we append an indent
            if (c == '\n') output.append(indent);
        }

        // Return the output
        return output;
    }
};

/**
 *  End namespace
 */
}}