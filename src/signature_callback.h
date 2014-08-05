/**
 *  SignatureCallback.h
 *
 *  Class to easily get the required libjit signatures
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
class SignatureCallback
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
    SignatureCallback(std::vector<jit_type_t> params, jit_type_t return_type = jit_type_void)
    : _signature(jit_type_create_signature(jit_abi_cdecl, return_type, params.data(), params.size(), 1)) {}

    /**
     *  Destructor
     */
    ~SignatureCallback()
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