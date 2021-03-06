/**
 *  Callback.h
 *
 *  Specific implementation of the Value class, in which the implementation
 *  is done by a callback
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 - 2019 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 *  @note This class is NOT thread-safe.
 */
class CallbackValue : public Value
{
private:
    /**
     *  The function that can be called when a value needs to be retrieved
     *  @var    Callback
     */
    Callback _callback;

    /**
     *  Should we only call your callback once? Or should we simply call it
     *  everytime we need a value?
     *  @var    bool
     */
    const bool _cacheable;

    /**
     *  The cached value, will only be used if _cacheable is set to true
     *  @var    std::unique_ptr<VariantValue>
     */
    mutable std::unique_ptr<VariantValue> _cache;

    /**
     *  Check if we should cache and if we should if we are already cached
     *  and if we aren't cached we'll cache
     *  @return bool
     *  @note This method is only const as it is called from const methods
     */
    bool cache() const
    {
        if (_cacheable && !_cache) _cache = std::unique_ptr<VariantValue>(new VariantValue(_callback()));
        return _cacheable;
    }

public:
    /**
     *  Constructor
     *  @param  callback   The callback function
     *  @param  cache      Should we cache the output of callback or not?
     */
    CallbackValue(const Callback &callback, bool cache = false)
    : _callback(callback)
    , _cacheable(cache) {}

    /**
     *  Destructor
     */
    virtual ~CallbackValue() {}

    /**
     *  Convert the value to a string
     *  @return const char *
     */
    virtual std::string toString() const override
    {
        // Are we cacheable? Yes return the cached version then
        if (cache()) return _cache->toString();

        // call the callback to find out the actual value
        VariantValue value(_callback());

        // retrieve the string value
        return value.toString();
    }

    /**
     *  Convert the variable to an integer value
     *  @return integer_t
     */
    virtual integer_t toNumeric() const override
    {
        // Are we cacheable? Yes return the cached version then
        if (cache()) return _cache->toInteger();

        // call the callback to find out the actual value
        VariantValue value(_callback());

        // retrieve the integer value
        return value.toInteger();
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        // Are we cacheable? Yes return the cached version then
        if (cache()) return _cache->toBoolean();

        // call the callback to find out the actual value
        VariantValue value(_callback());

        // retrieve the boolean value
        return value.toBoolean();
    }

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const override
    {
        // Are we cacheable? Yes return the cached version then
        if (cache()) return _cache->toDouble();

        // call the callback to find out the actual value
        VariantValue value(_callback());

        // retrieve the floating point value
        return value.toDouble();
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
 *  End of namespace
 */
}}
