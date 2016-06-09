/**
 *  Empty.h
 *
 *  Built-in "|empty" modifier
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
class EmptyModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~EmptyModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // if our member count is 0 we might be a string
        if (input.memberCount() == 0)
        {
            // as we might be a string we just cast to a string and return empty() of that
            std::string str = input.toString();
            return str.empty();
        }

        // if we get here then memberCount was clearly not 0, meaning we are not empty
        return false;
    }
};

/**
 *  End namespace
 */
}}