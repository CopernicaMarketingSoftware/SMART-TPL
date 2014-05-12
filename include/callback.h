/**
 *  Callback.h
 *
 *  Specific implementation of the Value class, in which the implementation
 *  is done by a callback
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Definition of the callback
 */
using Callback = std::function<Variant()>;

/**
 *  Class definition
 *  @todo    when a string value is retrieved, the next call is often
 *           directly a size() call (or is it the other way around??)
 *           it would be better to call the _callback only once in
 *           such situations
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
     *  @var    std::unique_ptr<Variant>
     */
    std::unique_ptr<Variant> _cache;

    /**
     *  Check if we should cache and if we should if we are already cached
     *  and if we aren't cached we'll cache
     *  @return bool
     */
    bool cache()
    {
        if (_cacheable)
        {
            if (!_cache) _cache = std::unique_ptr<Variant>(new Variant(_callback()));
        }
        return _cacheable;
    }

public:
    /**
     *  Constructor
     *  @param  callback
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
    virtual const char *toString() override
    {
        // Are we cacheable? Yes return the cached version then
        if (cache()) return _cache->toString();

        // call the callback to find out the actual value
        Variant value(_callback());

        // retrieve the string value
        return value.toString();
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() override
    {
        // Are we cacheable? Yes return the cached version then
        if (cache()) return _cache->toNumeric();

        // call the callback to find out the actual value
        Variant value(_callback());

        // retrieve the numeric value
        return value.toNumeric();
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() override
    {
        // Are we cacheable? Yes return the cached version then
        if (cache()) return _cache->toBoolean();

        // call the callback to find out the actual value
        Variant value(_callback());

        // retrieve the boolean value
        return value.toBoolean();
    }

    /**
     *  Get access to a member value
     * 
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return Value
     */
    virtual Variant member(const char *name, size_t size) override
    {
        // callbacks only return scalar values without members
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     */
    virtual size_t memberCount() override
    {
        // callbacks only return scalar variables without members
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param position
     *  @return Value or nullptr if not present
     */
    virtual Variant member(int position) override
    {
        // callbacks can only return scalar values, members will never
        // be retrieved
        return nullptr;
    }

    /**
     *  Get access to the key at a certain position
     *  @param position
     *  @return The name of the key at position or nullptr otherwise
     */
    virtual Variant key(int position) override
    {
        // callbacks can only return simple scalar values, so retrieving
        // a key never happens
        return nullptr;
    }

    /**
     *  String length of the variable
     * 
     *  @return size_t
     */
    virtual size_t size() override
    {
        // Are we cacheable? Yes return the cached version then
        if (cache()) return _cache->size();

        // call the callback to find out the actual value
        Variant value(_callback());

        // retrieve the size
        return value.size();
    }
};

/**
 *  End of namespace
 */
}

