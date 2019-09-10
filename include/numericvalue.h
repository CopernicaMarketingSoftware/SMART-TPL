/**
 *  NumericValue.h
 *
 *  A SmartTpl::Value which represents a numeric type (integer_t)
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
class NumericValue : public Value
{
private:
    /**
     *  The actual numeric value
     *  @var integer_t
     */
    const integer_t _value;

public:
    /**
     *  Constructors
     */
    NumericValue(int64_t value) : _value(value) {}
    NumericValue(int32_t value) : _value(value) {};
    NumericValue(int16_t value) : _value(value) {};

    /**
     *  Destructor
     */
    virtual ~NumericValue() {}

    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override
    {
        return std::to_string(_value);
    }

    /**
     *  Convert the variable to a numeric value
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
