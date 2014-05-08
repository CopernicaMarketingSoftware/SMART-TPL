/**
 *  Escaper.h
 *
 *  Base class used to implement encoders and decoders used to encode entire templates
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
class Escaper
{
protected:
    /**
     *  Protected constructor
     */
    Escaper(const std::string &name);

    /**
     *  Helper method to find and replace strings in the input buffer
     *  @param  input       The input string in which to search and replace
     *  @param  oldStr      The string to find and replace
     *  @param  newStr      The replacement string
     *  @return std::string It will return the modified input
     */
    std::string &replace(std::string &input, const char *oldStr, const char *newStr) const
    {
        // First we take the length of both replace strings
        const size_t oldStrLen = std::strlen(oldStr);
        const size_t newStrLen = std::strlen(newStr);

        size_t pos = 0;
        // As long as find doesn't return std::string::npos we found what we were looking for
        while ((pos = input.find(oldStr, pos)) != std::string::npos)
        {
            // Replace that what we were looking for with newStr
            input.replace(pos, oldStrLen, newStr);
            pos += newStrLen;
        }
        return input;
    }

public:
    /**
     *  Destructor
     */
    virtual ~Escaper() {}

    /**
     *  Return an Escaper based on the encoding
     *  @param  encoding     The human readable name of the Escaper
     *  @return A static Escaper which you should NOT delete
     */
    static const Escaper* get(const std::string &encoding);

    /**
     *  Encode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    virtual std::string &encode(std::string &input) const = 0;

    /**
     *  Decode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    virtual std::string &decode(std::string &input) const = 0;

};

/**
 *  End namespace
 */
}}