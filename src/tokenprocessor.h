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
namespace SmartTpl { namespace Internal {

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

    /**
     *  Is the template we are parsing in any way personalized?
     *  @var    bool
     */
    bool _personalized = false;

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
    std::string _error;

    /**
     *  This will contain the mode of the eventual template, set through {mode=raw}
     */
    std::unique_ptr<Token> _encoding;

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
        _statements.reset(statements);
    }

    /**
     *  This will get called by lemon in case of a syntax error
     */
    void syntaxError(const std::vector<std::string> &expectedTokens)
    {
        _error.append("Syntax error");

        // If we have any expected tokens append them to the error
        if (expectedTokens.empty() == false)
        {
            _error.append(", expected one of the following tokens [");

            for (auto iter = expectedTokens.begin(); iter != expectedTokens.end(); ++iter)
            {
                _error.append(*iter);

                // for every token that is not our last token (end iter - 1) we append a space for readability
                if (iter != expectedTokens.end() - 1) _error.push_back(' ');
            }

            _error.push_back(']');
        }
    }

    /**
     *  This template uses personalisation data
     */
    void setPersonalized()
    {
        _personalized = true;
    }

    /**
     *  Get whether we're personalized
     *
     *  @return boolean
     */
    bool personalized() const
    {
        return _personalized;
    }

    /**
     *  This will get called by lemon in case of a parse failure
     */
    void parseFailure()
    {
        _error = "Parse failure";
    }

    /**
     *  This will get called by lemon if the internal lemon stack is overflowing
     */
    void stackOverflow()
    {
        _error = "Stack overflow";
    }

    /**
     *  Allows us to set an error string from somewhere else
     */
    void error(const std::string &str)
    {
        _error = str;
    }

    /**
     *  Set the encoding mode, will be called from lemon
     */
    void mode(Token *token)
    {
        _encoding.reset(token);
    }

    /**
     *  Retrieve the current encoding mode of this tokenprocessor
     */
    const std::string &mode() const
    {
        return *_encoding;
    }
};

/**
 *  End namespace
 */
}}
