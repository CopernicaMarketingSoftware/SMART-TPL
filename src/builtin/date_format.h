/**
 *  date_format.h
 *
 *  Built-in "|date_format" modifier
 *
 *  @author Tamas Elekes <tamas.elekes@copernica.com>
 *  @copyright 2018 Copernica BV
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
        // initialize our timestamp, if empty string the current time, epoch start time if invalid input
        time_t timestamp = input.toString().empty() ? time(0) : input.toNumeric();

        // initialize the format
        std::string format = params.size() >= 1 ? params[0].toString() : "%b %e, %Y";


        char buffer[100];
        tm timeinfo;

        // get the timestamp in UTC
        gmtime_r(&timestamp, &timeinfo);

        // creating conversion from timestamp to formatted time string
        strftime(buffer, sizeof(buffer), format.c_str(), &timeinfo);

        return (VariantValue) buffer;
    }
};

/**
 *  End namespace
 */
}}