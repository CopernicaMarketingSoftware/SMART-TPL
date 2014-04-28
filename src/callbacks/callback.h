/**
 *  Callback.h
 *
 *  Base class of all the callback methods
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Callback
{
protected:
    /**
     *  The signature
     *  @var    jit_type_t
     */
    jit_type_t _signature;

public:
    /**
     *  Constructor
     */
    Callback() {
        _signature = nullptr;
    }

    /**
     *  Destructor
     */
    virtual ~Callback()
    {
        if (_signature) jit_type_free(_signature);
    }

    /**
     *  Retrieve the signature
     *  @return signature
     */
    const jit_type_t &signature() const
    {
        return _signature;
    }
};

/**
 *  End namespace
 */
}

