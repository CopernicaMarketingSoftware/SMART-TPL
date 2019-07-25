/**
 *  NumberFormat.h
 *
 *  Built-in "|number_format" modifier
 *
 *  @author         David van Erkelens <david.vanerkelens@copernica.com>
 *  @copyright      2019 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class NumberFormatModifier : public Modifier
{
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
        // Convert input to double
        double original(input.toDouble());

        // make sure we have a parameter containing the format
        if (params.size() < 1) throw NoModification();

        // get the amound of decimals to output
        int decimals = params[0].toInteger();

        // buffer to create the printf format
        char format[10];

        // format the format
        sprintf(format, "%%.%if", decimals);

        // calculate size of new string
        size_t size = snprintf(nullptr, 0, format, original);

        // create buffer
        char buffer[size + 1];

        // create new string
        sprintf(buffer, format, original);

        // create object
        return VariantValue(buffer);
    }
};

/**
 *  End namespace
 */
}}