/**
 *  DoubleValue.h
 *
 *  A SmartTpl::Value which represents a floating point type (double)
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
class DoubleValue : public Value
{
private:
    /**
     *  The actual double
     */
    const double _value;

public:
    /**
     *  Constructors
     */
    DoubleValue(double value) : _value(value) {}
    DoubleValue(float value) : _value(value) {};

    /**
     *  Destructor
     */
    virtual ~DoubleValue() {};

    /**
     *  If this type was used in an arithmetric operation, should it then be
     *  treated as a floating point number, or as a regular integer?
     *  @return bool
     */
    virtual bool arithmeticFloat() const override { return true; }

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override
    {
        // create buffer
        char buffer[512];

        // format string
        size_t written = snprintf(buffer, 512, "%.5f", _value);

        // Remove trailing zeroes
        while (buffer[written - 1] == '0') written--;

        // Round number?
        if (buffer[written - 1] == '.') written--;

        // Create string object
        return std::string(buffer, written);
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
        return _value;
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
