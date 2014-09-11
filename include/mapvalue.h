/**
 *  MapValue.h
 *
 *  A SmartTpl::Value which represents a map with VariantValues
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
    std::string toString() const override
    {
        return "";
    };

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    numeric_t toNumeric() const override
    {
        return 0;
    };

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    bool toBoolean() const override
    {
        return false;
    };

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    double toDouble() const override
    {
        return 0.0;
    };

    /**
     *  Get access to a member value
     *
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Variant
     *
     */
    VariantValue member(const char *name, size_t size) const override
    {
        // look for a value with name
        auto iter = _value.find(std::string(name, size));

        // found it? return it
        if (iter != _value.end()) return iter->second;

        // didn't see it? :( let's just return nullptr then
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    size_t memberCount() const override
    {
        return _value.size();
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    VariantValue member(size_t position) const override
    {
        // if position is higher than the amount of items in the map we just return nullptr
        if (position >= memberCount()) return nullptr;

        // get an iterator to the begin of the map
        auto iter = _value.begin();

        // advance it by position
        std::advance(iter, position);

        // return the value
        return iter->second;
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr from here in case memberCount returns 0
     *  as this method won't ever get called in that case anyway.
     *
     *  @return Newly allocated Iterator
     */
    Iterator *iterator() const override;
};

/**
 *  End namespace
 */
}
