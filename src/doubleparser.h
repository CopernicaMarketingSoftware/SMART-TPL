/**
 *  DoubleParser.h
 * 
 *  Helper class that is capable of parsing dot-based double values, no matter
 *  the current locale of the system SMART-TPL is running on. This is to ensure
 *  that floating point numbers are always parsed correctly.
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
        // First, get the current locale setting
        auto current = setlocale(LC_NUMERIC, NULL);

        // force en_US locale for numeric values
        setlocale(LC_NUMERIC, "en_US");

        // parse the token
        _value = std::strtod(buffer, nullptr);

        // reset locale
        setlocale(LC_NUMERIC, current);
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