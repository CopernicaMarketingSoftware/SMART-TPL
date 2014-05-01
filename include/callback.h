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
 */
class CallbackValue : public Value
{
private:
    /**
     *  The function that can be called when a value needs to be retrieved
     *  @var    Callback
     */
    Callback _callback;


    // @todo    when a string value is retrieved, the next call is often
    //          directly a size() call (or is it the other way around??)
    //          it would be better to call the _callback only once in
    //          such situations

public:
    /**
     *  Constructor
     *  @param  callback
     */
    CallbackValue(const Callback &callback) : _callback(callback) {}
    
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
    virtual Value *member(const char *name, size_t size) override
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
    virtual Value *member(int position) override
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
    virtual Value *key(int position) override
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

