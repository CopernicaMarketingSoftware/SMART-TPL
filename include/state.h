/**
 *  State.h
 *
 *  The class that implements the "{$smarty} variable that holds the
 *  current time (and in the future maybe other meta-properties)
 *
 *  @copyright 2018 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Begin of namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class State : public Value
{
public:
    /**
     *  Convert the value to a string
     *  @return std::string
     */
    virtual std::string toString() const override
    {
        // this is the output of {$smarty}
        return "";
    }

    /**
     *  Convert the variable to a numeric value
     *  @return numeric
     */
    virtual numeric_t toNumeric() const override
    {
        // this is the output of {$smarty|intval}
        return 0;
    }

    /**
     *  Convert the variable to a boolean value
     *  @return bool
     */
    virtual bool toBoolean() const override
    {
        // this is what happens when you call {if $smarty}yes{else}no{/if}
        return true;
    }

    /**
     *  Convert the variable to a floating point value
     *  @return double
     */
    virtual double toDouble() const override
    {
        // when used in double context
        return 0.0;
    }

    /**
     *  Get access to a member value
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return VariantValue
     */
    virtual VariantValue member(const char *name, size_t size) const override
    {
        // check the member
        if (size == 3 && strncmp(name, "now", 3) == 0) return int64_t(time(nullptr));
        
        // all other members are not set
        return nullptr;
    }

    /**
     *  Get access to the amount of members this value has
     *  @return size_t
     */
    virtual size_t memberCount() const override
    {
        // it is not an array
        return 0;
    }

    /**
     *  Get access to a member at a certain position
     *  @param  position    Position of the item we want to retrieve
     *  @return VariantValue
     */
    virtual VariantValue member(size_t position) const override
    {
        // impossible
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
        // the {$smarty} variable is not iteratable
        return nullptr;
    }
};

/**
 *  End of namespace
 */
}

