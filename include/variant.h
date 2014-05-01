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
class Variant : public Value
{
private:
    /**
     *  The underlying value
     *  @var std::shared_ptr<Value>
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
     *  Convert the value to a string
     *  @return const char *
     */
    virtual const char *toString()
    {
        return _value->toString();
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric()
    {
        return _value->toNumeric();
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean()
    {
        return _value->toBoolean();
    }

    /**
     *  Get access to a member value
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Value
     */
    virtual Value *member(const char *name, size_t size)
    {
        return _value->member(name, size);
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount()
    {
        return _value->memberCount();
    }

    /**
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Value *member(int position)
    {
        return _value->member(position);
    }

    /**
     *  Get access to the key at a certain position
     *  @param position
     *  @return The name of the key at position or nullptr otherwise
     */
    virtual Value *key(int position)
    {
        return _value->key(position);
    }

    /**
     *  String length of the variable
     *
     *  @return size_t
     */
    virtual size_t size()
    {
        return _value->size();
    }
};

/**
 *  End namespace
 */
}
