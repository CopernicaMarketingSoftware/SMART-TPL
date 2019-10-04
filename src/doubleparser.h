/**
 *  DoubleParser.h
 * 
 *  Helper class that is capable of parsing dot-based double values, no matter
 *  the current locale of the system SMART-TPL is running on. This is to ensure
 *  that floating point numbers are always parsed correctly - that being according
 *  to the SMART-TPL defintion (1.0) instead of the current locale (1.0 or 1,0).
 * 
 *  @author         David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright      2019 Copernica BV
 */

/**
 *  Dependencies
 */
#include <locale>

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
        // The current system we're running on might be set to another locale, 
        // which has comma separators instead of dots. To ensure correct
        // parsing of the floating point number, we temporarily reset the locale
        // First, get the current locale setting. We store this in a string copy,
        // since the buffer might turn into garbage when changing the locale
        std::string current(std::setlocale(LC_NUMERIC, NULL));

        // force en_US locale for numeric values
        std::setlocale(LC_NUMERIC, "en_US");

        // parse the token
        _value = std::strtod(buffer, nullptr);

        // reset locale
        std::setlocale(LC_NUMERIC, current.data());
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