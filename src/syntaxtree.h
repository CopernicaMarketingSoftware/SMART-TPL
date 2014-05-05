/**
 *  SyntaxTree.h
 *
 *  Class representing the abstract syntax tree that describes the entire
 *  template.tpl file.
 *
 *  The private base class of the SyntaxTree is the TokenProcessor class, so 
 *  that it is possible to pass an instance of the syntax tree class to the 
 *  tokenizer.
 *
 *  @author Emiel Bruijntjes <emiel.bruijntjes@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class SyntaxTree : protected TokenProcessor
{
public:
    /**
     *  Constructor
     *  @param  buffer          The buffer to parse
     *  @param  size            Size of the buffer
     *  @throws std::runtime_error in the case of an error
     */
    SyntaxTree(const char *buffer, size_t size) : TokenProcessor()
    {
        // ask the tokenizer to process the buffer, and tell that this object
        // is the parser that can be fed with the tokens found in the buffer
        Tokenizer tokenizer;
        if (tokenizer.process(this, buffer, size) == false)
        {
            // append the line to our error and throw it
            _error << " at line " << tokenizer.getCurrentLine();
            throw std::runtime_error(_error.str());
        }
    }

    /**
     *  Destructor
     */
    virtual ~SyntaxTree() {}

    /**
     *  Generate the source code
     *  @param  generator
     *  @return bool
     */
    bool generate(Generator *generator) const
    {
        // skip if there are no statements
        if (!_statements) return false;

        // generate the statements
        _statements->generate(generator);

        // done
        return true;
    }
};

/**
 *  End namespace
 */
}}