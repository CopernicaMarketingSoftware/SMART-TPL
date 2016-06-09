/**
 *  Strlen.h
 *
 *  Built-in "|strlen" modifier
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
class StrlenModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~StrlenModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // Simply return the length of the toString() method
        return (int64_t) input.toString().size();
    }
};

/**
 *  End namespace
 */
}}