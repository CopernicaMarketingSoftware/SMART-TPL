/**
 *  Library.h
 *
 *  Class to dynamically open libraries. When you want to open a library
 *  using dlopen(), you can use this class for it instead. To open
 *  a library, simply make an instance of Library:
 *
 *      Dynamic::Library("libopenssl.so");
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
#include "handle.h"

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal { namespace Dynamic {

/**
 *  Class to open the dynamic library
 */
class Library
{
private:
    /**
     *  The actual library handle
     *  @var std::shared_ptr<Handle>
     */
    std::shared_ptr<Handle> _handle;

    /**
     *  Any error messages are stored in this variable
     *  @var std::string
     */
    std::string _error;

public:
    /**
     *  Constructor
     *  @param  name        Name of the library to open
     */
    Library(const char *name) : _handle(new Handle(name))
    {
        // let's only set an error message if we aren't actually valid
        // we are purely storing this error message as dlerror() will
        // return the error from the last dl* operation, which doesn't
        // necessary come from us.
        if (!valid()) _error = dlerror();
    }

    /**
     *  Constructor
     *
     *  You can pass in an array of library names which will be tried
     *  in the order that you supply them. The first working library
     *  will be used. This can be useful if you want to try different
     *  version that you know are compatible:
     *
     *      Library lib({"libmagic.so","libmagic.so.1.","libmagic.so.1.0.0",nullptr});
     *
     *  @param  names       Array of library names to open, the last name in the array should be NULL
     */
    Library(const char *names[])
    {
        // loop through the library names
        for (unsigned i = 0; names[i]; ++i)
        {
            // create the handle
            _handle = std::make_shared<Handle>(names[i]);

            // leap out if this handle is valid
            if (_handle->valid()) return;
        }

        // if we reach this we failed to load any of the libraries, so we set an error message
        _error = dlerror();
    }

    /**
     *  Initialize with an initializer list
     *
     *  @param  names       Array of library names to open
     */
    Library(const std::initializer_list<const char *> &names)
    {
        // loop through the names
        for (const auto &name : names)
        {
            // create the handle
            _handle = std::make_shared<Handle>(name);

            // leap out if this handle is valid
            if (_handle->valid()) return;
        }

        // if we reach this we failed to load any of the libraries, so we set an error message
        _error = dlerror();
    }

    /**
     *  Destructor
     */
    virtual ~Library() {}

    /**
     *  Try loading a different dynamic library into this object
     *  @param  name        Name of the library file to open
     *  @return bool
     */
    bool load(const char *name)
    {
        // create a new handle, and check whether it is valid
        auto handle = std::make_shared<Handle>(name);
        if (!handle->valid()) return false;

        // handle is valid, forget previous handle
        _handle = handle;
        return true;
    }

    /**
     *  Get access to the internal handle
     *  @return std::shared_ptr
     *  @internal
     */
    const std::shared_ptr<Handle> &handle() const { return _handle; }

    /**
     *  Is this a valid library or not?
     *  @return bool
     */
    bool valid() const
    {
        return _handle && _handle->valid();
    }

    /**
     *  If the library is not valid, return an error.
     *  @see    valid()
     *  @return std::string
     */
    const std::string& error() const
    {
        return _error;
    }

    /**
     *  Look up a symbol in the library
     *  @param  name
     *  @return void*
     */
    void *symbol(const char *name) const
    {
        // pass on to the handle object
        return _handle ? _handle->symbol(name) : nullptr;
    }

    /**
     *  The library object can also be used as in a boolean context,
     *  for that there is an implementation of a casting operator, and
     *  the negate operator
     *  @return bool
     */
    operator bool () const { return valid(); }
    bool operator ! () const { return !valid(); }

    /**
     *  Test whether we are a valid object
     *  @param  nullptr test if we are null
     */
    bool operator==(std::nullptr_t /* nullptr */) const { return !valid(); }
    bool operator!=(std::nullptr_t /* nullptr */) const { return valid(); }
};

/**
 *  End of namespace
 */
}}}