/**
 *  DoubleParser.h
 * 
 *  Helper class that is capable of parsing dot-based double values, no matter
 *  the current locale of the system SMART-TPL is running on. This is to ensure
 *  that floating point numbers are always parsed correctly - that being according
 *  to the SMART-TPL defintion (1.0) instead of the current locale (1.0 or 1,0).
 *  Therefore, this class is basically a locale-independent variant of the 
 *  default strtod function.
 * 
 *  This parser uses a istringstream with a locale setting, since we don't want to
 *  change the global locale due to possible undefined behaviours in multithreaded
 *  applications. Therefore, a locale setting is applied to the stream only, so
 *  parsing doubles does not interfere with other threads.
 * 
 *  @author         David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright      2019 Copernica BV
 */

/**
 *  Dependencies
 */
#include <locale>
#include <sstream>

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class DoubleParser {
private:
    /**
     *  The parsed value
     *  @var double
     */
    double _value;

public:
    /**
     *  Constructor
     *  @param  const char *
     */
    DoubleParser(const char *buffer)
    {
        // create stream based on the buffer
        std::istringstream stream(buffer);

        // set stream locale
        stream.imbue(std::locale("en_US"));

        // stream to the value
        stream >> _value;
    }

    /**
     *  Cast to double
     *  @return double
     */
    operator double() const 
    {
        return _value;
    }
};

/**
 *  End of namespace
 */
}}