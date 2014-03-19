/**
 *  EchoStatement.h
 *
 *  Statement to simply echo raw output. Statements like this are created
 *  for text that was not inside a {template} instruction.
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
class EchoStatement : public Statement
{
private:
    /**
     *  The raw data to be echo'ed
     *  @var    std::string
     */
    std::string _data;

public:
    /**
     *  Constructor
     *  @param  token
     */
    EchoStatement(const Token *token) : _data(token->value, token->size) {}
    
    /**
     *  Destructor
     */
    virtual ~EchoStatement() {}
};

/**
 *  End of namespace
 */
}

