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
 *  @copyright 2014 - 2017 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl { namespace Internal {

/**
 *  Class definition
 */
class SyntaxTree : public TokenProcessor
{
public:
    /**
     *  Constructor
     *  @param  version         Tokenizer version (1 for old and 2 for new)
     *  @param  buffer          The buffer to parse
     *  @param  size            Size of the buffer
     *  @throws std::runtime_error in the case of an error
     */
    SyntaxTree(size_t version, const char *buffer, size_t size) : TokenProcessor()
    {
        // check version number
        if (version == 1)
        {
            // use the old tokenizer
            v1::Tokenizer tokenizer;
            
            // pass the buffer to the tokenizer, it will pass all tokens to this syntaxtree object
            if (tokenizer.process(this, buffer, size)) return;
            
            // report the error
            throw CompileError(_error, tokenizer.getCurrentLine());
        }
        else
        {
            // use the new tokenizer
            v2::Tokenizer tokenizer;
            
            // pass the buffer to the tokenizer, it will pass all tokens to this syntaxtree object
            if (tokenizer.process(this, buffer, size)) return;

            // report the error
            throw CompileError(_error, tokenizer.getCurrentLine());
        }
    }

    /**
     *  Destructor
     */
    virtual ~SyntaxTree() {}

    /**
     *  Generate the source code
     *  @param  generator The generator to use
     *  @return bool      False if we didn't have any statements to generate
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
