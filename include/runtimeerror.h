/**
 *  CompileError.h
 *
 *  An exception class about runtime errors within templates.
 *
 *  @copyright 2014 Copernica BV
 */

/**
 *  Dependencies
 */
#include <stdexcept>

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class RunTimeError : public std::runtime_error
{
public:
    /**
     *  Constructor
     *
     *  @param  error        The error message
     */
    RunTimeError(const std::string &error = "Runtime error")
        : std::runtime_error(error) {};

    /**
     *  Destructor
     */
    virtual ~RunTimeError() {}
};

/**
 *  End namespace
 */
}