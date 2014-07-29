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
    HtmlEscaper() : Escaper("html") {};
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
    std::string &encode(std::string &input) const override
    {
        // Replace the <, >, " and & with their escaped versions
        // We do this by looping through the input and looking for the characters that need to be escaped at the same time
        for (std::string::size_type pos = 0; pos != std::string::npos;) {

            pos = input.find_first_of("\"\'&<>", pos);

            if (pos == std::string::npos) break;
            // In case we found one of them we simply replace it in place with the escaped version
            switch (input[pos])
            {
                case '\"': input.replace(pos, 1, "&quot;"); pos += 6; break;
                case '\'': input.replace(pos, 1, "&apos;"); pos += 6; break;
                case '<' : input.replace(pos, 1, "&lt;");   pos += 4; break;
                case '>' : input.replace(pos, 1, "&gt;");   pos += 4; break;
                case '&' : input.replace(pos, 1, "&amp;");  pos += 5; break;
                default: break;
            }
        }

        // Return the modified input
        return input;
    }

    /**
     *  Decode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    std::string &decode(std::string &input) const override
    {
        // Replace the escaped versions of <, >, " and & with their escaped versions
        replace(input, "&lt;",   "<");
        replace(input, "&gt;",   ">");
        replace(input, "&quot;", "\"");
        replace(input, "&apos;", "\'");
        replace(input, "&amp;",  "&");

        // Return the modified input
        return input;
    }

};

/**
 *  End namespace
 */
}}