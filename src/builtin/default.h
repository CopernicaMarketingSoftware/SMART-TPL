/**
 *  Default.h
 *
 *  Built-in "|default:"default value"" modifier
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
class DefaultModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~DefaultModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(Value *input, const SmartTpl::Parameters *params) override
    {
        // If the string size of our input is 0 that means that we are empty
        if (input->size() == 0)
        {
            if (params) return params->get(0).toString();
        }

        // Return the output
        return std::string(input->toString(), input->size());
    }
};

/**
 *  End namespace
 */
}}