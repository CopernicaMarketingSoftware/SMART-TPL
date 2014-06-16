/**
 *  VariantValue.h
 *
 *  A wrapper for VARIANT-CPP that complies with the SmartTpl::Value
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
class VariantValue : public Value
{
private:
    /**
     *  The Variant::Value from VARIANT-CPP that we are wrapping around
     */
    std::shared_ptr<Variant::Value> _value;

public:
    /**
     *  Constructors, these basically match with all the constructors from Variant::Value
     */
    VariantValue() : _value(new Variant::Value()) {}
    VariantValue(std::nullptr_t value) : _value(new Variant::Value(nullptr)) {}
    VariantValue(bool value) : _value(new Variant::Value(value)) {}
    VariantValue(int value) : _value(new Variant::Value(value)) {}
    VariantValue(long value) : _value(new Variant::Value(value)) {}
    VariantValue(double value) : _value(new Variant::Value(value)) {}
    VariantValue(const char* value) : _value(new Variant::Value(value)) {}
    VariantValue(const char* value, size_t len) : _value(new Variant::Value(value, len)) {}
    VariantValue(const std::string& value) : _value(new Variant::Value(value)) {}
    VariantValue(std::string&& value) : _value(new Variant::Value(std::move(value))) {}
    VariantValue(const std::vector<Variant::Value>& value) : _value(new Variant::Value(value)) {}
    VariantValue(std::vector<Variant::Value>&& value) : _value(new Variant::Value(std::move(value))) {}
    VariantValue(const std::initializer_list<Variant::Value>& value) : _value(new Variant::Value(value)) {}
    VariantValue(const std::map<std::string, Variant::Value>& value) : _value(new Variant::Value(value)) {}
    VariantValue(std::map<std::string, Variant::Value>&& value) : _value(new Variant::Value(value)) {}
    VariantValue(const std::initializer_list<std::map<std::string, Variant::Value>::value_type>& value) : _value(new Variant::Value(value)) {}

    VariantValue(const Variant::Value& value) : _value(new Variant::Value(value)) {}
    VariantValue(const VariantValue &that) : _value(that._value) {}

    /**
     *  Destructor
     */
    virtual ~VariantValue() {};

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override { return *_value; };

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() const override { return (numeric_t) *_value; };

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override { return (bool) *_value; };

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
        return (*_value)[name].value();
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const override
    {
        return _value->size();
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual VariantValue member(size_t position) const override
    {
        return (*_value)[position].value();
    }

    /**
     *  Get access to the key at a certain position
     *  @param  position     Position of the key we want to retrieve
     *  @return Variant      Variant object, probably a string
     */
    virtual VariantValue key(size_t position) const override
    {
        // In case we're a vector we'll just return the position as our key
        if (_value->type() == Variant::ValueType::ValueVectorType) return std::to_string(position);

        // If we're out of bounds just return VariantValue()
        if (position >= memberCount()) return nullptr;

        if (_value->type() == Variant::ValueType::ValueMapType)
        {
            // get the iterator of the underlying map
            auto iter = ((std::map<std::string, Variant::Value>) *_value).begin();

            // advance it by position
            std::advance(iter, position);

            // return the Value in the iterator
            return iter->first;
        }

        // We shouldn't reach this, if we do return nullptr
        return nullptr;
    }

    /**
     *  String length of the variable
     *
     *  @return size_t
     */
    virtual size_t size() const override
    {
        std::string str = *_value;
        return str.size();
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr from here in case memberCount returns 0
     *  as this method won't ever get called in that case anyway.
     *
     *  @return Newly allocated Iterator
     */
    virtual Iterator *iterator() const override;

    /**
     *  Equals and not equals to operators
     */
    bool operator==(const VariantValue &that) const
    {
        return _value == that._value;
    }
    bool operator!=(const VariantValue &that) const { return !(*this == that); }
};

/**
 *  End namespace
 */
}