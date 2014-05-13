/**
 *  Variant.h
 *
 *  A simple value wrapper
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
 *
 *  @todo is it a good idea that a variant also implements the value
 *        interface? Inside the library we probably only want to work
 *        with real Value objects, and not the wrapped Variant ones.
 *
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
     *  @param value
     */
    Variant();
    Variant(std::nullptr_t value) : Variant() {};
    explicit Variant(bool value);
    Variant(const std::shared_ptr<Value> &value) : _value(value) {};
    Variant(const char *value);
    Variant(const char *value, size_t size);
    Variant(const std::string &value);
    Variant(numeric_t value);
    Variant(const Variant &copy) = default;

    /**
     *  Deconstructor
     */
    virtual ~Variant() {};

    /**
     *  Retrieve the underlying value object
     *  @return std::shared_ptr<Value>
     */
    const std::shared_ptr<Value> &value() const
    {
        return _value;
    }

    /**
     *  Cast operators to various types
     *  @return mixed
     */
    operator numeric_t() const { return toNumeric(); }
    operator const char * () const { return toString(); }
    operator bool() const { return toBoolean(); }

    /**
     *  Convert the value to a string
     *  @return const char *
     */
    virtual const char *toString() const override
    {
        return _value->toString();
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() const override
    {
        return _value->toNumeric();
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
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
    virtual Variant member(const char *name, size_t size) const override
    {
        return _value->member(name, size);
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() const override
    {
        return _value->memberCount();
    }

    /**
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Variant member(int position) const override
    {
        return _value->member(position);
    }

    /**
     *  Get access to the key at a certain position
     *  @param position
     *  @return The name of the key at position or nullptr otherwise
     */
    virtual Variant key(int position) const override
    {
        return _value->key(position);
    }

    /**
     *  String length of the variable
     *
     *  @return size_t
     */
    virtual size_t size() const override
    {
        return _value->size();
    }
};

/**
 *  End namespace
 */
}

