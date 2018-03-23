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
        
        // initialize the format
        std::string format = params.size() >= 1 ? params[0].toString() : "%b %e, %Y";

        // used to determine if the input is a formatted date string or unix timestamp
        tm input_timeinfo;

        // this timestamp will be formatted to the given format
        time_t timestamp;

        // try to parse the input as a formatted date string
        std::istringstream ss(input.toString().c_str());
        ss >> std::get_time(&input_timeinfo, "%Y-%m-%d %H:%M:%S");

        if (ss.fail())
            // if empty string the current time, epoch start time if invalid input
            timestamp = input.toString().empty() || input.toString() == "now" ? time(0) : input.toNumeric();
        else
            // make timestamp from time info
            timestamp = mktime(&input_timeinfo);

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