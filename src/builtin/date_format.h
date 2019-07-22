/**
 *  date_format.h
 *
 *  Built-in "|date_format" modifier
 *
 *  @author     Tamas Elekes <tamas.elekes@copernica.com>
 *  @author     David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright  2018 - 2019 Copernica BV
 */

/**
 *  Dependencies
 */
#include <ctime>

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class DateFormatModifier : public Modifier
{
private:
    /**
     *  Helper method to turn a timestamp into a VariantValue
     *  @param  timestamp
     *  @param  format
     *  @return VariantValue
     *  @throws bool
     */
    static VariantValue process(time_t timestamp, const char *format)
    {
        // structure in which the time will be loaded
        struct tm timeinfo;

        // get the timestructure in UTC
        auto result = gmtime_r(&timestamp, &timeinfo);
        
        // if we failed to get the time we return the format
        if (result == nullptr) throw false;

        // buffer in which we're going to write the formatted time
        char buffer[256];
        
        // write the time into the buffer
        size_t size = strftime(buffer, sizeof(buffer), format, &timeinfo);
        
        // return the original timestamp
        if (size == 0) throw false;
        
        // expose the buffer
        return VariantValue(buffer, size);
    }

    /**
     *  Helper method to turn a timestamp into a VariantValue
     *  @param  timestamp
     *  @param  params
     *  @return VariantValue
     *  @throws bool
     */
    static VariantValue process(time_t timestamp, const SmartTpl::Parameters &params)
    {
        // use default format if nothing was specified
        if (params.size() == 0) return process(timestamp, "%b %e, %Y");
        
        // get the format supplied by the user as string
        std::string format = params[0].toString();
        
        // use this format
        return process(timestamp, format.c_str());
    }

    /**
     *  Helper function to process absolute and relative dates (like '+1 days')
     *  For this functionality, we invoke timelib (https://github.com/derickr/timelib)
     *  @param  time
     *  @param  params
     *  @return VariantValue
     *  @throws false
     */
    static VariantValue process(const char *datetime, const SmartTpl::Parameters &params)
    {
        // create storage variables
        timelib_time *parsed, *current;
        timelib_error_container *errors;
        
        // store information about utc timezone
        timelib_tzinfo *tzi_utc;

        // try to parse the provided time
        parsed = timelib_strtotime((char *)datetime, std::strlen(datetime), &errors, timelib_builtin_db(), timelib_parse_tzfile);

        // if we have warnings or errors, parsing the date was not succesful
        if (errors->warning_count || errors->error_count) 
        {
            // clean up timelib variables
            timelib_time_dtor(parsed);
            timelib_error_container_dtor(errors);

            // no success
            throw false;
        }

        // dummy error code storage
        int tz_error;

        // get utc timezone information
        tzi_utc = timelib_parse_tzfile((char *) "UTC", timelib_builtin_db(), &tz_error);

        // construct object for the current time
        current = timelib_time_ctor();
        
        // set timezone 
        timelib_set_timezone(current, tzi_utc);

        // create unix timestamp from current time
        timelib_unixtime2gmt(current, time(NULL));
    
        // to allow relative times, fill in the blanks in the parsed time
        timelib_fill_holes(parsed, current, TIMELIB_NO_CLONE);

        // update the utc timestamp in the parsed time object
        timelib_update_ts(parsed, tzi_utc);

        // get the timestamp
        time_t timestamp = parsed->sse;

        // clean up timelib variables
        timelib_time_dtor(parsed);
        timelib_time_dtor(current);
        timelib_error_container_dtor(errors);
        timelib_tzinfo_dtor(tzi_utc);

        // process the timestamp
        return process(timestamp, params);
    }

    
public:
    /**
     *  Destructor
     */
    virtual ~DateFormatModifier() = default;

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // get the input value
        std::string value = input.toString();
        
        // prevent exceptions if parsing or generating fails
        try
        {
            // if no input was given, we treat it as the current time
            if (value.size() == 0) return process(time(nullptr), params);
            
            // iterate over the value to see if the input only contains numbers
            for (size_t i = 0; i < value.size(); ++i)
            {
                // all is ok if we only see digits
                if (isdigit(value[i])) continue;
                
                // we saw a non-digit character, so we have to parse the date that is given as input
                return process(value.c_str(), params);
            }
            
            // value only contains numers, so we can treat it as timestamp
            return process(input.toInteger(), params);
        }
        catch (...)
        {
            // expose the input given by the user
            return VariantValue(value);
        }
    }
};

/**
 *  End namespace
 */
}}

