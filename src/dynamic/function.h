/**
 *  Function.h
 *
 *  When you want to retrieve a function from a dynamicallly loaded
 *  library, you normally use the dlsym() function for that. The
 *  Function object is a little more convenient:
 *
 *      // create the library
 *      Dynamic::Library library("libmagic.so");
 *
 *      // get the magic_open function
 *      Dynamic::Function<magic_t(int)> magic_open(library, "magic_open");
 *
 *      // call the magic_open function
 *      magic_t result = magic_open(MAGIC_NONE);
 *
 *  This class is based on the "Callable" class by Martijn Otto that was
 *  first used in the MailerQ plugin system.
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
#include "library.h"

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal { namespace Dynamic {

/**
 *  Forward declarations
 */
class Handle;

/**
 *  Make the Function class a templated class
 */
template <class T> class Function {};

/**
 *  So that we can write a partial specialisation
 *  using a function prototype, indicating the
 *  prototype usable for the given callback
 */
template <class T, class ...Arguments>
class Function<T(Arguments...)>
{
private:
    /**
     *  We need a handle to the library for as long as the function object exists
     *  @var std::shared_ptr<Handle>
     */
    std::shared_ptr<Handle> _handle;

    /**
     *  Store pointer to the actual dynamically loaded
     *  function. This is done in a union because the
     *  result from a dlsym call is a void pointer which
     *  cannot be legally cast into a function pointer.
     *
     *  We therefore always set the first type (which is
     *  void* making it legal) and, because all members
     *  in a union share the same address, we can then
     *  read the second type and actually call it.
     *
     *  @var Callable
     */
    union Callable {

        /**
         *  Property for getting and setting the return
         *  value from dlsym. This is always a void*
         *  @var    void
         */
        void *ptr;

        /**
         *  Property for executing the mapped function
         *
         *  @param  mixed,...   function parameters
         *  @return mixed
         *
         *  @var    function
         */
        T (*func)(Arguments...);

        /**
         *  Constructor
         */
        Callable() : ptr(nullptr) {}

        /**
         *  We may be moved
         *
         *  @param  callable    the callable we are moving
         */
        Callable(Callable&& callable) :
            ptr(callable.ptr)
        {
            // the other callable no longer has a handle
            callable.ptr = nullptr;
        }

        /**
         *  Constructor
         *
         *  @param  function    the mapped function
         */
        Callable(void *function) : ptr(function) {}

    } _method;

public:
    /**
     *  Constructor
     */
    Function() = default;

    /**
     *  Constructor
     *  @param  library     The library to load the function from
     *  @param  name        Name of the function
     */
    Function(const Library &library, const char *name) :
        _handle(library.handle()),
        _method(_handle->symbol(name)) {}

    /**
     *  Move constructor
     *  @param other
     */
    Function(Function &&other) = default;

    /**
     *  Destructor
     */
    virtual ~Function() {}

    /**
     *  Is this a valid function or not?
     *  @return bool
     */
    bool valid() const
    {
        return _method.ptr != nullptr;
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

    /**
     *  Invoke the function
     *
     *  @param  mixed,...
     *  @throws std::bad_function_call
     */
    T operator()(Arguments... parameters) const
    {
        // check whether we have a valid function
        if (_method.ptr == nullptr) throw std::bad_function_call();

        // execute the method given all the parameters
        return _method.func(std::forward<Arguments>(parameters)...);
    }
};

/**
 *  End of namespace
 */
}}}