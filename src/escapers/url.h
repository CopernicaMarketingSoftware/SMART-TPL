/**
 *  Url.h
 *
 *  An url en/decoder
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
class UrlEscaper : public Escaper
{
public:
    /**
     *  Constructor
     */
    UrlEscaper() : Escaper("url") {};
    /**
     *  Destructor
     */
    virtual ~UrlEscaper() {}

    /**
     *  Encode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    virtual std::string &encode(std::string &input) const override
    {
        // Declare a simple hex table
        const char hex[] = "0123456789ABCDEF";

        // Start looping through the input string
        for (int i = 0; i < input.length(); ++i)
        {
            // Grab a reference to the current character so that we can easily overwrite it
            char &ch = input[i];

            // Everything that passes this first test doesn't have to be encoded
            if (std::isalnum(ch) || ch == '_' || ch == '.' || ch == '-') continue;

            // Spaces become '+'
            if (ch == ' ') ch = '+';
            else
            {
                // Everything else has to be hex encoded, this is where our hex table comes in
                // This is mostly some bit magic to look up the correct values from our hex table
                const char encoded[] = { hex[ch >> 4], hex[ch & 0x0F] };

                // Set the character at our current position to % as required by url encoding
                ch = '%';

                // Insert the hex encoded value just after the just placed '%'
                input.insert(i + 1, encoded, sizeof(encoded));

                // And increase our counter by 2 so we jump over our just inserted data that we don't want to overwrite
                // Although that should not happen as all the hex characters don't pass the first
                // if statement aka they don't have to be encoded
                i += 2;
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
     *  @todo Implement url decoding
     */
    virtual std::string &decode(std::string &input) const override
    {
        return input;
    }

};

/**
 *  End namespace
 */
}}