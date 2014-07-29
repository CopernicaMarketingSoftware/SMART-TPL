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
    std::string &encode(std::string &input) const override
    {
        // Declare a simple hex table
        const char hex[] = "0123456789ABCDEF";

        // Start looping through the input string
        for (size_t i = 0; i < input.length(); ++i)
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
     */
    std::string &decode(std::string &input) const override
    {
        std::string output;
        for (unsigned int i = 0; i < input.length(); ++i)
        {
            unsigned char ch = input[i];
            if (ch == '%' && (i + 2) < input.length() && std::isxdigit(input[i + 1]) && std::isxdigit(input[i + 2]))
            {
                if (std::isdigit(input[i + 1])) ch = (unsigned char) ((input[i + 1] - '0') << 4);
                else ch = (unsigned char) ((std::tolower(input[i + 1]) - 'a' + 10) << 4);

                if (std::isdigit(input[i + 2])) ch |= (unsigned char) (input[i + 2] - '0');
                else ch |= (unsigned char) (std::tolower(input[i + 2]) - 'a' + 10);

                i += 2;
            }
            else if (input[i] == '+') ch = ' ';
            output += ch;
        }
        std::swap(input, output);
        return input;
    }

};

/**
 *  End namespace
 */
}}