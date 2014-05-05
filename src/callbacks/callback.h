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
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class BaseCallback
{
protected:
    /**
     *  The signature
     *  @var    jit_type_t
     */
    jit_type_t _signature = nullptr;

public:
    /**
     *  Constructor
     */
    BaseCallback() {}

    /**
     *  Destructor
     */
    virtual ~BaseCallback()
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
}}