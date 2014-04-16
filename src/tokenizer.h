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
namespace SmartTpl {

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
    int line;

    /**
     *  The current token
     *  Mutable as it has to be modified in process, which is const
     */
    mutable Token* token;

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
     *  @return bool
     */
    bool process(TokenProcessor *parent, const char *buffer, size_t size) const;

    /**
     *  Increase the line counter
     */
    void increaseLine() { line++; };

    /**
     *  Change the current token to newToken
     */
    void setCurrentToken(Token* newToken) { token = newToken; };
};
    
/**
 *  End of namespace
 */
}

