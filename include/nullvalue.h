/**
 *  NullValue.h
 *
 *  A SmartTpl::Value which represents a nullptr
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
class NullValue : public Value
{
public:
    /**
     *  Constructors
     */
    NullValue() {}

    /**
     *  Destructor
     */
    virtual ~NullValue() {}

    /**
     *  Use this value as index of another parent value
     *  @param  value       the value in which to look for this key
     *  @return VariantValue
     */
    virtual VariantValue lookupIn(const Value &value) const override
    {
        // it makes no sense to use null to lookup inside another value
        return nullptr;
    }
};

/**
 *  End namespace
 */
}
