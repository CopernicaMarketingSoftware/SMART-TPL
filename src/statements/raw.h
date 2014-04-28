/**
 *  RawStatement.h
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
class RawStatement : public Statement
{
private:
    /**
     *  The raw data to be echo'ed
     *  @var    std::unique_ptr
     */
    std::unique_ptr<Token> _data;

public:
    /**
     *  Constructor
     *  @param  token
     */
    RawStatement(Token *token) : _data(token) {}

    /**
     *  Destructor
     */
    virtual ~RawStatement() {}

    /**
     *  Generate the output of this statement
     *  @param  generator
     */
    virtual void generate(Generator *generator) const override
    {
        // add write instruction of raw data
        generator->raw(*_data);
    }
};

/**
 *  End of namespace
 */
}

