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

#include <ctime>

namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class DateFormatModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~DateFormatModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // initialize our timestamp, empty string is 0 therefore current time
        time_t timestamp(input.toNumeric());

        // initialize the format
        std::string format = params.size() >= 1 ? params[0].toString() : "%b %e, %Y";


        char buffer[100];
        tm * timeinfo = localtime(&timestamp);

        // creating conversion from timestamp to formatted time string
        strftime(buffer, sizeof(buffer), format.c_str(), timeinfo);

        std::string time_str(buffer);

        return time_str;
    }
};

/**
 *  End namespace
 */
}}