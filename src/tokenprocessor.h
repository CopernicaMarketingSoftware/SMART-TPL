/**
 *  TokenProcessor.h
 *
 *  Class that is used internally to process token found in a template file. 
 *  The constructor is protected - you should create an instance of SyntaxTree 
 *  to get the syntax tree of a template.
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
class Statements;

/**
 *  Class definition
 */
class TokenProcessor
{
private:
    /**
     *  Parser resource
     *  @var    void*
     */
    void *_resource;

protected:
    /**
     *  A set of statements that make up the template
     *  @var    std::unique_ptr
     */
    std::unique_ptr<Statements> _statements;

    /**
     *  This will contain any form of human readable errors in case there is
     *  something in _error we should stop parsing as soon as possible!
     */
    std::stringstream _error;

    /**
     *  Constructor
     */
    TokenProcessor();

public:
    /**
     *  Destructor
     */
    virtual ~TokenProcessor();

    /**
     *  Called by the tokenizer when a token is detected
     *  @param  id      Token identifier (see lemon.h)
     *  @param  token   Additional token information
     *  @return false if an error occured
     */
    bool process(int id, Token *token);

    /**
     *  Called when the statements were found that make up the program
     *  @param  statements
     */
    void add(Statements *statements)
    {
        // store in unique ptr
        _statements = std::unique_ptr<Statements>(statements);
    }

    /**
     *  This will get called by lemon in case of a syntax error
     */
    void syntaxError()
    {
        _error << "Syntax error";
    }

    /**
     *  This will get called by lemon in case of a parse failure
     */
    void parseFailure()
    {
        _error << "Parse failure";
    }
};
 
/**
 *  End namespace
 */
}