/**
 *  NumericValue.h
 *
 *  A SmartTpl::Value which represents a numeric type (numeric_t)
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
class NumericValue : public Value
{
private:
    /**
     *  The actual numeric value
     */
    const numeric_t _value;

public:
    /**
     *  Constructors
     */
    NumericValue(int64_t value) : _value(value) {}
    NumericValue(int32_t value) : _value(value) {};

    /**
     *  Destructor
     */
    virtual ~NumericValue() {};

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    std::string toString() const override
    {
        return std::to_string(_value);
    };

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    numeric_t toNumeric() const override
    {
        return _value;
    };

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    bool toBoolean() const override
    {
        return _value;
    };

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    double toDouble() const override
    {
        return toNumeric();
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
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    size_t memberCount() const override
    {
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    VariantValue member(size_t position) const override
    {
        return nullptr;
    }

    /**
     *  Create a new iterator that allows you to iterate over the subvalues
     *  feel free to return nullptr from here in case memberCount returns 0
     *  as this method won't ever get called in that case anyway.
     *
     *  @return Newly allocated Iterator
     */
    Iterator *iterator() const override
    {
        return nullptr;
    }
};

/**
 *  End namespace
 */
}
