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
class SyntaxTree : protected Parser
{
public:
    /**
     *  Constructor
     *  @param  tokenizer       The tokenizer that can find tokens in a file
     *  @param  filename        Filename to parse
     */
    SyntaxTree(Tokenizer *tokenizer, const char *filename) : Parser()
    {
        // ask the tokenizer to process the file, and tell that this object
        // is the parser that can be fed with the tokens found in the file
        tokenizer->process(this, filename);
        
        // @todo    error handling
    }

    /**
     *  Constructor
     *  @param  tokenizer       The tokenizer that can find tokens in the buffer
     *  @param  buffer          The buffer to parse
     *  @param  size            Size of the buffer
     */
    SyntaxTree(Tokenizer *tokenizer, const char *buffer, size_t size) : Parser()
    {
        // ask the tokenizer to process the buffer, and tell that this object
        // is the parser that can be fed with the tokens found in the buffer
        tokenizer->process(this, buffer, size);
        
        // @todo    error handling
    }
        
    /**
     *  Destructor
     */
    virtual ~SyntaxTree() {}
};

/**
 *  End namespace
 */
}

