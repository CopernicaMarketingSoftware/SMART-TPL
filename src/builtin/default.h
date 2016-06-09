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
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
		// convert input to a string
		auto value = input.toString();
		
		// leap out on non-empty strings
		if (!value.empty()) throw NoModification();
		
        // input was empty, return the default that was passed as parameter
		if (params.size() >= 1) return params[0].toString();
		
        // no parameter was given, strange
        throw NoModification();
    }
};

/**
 *  End namespace
 */
}}
