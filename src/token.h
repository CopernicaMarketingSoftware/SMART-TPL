/**
 *  Token.h
 *
 *  Structure that holds the current token that is being processed by the
 *  Tokenizer. Note that the Tokenizer is implemented in Tokenizer.yy
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  The current parsed token
 */
class Token : public std::string
{
public:
    /**
     *  Constructor
     *  @param  buffer
     *  @param  size
     */
    Token(const char *buffer, size_t size) : std::string(buffer, size) {};
    Token(const std::string &str) : std::string(str) {};
    Token(std::string &&str) : std::string(std::move(str)) {};
    Token(const char c) : std::string(1, c) {};
    Token() : std::string() {};

    /**
     *  Destructor
     */
    virtual ~Token() {}
};

/**
 *  End namespace
 */
}}