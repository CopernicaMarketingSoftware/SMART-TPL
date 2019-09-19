/**
 *  MapValue.h
 *
 *  A SmartTpl::Value which represents a map with VariantValues
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
class MapValue : public Value
{
private:
    /**
     *  The actual vector
     */
    std::map<std::string, VariantValue> _value;

public:
    /**
     *  Constructors
     */
    MapValue() : _value() {};
    MapValue(const std::map<std::string, VariantValue>& value) : _value(value) {};
    MapValue(std::map<std::string, VariantValue>&& value) : _value(std::move(value)) {};
    MapValue(const std::initializer_list<std::map<std::string, VariantValue>::value_type>& value) : _value(value) {};

    /**
     *  Destructor
     */
    virtual ~MapValue() {};

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override
    {
        return "";
    }

    /**
     *  Convert the variable to an integer value
     *  @return numeric
     */
    virtual integer_t toNumeric() const override
    {
        return 0;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        return !_value.empty();
    }

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const override
    {
        return 0.0;
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const override
    {
        return _value.size();
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
        // look for a value with name
        auto iter = _value.find(std::string(name, size));

        // found it? return it
        if (iter != _value.end()) return iter->second;

        // didn't see it? :( let's just return nullptr then
        return nullptr;
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual VariantValue member(size_t position) const override
    {
        // create string from position
        std::string key(std::to_string(position));

        // pass on
        return member(key.data(), key.size());
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return VariantValue
     */
    virtual VariantValue member(const Value &position) const override
    {
        // get string representation of the position
        auto key = position.toString();

        // pass on
        return member(key.data(), key.size());
    }

    /**
     *  Use this value as index of another parent value
     *  @param  value       the value in which to look for this key
     *  @return VariantValue
     */
    virtual VariantValue lookupIn(const Value &value) const override
    {
        // we can not use a map to access another variable
        return nullptr;
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr if you don't want to be able to iterate
     *  over your type
     *
     *  @return Newly allocated Iterator
     */
    virtual Iterator *iterator() const override;

    /**
     *  A few rather basic inserters to expand your map later on
     */
    template<typename ...Args>
    void insert(const std::string &key, Args&&... args) { _value.insert(std::make_pair(key, args...)); };
    template<typename ...Args>
    void insert(std::string &&key, Args&&... args) { _value.insert(std::make_pair(std::move(key), args...)); };
};

/**
 *  End namespace
 */
}
