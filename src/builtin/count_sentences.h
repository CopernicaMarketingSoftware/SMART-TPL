/**
 *  Count_sentences.h
 *
 *  Built-in "|count_sentences" modifier
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
class CountSentencesModifier : public Modifier
{
public:
    /**
     *  Destructor
     */
    virtual ~CountSentencesModifier() {};

    /**
     *  Modify a value object
     *  @param  input
     *  @param  params      Parameters used for this modification
     *  @return Value
     */
    virtual Variant modify(const Variant &input, const SmartTpl::Parameters &params) override
    {
        // Let's just convert our input to a C string
        std::string str(input.toString(), input.size());

        // Split our input by whitespaces, newlines, etc
        boost::regex rgx("[^\\s]\\.(?!\\w)");
        boost::sregex_token_iterator iter(str.begin(), str.end(), rgx, -1);
        boost::sregex_token_iterator end;

        // Return the distance between the iterator and an invalid/end iterator
        return std::distance(iter, end);
    }
};

/**
 *  End namespace
 */
}}