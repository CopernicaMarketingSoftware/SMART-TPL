/**
 *  Jsonencode.h
 *
 *  Built-in "|jsonencode" modifier
 *
 *  @author Michael van der Werve <michael.vanderwerve@mailerq.com>
 *  @copyright 2020 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class JsonencodeModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~JsonencodeModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    VariantValue modify(const Value &input, const SmartTpl::Parameters &params) override
    {
        // Get the json encoder
        const Escaper *escaper = Escaper::get("json");

        // Turn our input into a string
        std::string output(input.toString());

        // Call encode and return the output
        return escaper->encode(output);
    }
};

/**
 *  End namespace
 */
}}
