/**
 *  Count_words.h
 *
 *  Built-in "|count_words" modifier
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
class CountWordsModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~CountWordsModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        // Let's just convert our input to a C string
        std::string str(input.toString(), input.size());

        // Split our input by whitespaces, newlines, etc
        boost::regex rgx("\\s+");
        boost::sregex_token_iterator iter(str.begin(), str.end(), rgx, -1);

        // Init our output value
        numeric_t output = 0;

        // Count matches that contain alphanumerics
        boost::regex word("[a-zA-Z0-9\\x80-\\xff]");
        boost::sregex_token_iterator end;
        for (; iter != end; ++iter)
        {
            if (boost::regex_search(iter->str(), word)) ++output;
        }

        // Return the output
        return output;
    }
};

/**
 *  End namespace
 */
}}
