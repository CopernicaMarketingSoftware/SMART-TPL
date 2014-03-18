/**
 *  SyntaxTree.h
 *
 *  Class representing the abstract syntax tree that describes the entire
 *  template.tpl file.
 *
 *  The private base class of the SyntaxTree is the Parser class, so that it
 *  is possible to pass an instance of the syntax tree class to the tokenizer
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
class SyntaxTree : private Parser
{
private:
    /**
     *  Called by the tokenizer when a token is detected
     *  @param  id      Token identifier (see lemon.h)
     *  @param  token   Additional token information
     */
    virtual void process(int id, const Token &token) override;

public:
    /**
     *  Constructor
     *  @param  tokenizer       The tokenizer that can find tokens in the buffer
     *  @param  buffer          The buffer to parse
     *  @param  size            Size of the buffer
     */
    SyntaxTree(Tokenizer *tokenizer, const char *buffer, size_t size);
    
    /**
     *  Destructor
     */
    virtual ~SyntaxTree();
};

/**
 *  End namespace
 */
}

