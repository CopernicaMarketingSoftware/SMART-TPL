/**
 *  Regex_Replace.h
 *
 *  Built-in "|regex_replace:"[\r\t\n]":":"" modifier
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
class RegexReplaceModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~RegexReplaceModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual VariantValue modify(const VariantValue &input, const SmartTpl::Parameters &params) override
    {
        if (params.size() >= 2)
        {
            try
            {
                // initialize our settings based on the provided parameters
                boost::regex regex(params[0].toString());
                std::string replace_text(params[1].toString());

                // initialize our input string
                std::string input_str(input.toString());

                // Do the actual regex replace into stream
                std::ostringstream stream;
                boost::regex_replace(std::ostream_iterator<char>(stream)
                                    ,input_str.begin(), input_str.end(), regex, replace_text);

                // Turn stream into a string and return it
                return stream.str();
            }
            catch (const boost::regex_error &error)
            {
                // Return the original input in case of a failure
                return input;
            }
        }

        // Return the original input in case of not enough parameters
        return input;
    }
};

/**
 *  End namespace
 */
}}
