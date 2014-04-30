/**
 *  Variant.h
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
class Variant
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
    Variant(const char *value) : _value(new StringValue(value)) {};
    Variant(const char *value, size_t size) : _value(new StringValue(value, size)) {};
    Variant(const std::string &value) : _value(new StringValue(value)) {};
    Variant(numeric_t value) : _value(new NumericValue(value)) {};

    /**
     *  Deconstructor
     */
    virtual ~Variant() {};

    /**
     *  Value* operator, to convert this wrapper value to a Value*
     *  @internal
     */
    operator Value*() { return _value.get(); };
};

/**
 *  End namespace
 */
}