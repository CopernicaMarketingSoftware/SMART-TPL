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
     *  The line at which the error occured, no line known means this is set to -1
     *  @var int
     */
    int _line = -1;

public:
    /**
     *  Constructor
     *
     *  @param  error        The error message
     *  @param  line         The line at which the error occured
     */
    CompileError(const std::string &error, int line)
        : std::runtime_error("Compile error at line " + std::to_string(line) + ": " + error), _line(line) {};
    CompileError(const std::string &error)
        : std::runtime_error("Compile error: " + error) {};

    /**
     *  Destructor
     */
    virtual ~CompileError() {}

    /**
     *  The line at which the error occured
     *
     *  @return int
     */
    int line() const { return _line; };
};

/**
 *  End namespace
 */
}