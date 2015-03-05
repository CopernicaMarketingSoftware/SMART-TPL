/**
 *  Buffer.h
 *
 *  Template source that can be used for templates that are fetched from
 *  memory.
 *
 *  Explanation: when you instantiate a Template object, you need to pass
 *  a Source object to it to tell the Template object where it can be found.
 *  This Buffer class is one of the available Source objects that can be used
 *  for templates that are already in memory.
 *
 *  Important: the buffer that is passed to the constructor should be valid
 *  for as long as the Memory object exists!
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
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