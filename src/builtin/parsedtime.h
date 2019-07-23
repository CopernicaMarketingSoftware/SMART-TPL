/**
 *  ParsedTime.h
 *
 *  Class for parsing a timestamp. This is essentially a wrapper around
 *  timelib.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2019 Copernica BV
 */
 
/**
 *  Begin of namespace 
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class ParsedTime
{
private:
    /**
     *  Internal helper class for the timezone
     */
    class Timezone
    {
    private:
        /**
         *  Store information about utc timezone
         *  @var timelib_tzinfo
         */
        timelib_tzinfo *_info = nullptr;
    
    public:
        /**
         *  Constructor
         */
        Timezone()
        {
            // dummy error code
            int error;
            
            // get utc timezone information
            _info = timelib_parse_tzfile((char *) "UTC", timelib_builtin_db(), &error);
        }
        
        /**
         *  No copying
         *  @param  that
         */
        Timezone(const Timezone &that) = delete;
        
        /**
         *  Destructor
         */
        virtual ~Timezone()
        {
            // destruct timezone-info
            timelib_tzinfo_dtor(_info);
        }

        /**
         *  Get the internal representation
         *  @return timelib_tzinfo *
         */
        const timelib_tzinfo *internal() const { return _info; }
        
        /**
         *  Cast to the internal structure
         *  @return timelib_tzinfo *
         */
        operator const timelib_tzinfo * () const { return _info; }
    };

    /**
     *  The actual time that was parsed
     *  @var timelib_time
     */
    timelib_time *_time = nullptr;
    
    /**
     *  Errors that accured while parsing
     *  @var timelib_error_container
     */
    timelib_error_container *_errors = nullptr;
    
    /**
     *  Get the internal representation
     *  @return timelib_time *
     */
    const timelib_time *internal() const { return _time; }
    
    /**
     *  Cast to the internal representation
     *  @return timelib_time *
     */
    operator const timelib_time * () const { return _time; }
    
    
private:
    /**
     *  Constructor to get the current time
     *  @param  timezone        Timezone info
     */
    ParsedTime(const Timezone &timezone) : _time(timelib_time_ctor()) 
    {
        // set timezone 
        timelib_set_timezone(_time, (timelib_tzinfo *)timezone.internal());

        // create unix timestamp from current time
        timelib_unixtime2gmt(_time, time(nullptr));
    }

    /**
     *  Constructor to parse a time-string
     *  @param  timezone        Timezone info
     *  @param  input           the input string
     *  @param  size            size of the input string
     */
    ParsedTime(const Timezone &timezone, const char *input, size_t size) :
        _time(timelib_strtotime((char *)input, size, &_errors, timelib_builtin_db(), timelib_parse_tzfile))
    {
        // we also ask for the current time
        ParsedTime current(timezone);
        
        // to allow relative times, fill in the blanks in the parsed time
        timelib_fill_holes(_time, (timelib_time *)current.internal(), TIMELIB_NO_CLONE);

        // update the utc timestamp in the parsed time object
        timelib_update_ts(_time, (timelib_tzinfo *)timezone.internal());
    }

public:
    /**
     *  Constructor
     *  Note that this object does not throw on error, you must use the cast-to-bool
     *  operator to check if the parsing succeeded
     *  @param  input           the input string
     *  @param  size            size of the input string
     */
    ParsedTime(const char *input, size_t size) : 
        ParsedTime(Timezone{}, input, size) {}
        
    /**
     *  Constructor
     *  Note that this object does not throw on error, you must use the cast-to-bool
     *  operator to check if the parsing succeeded
     *  @param  input           the input string
     */
    ParsedTime(const char *input) : 
        ParsedTime(input, strlen(input)) {}

    /**
     *  No copying
     *  @param  that
     */
    ParsedTime(const ParsedTime &that) = delete;
    
    /**
     *  Destructor
     */
    virtual ~ParsedTime()
    {
        // destruct the time
        timelib_time_dtor(_time);
        
        // nothing else to destruct if there are no errors
        if (_errors == nullptr) return;
        
        // if we also have error, we destruct them too
        timelib_error_container_dtor(_errors);
    }
    
    /**
     *  Cast to boolean: is the object in a valid state?
     *  @return bool
     */
    operator bool () const 
    {
        // do we have an errors object?
        if (_errors == nullptr) return true;

        // if there are no errors or warnings
        return _errors->warning_count == 0 && _errors->error_count == 0;
    }
    
    /**
     *  Negate operator
     *  @return bool
     */
    bool operator! () const 
    {
        // do we have an errors object?
        if (_errors == nullptr) return false;

        // if there are errors or warnings
        return _errors->warning_count > 0 || _errors->error_count > 0;
    }
    
    /**
     *  Cast to a timestamp 
     *  @return time_t
     */
    operator time_t () const
    {
        return _time ? _time->sse : 0;
    }
};

/**
 *  End of namespace
 */
}


