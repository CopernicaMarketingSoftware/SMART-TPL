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
    QuotedString(const char *input, size_t size)
    {
        // we reserve plenty of space (normally not more that two or three 
        // extra characters are necessary
        reserve(size + 20);
        
        // loop through the input
        for (size_t i=0; i<size; i++)
        {
            switch (input[i]) {
            case '\n':  append("\\n"); break;
            case '\0':  append("\\0"); break;
            case '\t':  append("\\t"); break;
            case '"' :  append("\\\""); break;
            default:    append(&input[i], 1); break;
            }
        }
    }
};

/**
 *  End namespace
 */
}

