/**
 *  Tokenizer.h
 *
 *  C++ class that tokenizes an input string, and that feeds the tokens to
 *  the parser object
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Forward declarations
 */
class Parser;

/**
 *  Class definition
 */
class Tokenizer
{
private:
    /**
     *  The scanner object
     *  @var    void*
     */
    void *_scanner;

    /**
     *  The line currently being processed
     */
    int _line;

    /**
     *  The current token
     */
    Token* _token;

public:
    /**
     *  Constructor
     */
    Tokenizer();

    /**
     *  Destructor
     */
    virtual ~Tokenizer();

    /**
     *  Process a string, and feed all elements to the parser
     *  @param  parent      Parser object that is notified about tokens
     *  @param  buffer      The buffer to process
     *  @param  size        Size of the buffer
     *  @return true if parsing finished succesful, false otherwise
     */
    bool process(TokenProcessor *parent, const char *buffer, size_t size);

    /**
     *  Increase the line counter
     */
    void increaseLine() { _line++; };

    /**
     *  Get the current line that we are/were at
     */
    int getCurrentLine() const { return _line; };

    /**
     *  Change the current token to newToken
     */
    void setCurrentToken(Token* newToken) { _token = newToken; };

    /**
     *  Returns the current token
     *  @return Token*
     */
    Token* token() const { return _token; };
};

/**
 *  End of namespace
 */
}}