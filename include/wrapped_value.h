/**
 *  WrappedValue.h
 *
 *  A simple value wrapper purely available for lambda functions
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class WrappedValue
{
private:
    /**
     *  The underlying value
     */
    std::shared_ptr<Value> _value;
public:
    /**
     *  Constructor
     */
    WrappedValue(const char *value) : _value(new StringValue(value)) {};
    WrappedValue(const char *value, size_t size) : _value(new StringValue(value, size)) {};
    WrappedValue(const std::string &value) : _value(new StringValue(value)) {};
    WrappedValue(numeric_t value) : _value(new NumericValue(value)) {};

    /**
     *  Deconstructor
     */
    virtual ~WrappedValue() {};

    /**
     *  Value* operator, to convert this wrapper value to a Value*
     */
    operator Value*() { return _value.get(); };
};

/**
 *  End namespace
 */
}