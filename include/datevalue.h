/**
 *  DateValue.h
 *
 *  Class that represents a date variable
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class DateValue : public Value
{
private:
    /**
     *  The date printing format
     *  @var    std::string
     */
    const std::string _format;

    /**
     *  Buffer that will hold the current output
     */
    std::string _buffer;

    /**
     *  Put the current date/time in the _buffer
     */
    void initializeDate()
    {
        // Get the current time
        std::time_t time = std::time(NULL);

        // Convert it to our local time
        std::tm *timeinfo = std::localtime(&time);

        // Print it into _buffer using strftime
        // http://en.cppreference.com/w/cpp/chrono/c/strftime
        std::size_t len = std::strftime(&_buffer[0], _buffer.capacity(), _format.c_str(), timeinfo);
        while (len == 0)
        {
            // if strftime failed increase the buffer capacity and try again
            _buffer.reserve(_buffer.capacity() * 2);
            len = std::strftime(&_buffer[0], _buffer.capacity(), _format.c_str(), timeinfo);
        }
    }

public:
    /**
     *  Constructor
     *  @param format The format in which the date should be represented
     *                an empty format is undefined behavior and will throw for
     *                documentation regarding the format please head over to
     *                http://en.cppreference.com/w/cpp/chrono/c/strftime
     */
    DateValue(const std::string &format)
    : _format(format) {
        _buffer.reserve(_format.size());
        if (_format.empty()) throw std::runtime_error("A DateValue with an empty format is undefined");
    }

    /**
     *  Destructor
     */
    virtual ~DateValue() {}

    /**
     *  Convert the variable to a string
     *  @return const char *
     */
    virtual const char *toString() override
    {
        // Put the current date/time in our buffer
        initializeDate();

        // return the buffer as a C String
        return _buffer.c_str();
    }

    /**
     *  Returns the current unix timestamp
     *  @return numeric
     */
    virtual numeric_t toNumeric() override
    {
        return time(NULL);
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() override
    {
        return false;
    }

    /**
     *  Get access to a member variable
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Value
     */
    virtual Value *member(const char *name, size_t size) override
    {
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() override
    {
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Value *member(int position) override
    {
        return nullptr;
    }

    /**
     *  Get access to the key at a certain position
     *  @param position
     *  @return The name of the key at position or nullptr otherwise
     */
    virtual Value *key(int position) override
    {
        return nullptr;
    }

    /**
     *  String length of the variable
     *
     *  @return int
     */
    virtual size_t size() override
    {
        // Put the current date/time in the buffer
        initializeDate();

        // Returns the size of the buffer
        return _buffer.size();
    }

    /**
     *  Method used to get a instance of this value
     */
    virtual Variant cache() override
    {
        return Variant();
    }
};

/**
 *  End namespace
 */
}