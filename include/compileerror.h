/**
 *  CompileError.h
 *
 *  An exception class about compile errors within templates, these will include
 *  a line number which you can retrieve using the line() method.
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
class CompileError : public std::runtime_error
{
private:
    /**
     *  The line at which the error occured
     *  @var std::size_t
     */
    std::size_t _line;

public:
    /**
     *  Constructor
     *
     *  @param  error        The error message
     *  @param  line         The line at which the error occured
     */
    CompileError(const std::string &error, std::size_t line)
        : std::runtime_error("Compile error at line " + std::to_string(line) + ": " + error), _line(line) {};

    /**
     *  Destructor
     */
    virtual ~CompileError() {}

    /**
     *  The line at which the error occured
     *
     *  @return std::size_t
     */
    std::size_t line() const { return _line; };
};

/**
 *  End namespace
 */
}