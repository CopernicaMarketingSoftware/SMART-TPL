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
    RunTimeError(const std::string &error)
        : std::runtime_error("RunTimeError: " + error) {};
    RunTimeError() : std::runtime_error("RunTimeError") {};

    /**
     *  Destructor
     */
    virtual ~RunTimeError() {}
};

/**
 *  End namespace
 */
}