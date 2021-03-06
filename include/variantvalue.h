/**
 *  VariantValue.h
 *
 *  A wrapper around SmartTpl::Value which has constructors for most scalar types
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
class VariantValue : public Value
{
private:
    /**
     *  A regular Value object that we wrapped around
     */
    std::shared_ptr<Value> _value;

public:
    /**
     *  Constructors, one for most scalar types
     */
    VariantValue();
    VariantValue(std::nullptr_t value);
    VariantValue(bool value);
    VariantValue(int16_t value);
    VariantValue(int32_t value);
    VariantValue(int64_t value);
    VariantValue(double value);
    VariantValue(const char* value);
    VariantValue(const char* value, size_t len);
    VariantValue(std::string value);
    VariantValue(const std::vector<VariantValue>& value);
    VariantValue(std::vector<VariantValue>&& value);
    VariantValue(const std::initializer_list<VariantValue>& value);
    VariantValue(const std::map<std::string, VariantValue>& value);
    VariantValue(std::map<std::string, VariantValue>&& value);
    VariantValue(const std::initializer_list<std::map<std::string, VariantValue>::value_type>& value);

    /**
     *  Constructor to wrap around your own Value objects
     */
    VariantValue(const std::shared_ptr<Value> &value) : _value(value) {};

    /**
     *  Do not allow us to create this directly from a Value*!
     */
    VariantValue(const Value *value) = delete;
    VariantValue(Value *value) = delete;

    /**
     *  Copy and move constructors
     */
    VariantValue(const VariantValue &that) : _value(that._value) {}
    VariantValue(VariantValue &&that) : _value(std::move(that._value)) {}

    /**
     *  Destructor
     */
    virtual ~VariantValue() {};

    /**
     *  If this type was used in an arithmetric operation, should it then be
     *  treated as a floating point number, or as a regular integer?
     *  @return bool
     */
    virtual bool arithmeticFloat() const override { return _value->arithmeticFloat(); }

    /**
     *  Assignment operators
     */
    VariantValue& operator=(std::nullptr_t value);
    VariantValue& operator=(bool value);
    VariantValue& operator=(int16_t value);
    VariantValue& operator=(int32_t value);
    VariantValue& operator=(int64_t value);
    VariantValue& operator=(double value);
    VariantValue& operator=(const char* value);
    VariantValue& operator=(std::string value);
    VariantValue& operator=(const std::vector<VariantValue>& value);
    VariantValue& operator=(std::vector<VariantValue>&& value);
    VariantValue& operator=(const std::initializer_list<VariantValue>& value);
    VariantValue& operator=(const std::map<std::string, VariantValue>& value);
    VariantValue& operator=(std::map<std::string, VariantValue>&& value);
    VariantValue& operator=(const std::initializer_list<std::map<std::string, VariantValue>::value_type>& value);
    VariantValue& operator=(const std::shared_ptr<Value> &value) { _value = value; return *this; }
    VariantValue& operator=(const VariantValue &value) { _value = value._value; return *this; }
    VariantValue& operator=(VariantValue &&value) { _value = std::move(value._value); value._value = nullptr; return *this; }

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override
    {
        // return the toString of the underlying Value
        return _value->toString();
    }

    /**
     *  Convert the variable to a numeric value
     *  @return integer_t
     */
    virtual integer_t toNumeric() const override
    {
        // return the toNumeric of the underlying Value
        return _value->toNumeric();
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        // return the toBoolean of the underlying Value
        return _value->toBoolean();
    }

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const override
    {
        // return the toDoubleO of the underlying Value
        return _value->toDouble();
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const override
    {
        // return the memberCount() of the underlying Value
        return _value->memberCount();
    }

    /**
     *  Get access to a member value
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Variant
     *
     */
    virtual VariantValue member(const char *name, size_t size) const override
    {
        // return the member(const char*, size_t) of the underlying Value
        return _value->member(name, size);
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual VariantValue member(size_t position) const override
    {
        // return the member(size_t) of the underlying Value
        return _value->member(position);
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return VariantValue
     */
    virtual VariantValue member(const Value &position) const override
    {
        // return the member(Value) of the underlying Value
        return _value->member(position);
    }

    /**
     *  Use this value as index of another parent value
     *  @param  value       the value in which to look for this key
     *  @return VariantValue
     */
    virtual VariantValue lookupIn(const Value &value) const override
    {
        // pass on to lookupIn method of underlying value
        return _value->lookupIn(value);
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr if you don't want to be able to iterate
     *  over your type
     *
     *  @return Newly allocated Iterator
     */
    virtual Iterator *iterator() const override
    {
        // return the iterator of the underlying Value
        return _value->iterator();
    }

    /**
     *  Equals and not equals to operators
     */
    bool operator==(const VariantValue &that) const { return _value == that._value; }
    bool operator!=(const VariantValue &that) const { return !(*this == that); }
};

/**
 *  End namespace
 */
}
