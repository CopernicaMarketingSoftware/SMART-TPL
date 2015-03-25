/**
 *  Handle.h
 *
 *  Wrapper around the function handle. Instances of this class are
 *  stored in shared pointers, so that an instance of the handle
 *  will stay in memory for as long as there are functions active
 *  that refer to it.
 *
 *  This is an internal class, in normal circumstances, there is
 *  no need to instantiate this class. Use the Library class to make
 *  an instance.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2015 Copernica BV
 */

/**
 *  Include guard
 */
#pragma once

/**
 *  Dependencies
 */
#include <dlfcn.h>

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal { namespace Dynamic {

/**
 *  Class definition
 */
class Handle
{
private:
    /**
     *  The actual void* returned from dlopen()
     *  @var void*
     */
    void *_handle;

public:
    /**
     *  Constructor
     *  @param  name        Library to open
     */
    Handle(const char *name) : _handle(dlopen(name, RTLD_NOW)) {}

    /**
     *  Destructor
     */
    virtual ~Handle()
    {
        // close the handle
        if (_handle) dlclose(_handle);
    }

    /**
     *  Check whether the handle is valid
     *  @return bool
     */
    bool valid() const
    {
        // handle should be valid
        return _handle != nullptr;
    }

    /**
     *  Get access to the internal handle
     *  @return void*
     */
    void *handle() const
    {
        return _handle;
    }

    /**
     *  Retrieve a symbol
     *  @param  name
     *  @return void*
     */
    void *symbol(const char *name) const
    {
        // call dlsym()
        return dlsym(_handle, name);
    }
};

/**
 *  End namespace
 */
}}}