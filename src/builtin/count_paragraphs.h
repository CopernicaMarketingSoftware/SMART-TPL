/**
 *  Count_paragraphs.h
 *
 *  Built-in "|count_paragraphs" modifier
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class CountParagraphsModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~CountParagraphsModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // Let's just convert our input to a C string
        std::string str = input.toString();

        // Init our output value
        numeric_t output = 0;
        for (auto c : str)
        {
            // We're really just counting the \n and \r's
            if (c == '\n' || c == '\r') ++output;
        }

        // Return the output
        return output;
    }
};

/**
 *  End namespace
 */
}}