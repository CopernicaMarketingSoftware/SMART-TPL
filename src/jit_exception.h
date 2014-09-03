/**
 *  Jit_Exception.h
 *
 *  A custom exception which will turn a libjit exception code into a human
 *  readable error
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
class JitException : public std::runtime_error
{
private:
    std::string initialize(int exception_type)
    {
        // convert the exception type to a human readable string
        // source: https://github.com/agalakhov/libjit/blob/master/jit/jit-except.c#L213
        switch (exception_type) {
        case JIT_RESULT_OVERFLOW:
            return "Overflow during checked arithmetic operation";
        case JIT_RESULT_ARITHMETIC:
            return "Arithmetic exception (dividing the minimum integer by -1)";
        case JIT_RESULT_DIVISION_BY_ZERO:
            return "Division by zero";
        case JIT_RESULT_COMPILE_ERROR:
            return "Error during function compilation";
        case JIT_RESULT_OUT_OF_MEMORY:
            return "Out of memory";
        case JIT_RESULT_NULL_REFERENCE:
            return "Null pointer dereferenced";
        case JIT_RESULT_NULL_FUNCTION:
            return "Null function pointer called";
        case JIT_RESULT_CALLED_NESTED:
            return "Nested function called from non-nested context";
        case JIT_RESULT_OUT_OF_BOUNDS:
            return "Array index out of bounds";
        case JIT_RESULT_UNDEFINED_LABEL:
            return "Undefined label";
        case JIT_RESULT_OK: // I'm assuming this will never actually happen..
            return "Uhm, success?";
        default:
            return "Unknown exception " + std::to_string(exception_type);
        };
    }

public:
    /**
     *  Constructor
     */
    JitException(int exception_type)
    : std::runtime_error(initialize(exception_type))
    {
    }

    /**
     *  Deconstructor
     */
    virtual ~JitException() {};

    /**
     *  Custom exception handler for libjit
     *  We purely need this as the default exception handler of libjit will call
     *  exit(1); Which we obviously don't want. The only way around this is to
     *  register our own exception handler and throw a C++ exception from there
     *  so it'll jump over parts of the default libjit exception handler.
     */
    static void* handler(int exception_type)
    {
        throw JitException(exception_type);
    }
};

/**
 *  End namespace
 */
}}