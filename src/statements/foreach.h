/**
 *  ForEach.h
 *
 *  Statement to simply loop through all the members of a multi member variable
 *
 *  @author Toon Schoenmakers <toon.schoenmakers@copernica.com>
 *  @copyright 2014 Copernica BV
 */

/**
 *  Set up namespace
 */
namespace SmartTpl {

/**
 *  Class definition
 */
class ForEachStatement : public Statement
{
private:
    /**
     *  The variable that will contain the value during the loop
     */
    std::unique_ptr<Token> _var;

    /**
     *  The variable that will contain the key during the loop
     *  @note This is not a requirement
     */
    std::unique_ptr<Token> _keyvar;

    /**
     *  The variable to loop over
     */
    std::unique_ptr<Variable> _target;

    /**
     *  The statements to execute within the loop
     */
    std::unique_ptr<Statements> _statements;

public:
    /**
     *  Constructor
     *  @param key           The {foreach ... in ${variable}} part of the foreach
     *                       we demand that this is a LiteralVariable, otherwise we'll throw
     *  @param target        The variable to loop through, this does NOT have to be a LiteralVariable
     *  @param statements    The statements to execute in the foreach loop
     */
    ForEachStatement(Token *var, Variable *target, Statements *statements)
    : _var(var)
    , _target(target)
    , _statements(statements) {
    }

    /**
     *  Constructor
     *  @param key           The {foreach ... in ${variable}} part of the foreach
     *                       we demand that this is a LiteralVariable, otherwise we'll throw
     *  @param target        The variable to loop through, this does NOT have to be a LiteralVariable
     *  @param statements    The statements to execute in the foreach loop
     *  @param keyvar        The variable to store the key in
     */
    ForEachStatement(Token *var, Variable *target, Token *keyvar, Statements *statements)
    : _var(var)
    , _keyvar(keyvar)
    , _target(target)
    , _statements(statements) {
    }

    /**
     *  Destructor
     */
    virtual ~ForEachStatement() {}

    /**
     *  Generate the output of this statement
     *  @param  generator
     */
    virtual void generate(Generator *generator) const override
    {
        generator->foreach(*_var.get(), _target.get(), _statements.get(), (_keyvar) ? *_keyvar.get() : std::string(""));
    }
};

/**
 *  End of namespace
 */
}

