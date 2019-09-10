/**
 *  State.h
 *
 *  The class that implements the "{$smarty} variable that holds the
 *  current time (and in the future maybe other meta-properties)
 *
 *  @copyright 2018 - 2019 Copernica BV
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
     *  Get access to a member value
     *  @param  name        name of the member
     *  @param  size        size of the name
     *  @return VariantValue
     */
    virtual VariantValue member(const char *name, size_t size) const override
    {
        std::cout << "state member" << std::endl;
        // check the member
        if (size == 3 && strncmp(name, "now", 3) == 0) return int64_t(time(nullptr));
        
        // all other members are not set
        return nullptr;
    }
};

/**
 *  End of namespace
 */
}

