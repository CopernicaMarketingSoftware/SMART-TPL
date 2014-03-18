/**
 *  Parser.h
 *
 *  Class that is used internally to parse a template file. The constructor
 *  is protected - you should create an instance of SyntaxTree to get the 
 *  syntax tree of a template.
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
class Tokenizer;
class Token;

/**
 *  Class definition
 */
class Parser
{
protected:
    /**
     *  Constructor
     */
    Parser() {}

public:        
    /**
     *  Destructor
     */
    virtual ~Parser() {}
    
    /**
     *  Called by the tokenizer when a token is detected
     *  @param  id      Token identifier (see lemon.h)
     *  @param  token   Additional token information
     */
    virtual void process(int id, const Token &token) = 0;
};
 
/**
 *  End namespace
 */
}