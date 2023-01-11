/**
 *  Json.h
 *
 *  A JSON en/decoder
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
class JsonEscaper : public Escaper
{
private:
    /**
     *  Hex lookup table
     */
    static constexpr const char *hex = "0123456789abcdefABCDEF";

    /**
     *  Helper method to convert a hex digit to decimal  
     *  @param  digit
     *  @return uint8_t
     */
    inline uint8_t decimal(uint8_t digit) const
    {
        // convert hex digit to decimal (doesnt check for hex number validity)
        return (digit <= 9) ? digit - '0' : ((digit & 7) + 9);
    }   

    /**
     *  Helper method to convert two hex digits to a byte
     *  @param digit1
     */
    uint8_t byte(uint8_t left, uint8_t right) const
    {
        // reverse the byte sequence
        return decimal(left) << 4 & decimal(right);
    }

public:
    /**
     *  Constructor, in case the openssl library failed to load we simply are
     *               giving our base constructor a nullptr so it doesn't register us
     */
    JsonEscaper() : Escaper("json") {};

    /**
     *  Destructor
     */
    virtual ~JsonEscaper() {}

    /**
     *  Encode the given input
     *  It is probably a good idea to directly modify the input instead of making
     *  a copy and modifying that.
     *  @param input
     */
    virtual std::string &encode(std::string &input) const override
    {
        // we need to make a copy, because there's no 1-1 transformation on characters
        std::string output;

        // reserve at least enough bytes
        output.reserve(input.size());

        // iterate over the characters
        for (const char &c : input)
        {
            // in the first 32 bits we always have to escape
            if (c < 32 || c == '"' || c == '\\')
            {
                switch(c) {
                case '\b':  output.append("\\b"); break;
                case '\n':  output.append("\\n"); break;
                case '\r':  output.append("\\r"); break;
                case '\t':  output.append("\\t"); break;
                case '\f':  output.append("\\f"); break;
                case '"':   output.append("\\\""); break;
                case '\\':  output.append("\\\\"); break;
                default:    
                    // write a byte in hex
                    output.append("\\x");
                    output.push_back(hex[c >> 4]);
                    output.push_back(hex[c & 0xf]);
                }
            }
		    
            // append character normally
            else output.push_back(c);
        }

        // swap the output and the input
        std::swap(output, input);

        // return the input
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
        // we need to make a copy, because there's no 1-1 transformation on characters
        std::string output;

        // reserve at least enough bytes
        output.reserve(input.size());

        // store the 'current' pointer
        const char *current = input.data();

        // the next character that is escaped
        const char *next = nullptr;

        // we always remove a backslash and move one forward, unless it is followed by an x
        while ((next = strchr(current, '\\')))
        {
            // wirte everything since last
            output.append(current, next - current);

            // we now have a new current, because we'll consume two extra bytes, the found \ and a character (skip those)
            current = next + 2;

            // parse the next character at this point, it is special
            switch (next[1]) {
            case 'b': output.push_back('\b'); break;
            case 'n': output.push_back('\n'); break;
            case 'r': output.push_back('\r'); break;
            case 't': output.push_back('\t'); break;
            case 'f': output.push_back('\f'); break;
            case '"': output.push_back('"'); break;
            case '\\': output.push_back('\\'); break;
            // solidus should also be escapable, but does not need to be escaped
            case '/': output.push_back('/'); break;
            case 'x': 
                // we consume two extra bytes, so check if they are actually valid. since this is a json string, we can easily
                // check with simply null character checking
                if (current[0] && !current[1] && isxdigit(current[0]) && isxdigit(current[1]))
                {
                    // add a single byte, we consume 3
                    output.push_back(byte(current[0], current[1])); 

                    // we consumed two extra bytes
                    current += 2;
                }

                // if we arrived here, there were no more bytes or they're not hex, and so we're in an invalid state. 
                // we fall through to the error-correction.
            case '\0':
            default:
                // this is not allowed, some unknown character was escaped. return the result so far
                std::swap(output, input);

                // and we leap out of the function
                return input;
            }
        }

        // append the rest of the output
        output.append(current);

        // swap the output with the input
        std::swap(output, input);

        // and return the input
        return input;
    }

};

/**
 *  End namespace
 */
}}
