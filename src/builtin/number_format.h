/**
 *  NumberFormat.h
 *
 *  Built-in "|number_format" modifier
 *
 *  @author         David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright      2019 - 2020 Copernica BV
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
    struct formatter : std::numpunct<char>
    {
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

        // get separator variables for decimals and thousands
        char decimal_separator = '.'; char thousand_separator = (char) 0;

        // if we have a valid parameter, overwrite decimal separator
        if (params.size() > 1)
        {
            // convert to string
            auto param = params[1].toString();

            // make sure that we have a character (we could throw if the param is too long?)
            if (param.size() > 0) decimal_separator = param[0]; 
        }

        // if we have a valid parameter, overwrite thousands separator
        if (params.size() > 2)
        {
            // convert to string
            auto param = params[2].toString();

            // make sure that we have a character (we could throw if the param is too long?)
            if (param.size() > 0) thousand_separator = param[0]; 
        }

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