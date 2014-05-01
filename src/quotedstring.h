/**
 *  QuotedString.h
 *
 *  Class that takes a string and quotes all input from it so that it can
 *  be picked up by a compiler
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class QuotedString : public std::string
{
public:
    /**
     *  Constructor
     *  @param  input       Input string
     */
    QuotedString(const std::string &input)
    {
        // we reserve plenty of space (normally not more that two or three 
        // extra characters are necessary
        reserve(input.size() + 20);

        // loop through the input
        for (char c : input)
        {
            switch (c) {
            case '\a':  append("\\a"); break;
            case '\n':  append("\\n"); break;
            case '\r':  append("\\r"); break;
            case '\0':  append("\\0"); break;
            case '\t':  append("\\t"); break;
            case '"' :  append("\\\""); break;
            case '\'':  append("\\\'"); break;
            case '\\':  append("\\\\"); break;
            default:    append(&c, 1); break;
            }
        }
    }
};

/**
 *  End namespace
 */
}

