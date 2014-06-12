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
    mutable std::shared_ptr<Variant::Value> _value;

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

    /**
     *  Destructor
     */
    virtual ~VariantValue() {};

    /**
     *  Convert the value to a string
     *  @return const char *
     */
    virtual const char *toString() const { return ((std::string) *_value).c_str(); };

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() const { return (numeric_t) *_value; };

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const { return (bool) *_value; };

    /**
     *  Get access to a member value
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Variant
     *
     */
    virtual VariantValue member(const char *name, size_t size) const
    {
        return (*_value)[name].value();
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const
    {
        if (_value->type() == Variant::ValueType::ValueVectorType)
        {
            std::vector<Variant::Value> output = *_value;
            return output.size();
        }
        else if (_value->type() == Variant::ValueType::ValueMapType)
        {
            std::map<std::string, Variant::Value> output = *_value;
            return output.size();
        }

        // In case we aren't a map or a vector just return 0
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual VariantValue member(int position) const
    {
        // If we're out of bounds just return VariantValue()
        if (position < 0 || position >= memberCount()) return nullptr;

        if (_value->type() == Variant::ValueType::ValueVectorType)
        {
            std::vector<Variant::Value> vector = *_value;
            return vector[position];
        }
        else if (_value->type() == Variant::ValueType::ValueMapType)
        {
            // get the iterator of the underlying map
            auto iter = ((std::map<std::string, Variant::Value>) *_value).begin();

            // advance it by position
            std::advance(iter, position);

            // return the Value in the iterator
            return iter->second;
        }

        // We shouldn't reach this, but in case we do we'll just return nullptr
        return nullptr;
    }

    /**
     *  Get access to the key at a certain position
     *  @param  position     Position of the key we want to retrieve
     *  @return Variant      Variant object, probably a string
     */
    virtual VariantValue key(int position) const
    {
        // In case we're a vector we'll just return the position as our key
        if (_value->type() == Variant::ValueType::ValueVectorType) return position;

        // If we're out of bounds just return VariantValue()
        if (position < 0 || position >= memberCount()) return nullptr;

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
    virtual size_t size() const
    {
        return ((std::string) *_value).size();
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr from here in case memberCount returns 0
     *  as this method won't ever get called in that case anyway.
     *
     *  @return Newly allocated Iterator
     */
    virtual Iterator *iterator() const
    {
        // @todo
        return nullptr;
    }

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