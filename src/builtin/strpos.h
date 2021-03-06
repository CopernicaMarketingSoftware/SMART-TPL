/**
 *  Strpos.h
 *
 *  Built-in "|strpos:\"needle"" modifier
 *
 *  @author Tamas Elekes <tamas.elekes@copernica.com>
 *  @copyright 2018 Copernica BV
 */

/**
 *  Dependencies
 */
#include <limits>

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class StrPosModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~StrPosModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {        
        if (params.size() >= 1)
        {
            // initialize the needle 
            std::string needle(params[0].toString());

            // initialize our haystack
            std::string haystack(input.toString());
            
            // Look for the needle in our haystack
            size_t pos = haystack.find(needle);
			
            // Return -1 if unable to find the needle
            if (pos == std::string::npos) return -1;

			// also return -1 if it is outside our indexable range
			if (pos > static_cast<size_t>(std::numeric_limits<int64_t>::max())) return -1;
			
			// return the position
			return static_cast<int64_t>(pos);
        }

        // Return the input as we can't do strpos without at least a needle
        throw NoModification();
    }
};

/**
 *  End namespace
 */
}}
