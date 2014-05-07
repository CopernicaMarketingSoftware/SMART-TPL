/**
 *  Html.h
 *
 *  A html en/decoder
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
class HtmlEscaper : public Escaper
{
public:
    /**
     *  Constructor
     */
    HtmlEscaper() {};
    /**
     *  Destructor
     */
    virtual ~HtmlEscaper() {}

    /**
     *  Encode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    virtual std::string &encode(std::string &input) const override
    {
        // Replace the <, >, " and & with their escaped versions
        replace(input, "<",  "&lt;");
        replace(input, ">",  "&gt;");
        replace(input, "\"", "&quot;");
        replace(input, "&",  "&amp;");

        // Return the modified input
        return input;
    }

    /**
     *  Decode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    virtual std::string &decode(std::string &input) const override
    {
        // Replace the escaped versions of <, >, " and & with their escaped versions
        replace(input, "&lt;",   "<");
        replace(input, "&gt;",   ">");
        replace(input, "&quot;", "\"");
        replace(input, "&amp;",  "&");

        // Return the modified input
        return input;
    }

};

/**
 *  End namespace
 */
}}