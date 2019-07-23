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
#include "parsedtime.h"

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
        // parse the time
        ParsedTime parsed(datetime);

        // If parsing was unsuccessful, throw so that the original string is kept
        if (!parsed) throw false;
        
        // was this a success? if not we use the current time
        return process(parsed, params);
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

