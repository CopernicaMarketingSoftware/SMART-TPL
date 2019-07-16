/**
 *  date_format.h
 *
 *  Built-in "|date_format" modifier
 *
 *  @author Tamas Elekes <tamas.elekes@copernica.com>
 *  @copyright 2018 - 2019 Copernica BV
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
     *  Helper method to turn a datetime formatted by the user into a variant value
     *  according to the preferred formatting
     *  @param  time
     *  @param  params
     *  @return VariantValue
     *  @throws false
     */
    static VariantValue process(const char *datetime, const SmartTpl::Parameters &params)
    {
        // possible formats
        const char *formats[] = {
            "%Y-%m-%d %H:%M:%S",            // 2013-03-13 12:50:00
            "%a, %d %b %Y %H:%M:%S GMT",    // Sun, 06 Nov 1994 08:49:37 GMT  ; RFC 822, updated by RFC 1123
            "%A, %d-%b-%y %H:%M:%S GMT",    // Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036
            "%a %b %e %H:%M:%S %Y",         // Sun Nov  6 08:49:37 1994       ; ANSI C's asctime() format
            "%Y-%m-%d",                     // 2013-03-13
            nullptr
        };
        
        // loop through the formats
        for (int i=0; formats[i]; ++i)
        {
            // result variable
            struct tm tm;
            
            // set everything to zero otherwise valgrind complains
            memset(&tm, 0, sizeof(struct tm));

            // try parsing the string
            const char *result = strptime(datetime, formats[i], &tm);
            
            // proceed
            if (!result || strlen(result) > 0) continue;
            
            // found a match
            return process(mktime(&tm) - timezone, params);
        }
        
        // was the current time supplied?
        if (strcasecmp(datetime, "now") == 0) return process(time(nullptr), params);

        // try to parse the datetime as a relative interval
        return processRelative(datetime, params);
    }

    /**
     *  Helper function to process relative date intervals (like '+1 days')
     *  @param  time
     *  @param  params
     *  @return VariantValue
     *  @throws false
     */
    static VariantValue processRelative(const char *datetime, const SmartTpl::Parameters &params)
    {
        // is it tomorrow?
        if (strcasecmp(datetime, "tomorrow") == 0) return process(time(nullptr) + (24 * 60 * 60), params);

        // nothing matches
        throw false;
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

