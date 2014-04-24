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
     */
    void process(int id, Token *token);

    /**
     *  Called when the statements were found that make up the program
     *  @param  statements
     */
    void add(Statements *statements)
    {
        // store in unique ptr
        _statements = std::unique_ptr<Statements>(statements);
    }
};
 
/**
 *  End namespace
 */
}