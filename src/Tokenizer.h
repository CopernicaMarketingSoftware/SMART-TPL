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
     *  Pointer to the parser
     *  @var    Parser
     */
    Parser *_parser;

public:
    /**
     *  Constructor
     *  @param  parser      Pointer to the parser that wants to be fed with tokens
     */
    Tokenizer(Parser *parser) : _parser(parser) {}
    
    /**
     *  Destructor
     */
    virtual ~Tokenizer() {}
    
    /**
     *  Process a string, and feed all elements to the parser
     *  @param  buffer      The buffer to process
     *  @param  size        Size of the buffer
     *  @return bool
     */
    bool process(const char *buffer, size_t size);
};
    
/**
 *  End of namespace
 */
}

