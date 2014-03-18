/**
 *  Parser.h
 *
 *  Class that is used internally to parse a template file
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class Parser
{
public:
    /**
     *  Constructor
     */
    Parser() {}
    
    /**
     *  Destructor
     */
    virtual ~Parser() {}
    
    /**
     *  Called by the tokenizer when a token is detected
     *  @param  id      Token identifier (see lemon.h)
     *  @param  token   Additional token information
     */
    void process(int id, const Token &token) {}
    
};
 
/**
 *  End namespace
 */
}