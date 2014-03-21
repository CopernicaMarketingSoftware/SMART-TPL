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
     *  Process the buffer
     *  @param  parent      Parser object that is notified about tokens
     *  @return bool
     */
    bool process(TokenProcessor *parent) const;

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
     *  Process a file, and feed all the elements to the parser
     *  @param  parent      Parser object that is notified about tokens
     *  @param  filename    The file to process
     *  @return bool
     */
    bool process(TokenProcessor *parent, const char *filename) const;
};
    
/**
 *  End of namespace
 */
}

