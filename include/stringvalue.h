/**
 *  StringValue.h
 *
 *  A SmartTpl::Value which represents a string (std::string)
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class StringValue : public Value
{
private:
    /**
     *  The actual string
     */
    const std::string _value;

public:
    /**
     *  Constructors
     */
    StringValue(const char* value) : _value(value) {}
    StringValue(const char* value, size_t len) : _value(value, len) {};
    StringValue(std::string value) : _value(std::move(value)) {};

    /**
     *  Destructor
     */
    virtual ~StringValue() {};

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override
    {
        return _value;
    };

    /**
     *  Convert the variable to a numeric value
     *  @return integer_t
     */
    virtual integer_t toNumeric() const override
    {
        try
        {
            return std::stoll(_value);
        }
        catch (...)
        {
            return 0;
        }
    };

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        // just like in php an empty string and a string containing "0" are false
        if (_value.empty()) return false;
        else if (_value == "0") return false;
        else return true;
    };

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const override
    {
        try
        {
            return std::stod(_value);
        }
        catch (...)
        {
            return 0.0;
        }
    }
};

/**
 *  End namespace
 */
}
