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
#include <regex>

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

        // is it yesterday?
        if (strcasecmp(datetime, "yesterday") == 0) return process(time(nullptr) - (24 * 60 * 60), params);

        // convert our buffer into a string
        std::string input(datetime);
        
        // we need a regex to match our interval
        std::regex interval("^(\\+|\\-)(\\d+)\\s+(second|minute|hour|day|week|month|year)[s]{0,1}$", std::regex_constants::icase);

        // store matches
        std::smatch matches;

        // do we have a match?
        if (std::regex_search(input, matches, interval))
        {
            // Get the current timestamp
            time_t current = time(nullptr);

            // Get the amount of time units to shift
            int shift = std::stoi(matches[2].str());

            // If we have a decrement, negate the shift
            if (strcasecmp(matches[1].str().data(), "-") == 0) shift *= -1;

            // Get the time unit to change
            const char *timeunit = matches[3].str().data(); 
            
            // Should we move seconds?
            if (strcasecmp(timeunit, "second") == 0) return process(current + shift, params);

            // Should we change minutes?
            if (strcasecmp(timeunit, "minute") == 0) return process(current + (shift * 60), params);

            // Should we add/remove hours?
            if (strcasecmp(timeunit, "hour") == 0) return process(current + (shift * 60 * 60), params);

            // Should we add / remove days?
            if (strcasecmp(timeunit, "day") == 0) return process(current + (shift * 60 * 60 * 24), params);

            // Should we add / remove weeks?
            if (strcasecmp(timeunit, "week") == 0) return process(current + (shift * 60 * 60 * 24 * 7), params);

            // If we are adding / removing months or years, we need a tm structure to calculate
            tm *time_tm = gmtime(&current);

            // Should we add / remove months?
            if (strcasecmp(timeunit, "month") == 0)
            {
                // calculate the new month value
                int month = time_tm->tm_mon + shift;
                int year = time_tm->tm_year;

                // make sure we're within boundaries
                if (std::abs(month) > 11)
                {
                    // since we're working with ints, the increment in years
                    // is the division of the months by 12, and the new month value
                    // is the remainder of that division
                    year += month / 12;
                    month = month % 12;
                }

                // make sure the number is positive
                if (month < 0)
                {
                    // add 12 months, and remove one year
                    year -= 1; 
                    month += 12;
                }

                // set the new values
                time_tm->tm_mon = month;
                time_tm->tm_year = year;
            }

            // Should we add / remove years
            if (strcasecmp(timeunit, "year") == 0)
            {
                // set new value in tm struct, make sure we're within boundaries
                time_tm->tm_year = std::min(0, time_tm->tm_year + shift);
            }

            // Recreate a timestamp from the structure and process it
            return process(mktime(time_tm), params);
        }

        // no match
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

