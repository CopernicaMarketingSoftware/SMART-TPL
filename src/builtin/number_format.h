/**
 *  NumberFormat.h
 *
 *  Built-in "|number_format" modifier
 *
 *  @author         David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright      2019 Copernica BV
 */

/**
 *  Dependencies
 */
#include <locale>

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class NumberFormatModifier : public Modifier
{
private:
    /**
     *  Struct that works with the std::numpunct facet and can be
     *  constructed with a char for the decimal and thousands separators 
     */
    struct formatter : std::numpunct<char> {

        // chars for the separators
        char decimal; char thousand;

        // constructor
        formatter(char decimal, char thousand) : decimal(decimal), thousand(thousand) {}

        // build in functions for separator formatting
        char do_thousands_sep()   const { return thousand; } // thousands separator
        std::string do_grouping() const { return (int) thousand == 0 ? "" : "\3"; } // separate every 3 digits, if we have a separator
        char do_decimal_point()   const { return decimal; }  // decimal separator
    };

public:
    /**
     *  Destructor
     */
    virtual ~NumberFormatModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // make sure we have a parameter containing the number of decimals
        if (params.size() < 1) throw NoModification();

        // get the amount of decimals to output
        int decimals = params[0].toInteger();

        // get separators for decimals and thousands
        char decimal_separator = params.size() > 1 ? params[1].toString()[0] : '.';
        char thousand_separator = params.size() > 2 ? params[2].toString()[0] : (char) 0;

        // create stringstream to store formatted number
        std::stringstream stream;

        // create custom locale for our formatting options
        std::locale formatting_locale(stream.getloc(), new NumberFormatModifier::formatter(decimal_separator, thousand_separator));

        // set formatting options
        stream.precision(decimals);
        stream.imbue(formatting_locale);

        // stream the value (never in scientific format)
        stream << std::fixed << input.toDouble();

        // create object
        return VariantValue(stream.str());
    }
};

/**
 *  End namespace
 */
}}