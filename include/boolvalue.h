/**
 *  BoolValue.h
 *
 *  A SmartTpl::Value which represents a boolean
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
class BoolValue : public Value
{
private:
    /**
     *  The actual boolean value
     */
    const bool _value;

public:
    /**
     *  Constructors
     */
    BoolValue(bool value) : _value(value) {}

    /**
     *  Destructor
     */
    virtual ~BoolValue() {};

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override
    {
        return (_value) ? "true" : "false";
    };

    /**
     *  Convert the variable to an integer value
     *  @return integer_t
     */
    virtual integer_t toNumeric() const override
    {
        return _value;
    };

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        return _value;
    };

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const override
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
    virtual VariantValue member(const char *name, size_t size) const override
    {
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const override
    {
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return Variant
     */
    virtual VariantValue member(size_t position) const override
    {
        return nullptr;
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
        return nullptr;
    }
};

/**
 *  End namespace
 */
}
