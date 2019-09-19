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
    virtual ~BoolValue() {}

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override
    {
        return (_value) ? "true" : "false";
    }

    /**
     *  Convert the variable to an integer value
     *  @return integer_t
     */
    virtual integer_t toNumeric() const override
    {
        return _value;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        return _value;
    }

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const override
    {
        return toNumeric();
    }

    /**
     *  Use this value as index of another parent value
     *  @param  value       the value in which to look for this key
     *  @return VariantValue
     */
    virtual VariantValue lookupIn(const Value &value) const override
    {
        // get member via integer
        return value.member(this->toInteger());
    }
};

/**
 *  End namespace
 */
}
