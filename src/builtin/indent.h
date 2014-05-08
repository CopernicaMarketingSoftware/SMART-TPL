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
 *  @todo Multiline support?
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
    virtual Variant modify(Value *input, const SmartTpl::Parameters *params) override
    {
        // Initialize the default settings
        int indents = 4;
        std::string character = " ";

        // if we have any parameters start parsing them
        if (params)
        {
            indents = params->get(0).toNumeric();

            // If we have at least 2 parameters use the second one as well
            if (params->size() >= 2) character = params->get(1).toString();
        }

        // initialize our output
        std::string output;

        // Append our indent character indent times
        for (int i = 0; i < indents; ++i) output.append(character);

        // Append the input and return the output
        return output.append(input->toString(), input->size());
    }
};

/**
 *  End namespace
 */
}}